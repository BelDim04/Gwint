#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Class_Game.h"
#include "Card_src.h"
#include<filesystem>
#include "Bot_decks.h"
#include"Player_decks.h"
#include "Bot_Logic.h"

class TextureHolder{
public:
    std::map<std::string , std::unique_ptr<sf::Texture>> textureMap;

    void load(std::string name, std::string filename);

    sf::Texture& get(std::string name);
};


class GameAnimation{
public:
    sf::RenderWindow window;

    Game gameLogic;

    TextureHolder textureHolder;

    std::vector<sf::Sprite> clickSprites;

    Src src = Src();
    Player_deck_src Player_src = Player_deck_src();
    Bot_deck_src Bot_src = Bot_deck_src();

    bool is_menu_open = true;
    bool is_first_menu_open = true;
    bool is_second_menu_open = false;
    bool is_show_info_open = false;
    bool choosing_been_bot_and_player = false;
    bool choosing_bot_difficulty = false;
    int choosing_decks = 0;
    bool is_game_ended = false;


    bool is_waiting = false;


    GameAnimation(Game& g);

    void run();

    void processEvents();

    void update();

    void render();

    void show_line_of_cards(const std::vector<Card*>& cards, size_t start_x, size_t end_x, size_t y, bool clickable);
};