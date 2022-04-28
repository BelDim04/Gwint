//
// Created by dmitriy on 4/17/22.
//

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Class_Game.h"
#include "Card_src.h"
#include<filesystem>

/*class CardT{
public:
    size_t id;
    std::string filename;

    CardT(size_t n, std::string f): id(n), filename(f){}
};


class GameLogic{
public:
    CardT card1;
    CardT card2;

    bool turnChange;
    bool movingFirst;

    GameLogic(): card1(CardT(1, "/home/dmitriy/CLionProjects/Gwint/1.jpg")), card2(CardT(2, "/home/dmitriy/CLionProjects/Gwint/2.jpg")), turnChange(false), movingFirst(true){}

    void playerReady(){
        turnChange = false;
    }

    void updateForNextTurn(size_t n) {
        turnChange = true;
        movingFirst = !movingFirst;
    }
};*/

class TextureHolder{
public:
    std::map<std::string , std::unique_ptr<sf::Texture>> textureMap;

    void load(std::string name, std::string filename){
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        texture->loadFromFile(filename);

        textureMap.insert(std::make_pair(name, std::move(texture)));
    }

    sf::Texture& get(std::string name){
        auto found = textureMap.find(name);
        return *found->second;
    }
};

class GameAnimation{
public:
    sf::RenderWindow window;

    Game gameLogic;

    TextureHolder textureHolder;

    std::vector<sf::Sprite> clickSprites;

    bool is_menu_open = true;
    bool is_first_menu_open = true;
    bool is_second_menu_open = false;
    bool is_show_info_open = false;

    bool is_waiting = false;


    GameAnimation(Game& g): window(sf::VideoMode(900, 700), "Test"), gameLogic(g){
        std::string parent_path = std::filesystem::current_path().parent_path();
        parent_path+="/";
        textureHolder.load("Game_Table", parent_path+"src/Game_table.jpg");
        textureHolder.load("fold_button", parent_path+"src/fold.jpg");
        textureHolder.load("Background", parent_path+"src/Background.jpg");
        textureHolder.load("Button_start_game", parent_path+"src/Button_start_game.png");
        textureHolder.load("Button_show_info", parent_path+"src/Igry_v_Novigrade.png");
        textureHolder.load("Window_show_info", parent_path+"src/Igry_v_Novigrade.png");
        for(const auto& card: g.player1.hand){
            textureHolder.load(card->name, parent_path+card->filename_of_image);
        }
        for(const auto& card: g.player2.hand){
            textureHolder.load(card->name, parent_path+card->filename_of_image);
        }
        for(const auto& card: g.player1.deck){
            textureHolder.load(card->name, parent_path+card->filename_of_image);
        }
        for(const auto& card: g.player2.deck){
            textureHolder.load(card->name, parent_path+card->filename_of_image);
        }
    }

    void run(){
        while (window.isOpen()){
            processEvents();
            update();
            render();
        }
    }

    void processEvents(){
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::MouseButtonReleased:{
                    if(is_waiting){
                        is_waiting = false;
                        break;
                    }
                    if(is_menu_open) {
                        //если first menu is open
                        //если нажали на show_info, переменная = 1
                        //если нажали на start то second menu is open
                        if(is_first_menu_open && !is_show_info_open) {
                            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            sf::FloatRect start_bounds = sf::FloatRect(750, 600,
                                                                       100, 50);
                            sf::FloatRect info_bounds = sf::FloatRect (750, 550,
                                                                       100, 50);
                            if(start_bounds.contains(mouse)) {
                                is_first_menu_open = false;
                                is_second_menu_open = true;
                            }
                            if(info_bounds.contains(mouse)) {
                                is_show_info_open = true;
                            }

                        }
                        else if(is_first_menu_open && is_show_info_open) {
                            is_show_info_open = false;
                        }
                        else {

                        }
                        return;
                    }
                    bool moving = gameLogic.is_first_moving;
                    for(size_t i=0;i<clickSprites.size()-1;++i){
                        sf::Sprite sprite = clickSprites[i];
                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        sf::FloatRect bounds = sprite.getGlobalBounds();
                        if (bounds.contains(mouse)){
                            gameLogic.make_turn(i);
                            break;
                        }
                    }
                    sf::Sprite foldSprite = clickSprites[clickSprites.size()-1];
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::FloatRect bounds = foldSprite.getGlobalBounds();
                    if (bounds.contains(mouse)){
                        gameLogic.now_moving().has_fold = true;
                        gameLogic.switch_turn();
                    }

                    if(gameLogic.is_first_moving != moving) is_waiting = true;
                    break;
                }
                /*case sf::Event::KeyPressed:{
                    if(event.key.code == sf::Keyboard::Enter) {
                        is_show_info_open = false;
                    }
                }*/
                case sf::Event::Closed:{
                    window.close();
                    break;
                }
            }
        }
    }

    void update(){
        if(gameLogic.is_round_ended()){
            gameLogic.on_round_ended();
        }
        if(gameLogic.is_game_ended()){
            gameLogic.on_game_ended();
            is_menu_open = true;
        }
    }

    void render(){
        window.clear();
        if(is_waiting){
            window.display();
            return;
        }
        if(is_menu_open){

            sf::Sprite MenuSprite(textureHolder.get("Background"));
            sf::Vector2f targetSize(900.0f, 700.0f); //целевой размер
            MenuSprite.setScale(
                    targetSize.x / MenuSprite.getLocalBounds().width,
                    targetSize.y / MenuSprite.getLocalBounds().height);
            window.draw(MenuSprite);
            if(is_first_menu_open) {


                sf::Sprite StartGameSprite(textureHolder.get("Button_start_game"));
                StartGameSprite.setPosition(750, 600);
                sf::Vector2f targetSizest(100.0f, 50.0f);
                StartGameSprite.setScale(
                        targetSizest.x / StartGameSprite.getLocalBounds().width,
                        targetSizest.y / StartGameSprite.getLocalBounds().height);

                sf::Sprite ButtonShowInfoSprite(textureHolder.get("Button_show_info"));
                ButtonShowInfoSprite.setPosition(750, 550);
                ButtonShowInfoSprite.setScale(
                        targetSizest.x / ButtonShowInfoSprite.getLocalBounds().width,
                        targetSizest.y / ButtonShowInfoSprite.getLocalBounds().height);

                window.draw(StartGameSprite);
                window.draw(ButtonShowInfoSprite);

                if(is_show_info_open) {
                    sf::Sprite InfoSprite(textureHolder.get("Window_show_info"));
                    window.draw(InfoSprite);
                }
            }
            else {

            }
            window.display();
            return;
        }
        sf::Sprite deskSprite(textureHolder.get("Game_Table"));
        //deskSprite.setScale(window.getSize().x/deskSprite.getLocalBounds().width, 6.0/7.0*window.getSize().y/deskSprite.getLocalBounds().height);
        window.draw(deskSprite);
        Player& curPlayer = gameLogic.now_moving();
        Player& otherPlayer = gameLogic.not_now_moving();
        clickSprites.clear();
        show_line_of_cards(curPlayer.hand, 0, 700, 600, true);
        sf::Sprite foldSprite(textureHolder.get("fold_button"));
        foldSprite.setPosition(720, 630);
        window.draw(foldSprite);
        clickSprites.push_back(foldSprite);
        show_line_of_cards(curPlayer.desk.strength_melee, 340, 900, 300, false);
        show_line_of_cards(curPlayer.desk.strength_siege, 340, 900, 400, false);
        show_line_of_cards(curPlayer.desk.strength_archer, 340, 900, 500, false);
        show_line_of_cards(otherPlayer.desk.strength_melee, 340, 900, 200, false);
        show_line_of_cards(otherPlayer.desk.strength_siege, 340, 900, 100, false);
        show_line_of_cards(otherPlayer.desk.strength_archer, 340, 900, 0, false);

        show_line_of_cards(curPlayer.desk.buff_melee, 265, 265, 300, false);
        show_line_of_cards(curPlayer.desk.buff_siege, 265, 265, 400, false);
        show_line_of_cards(curPlayer.desk.buff_archer, 265, 265, 500, false);
        show_line_of_cards(otherPlayer.desk.buff_melee, 265, 265, 200, false);
        show_line_of_cards(otherPlayer.desk.buff_siege, 265, 265, 100, false);
        show_line_of_cards(otherPlayer.desk.buff_archer, 265, 265, 0, false);

        show_line_of_cards(gameLogic.weather_manager.weather, 10, 210,250,false);
        window.display();
    }

    void show_line_of_cards(const std::vector<Card*>& cards, size_t start_x, size_t end_x, size_t y, bool clickable){
        if(cards.size() == 0 ) {
            return;
        }
        size_t delta = (end_x - start_x) / cards.size();
        for(size_t i=0; i<cards.size(); ++i){
            sf::Sprite cardSprite(textureHolder.get(cards[i]->name));
            cardSprite.setPosition(start_x + i * delta, y);
            cardSprite.setScale(1.0/6.0, 1.0/6.0);
            if(clickable) clickSprites.push_back(cardSprite);
            window.draw(cardSprite);
        }
    }
};