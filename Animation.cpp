//
// Created by dmitriy on 4/17/22.
//

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Class_Game.h"
#include "Card_src.h"
#include<filesystem>
#include "Animation.h"


void TextureHolder::load(std::string name, std::string filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);

    textureMap.insert(std::make_pair(name, std::move(texture)));
}

sf::Texture& TextureHolder::get(std::string name){
    auto found = textureMap.find(name);
    return *found->second;
}

GameAnimation::GameAnimation(Game& g): window(sf::VideoMode(900, 700), "Test"), gameLogic(g){
        std::string parent_path = std::filesystem::current_path().parent_path();
        parent_path+="/";
        textureHolder.load("Game_Table", parent_path+"src/Game_table.jpg");
        textureHolder.load("fold_button", parent_path+"src/fold.jpg");
        textureHolder.load("Background", parent_path+"src/Background.jpg");
        textureHolder.load("Button_start_game", parent_path+"src/Button_start_game.png");
        textureHolder.load("Button_show_info", parent_path+"src/Igry_v_Novigrade.png");
        textureHolder.load("Window_show_info", parent_path+"src/Igry_v_Novigrade.png");
        textureHolder.load("Player_vs_player", parent_path + "src/Player_vs_Player.png");
        textureHolder.load("Player_vs_bot", parent_path + "src/Player_vs_bot.png");
        textureHolder.load("Easy_dif", parent_path + "src/Eazy_dif.png");
        textureHolder.load("Normal_dif", parent_path + "src/Normal_dif.png");
        textureHolder.load("Hard_dif", parent_path + "src/Hard_dif.png");
        textureHolder.load("Deck1", parent_path + "src/Eazy_dif.png");
        textureHolder.load("Deck2", parent_path + "src/Normal_dif.png");
        textureHolder.load("Deck3", parent_path + "src/Hard_dif.png");
        textureHolder.load("Player2_win", parent_path + "src/Player2_win.png");
        textureHolder.load("Player1_win", parent_path + "src/Player1_win.png");
        for(const auto& card: src.Src_vector){
            textureHolder.load(card->name, parent_path+card->filename_of_image);
        }
}

void GameAnimation::run(){
    while (window.isOpen()){
        processEvents();
        update();
        render();
    }
}

void GameAnimation::processEvents(){
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type) {
            case sf::Event::MouseButtonReleased:{
                if(is_game_ended) {
                    is_game_ended = false;
                    is_menu_open = true;
                    break;
                }
                if(is_waiting){
                    is_waiting = false;
                    break;
                }
                if(is_menu_open) {
                    if(is_first_menu_open && !is_show_info_open) {
                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        sf::FloatRect start_bounds = sf::FloatRect(750, 600,
                                                                   100, 50);
                        sf::FloatRect info_bounds = sf::FloatRect (750, 550,
                                                                   100, 50);
                        if(start_bounds.contains(mouse)) {
                            is_first_menu_open = false;
                            is_second_menu_open = true;
                            choosing_been_bot_and_player = true;
                        }
                        if(info_bounds.contains(mouse)) {
                            is_show_info_open = true;
                        }
                        break;
                    }
                    else if(is_first_menu_open && is_show_info_open) {
                        is_show_info_open = false;
                        break;
                    }
                    else {
                        if(choosing_been_bot_and_player) {
                            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            sf::FloatRect player_vs_player_bounds = sf::FloatRect(390, 300,
                                                                                  80, 50);
                            sf::FloatRect player_vs_bot_bounds = sf::FloatRect(390, 350,
                                                                               80, 50);
                            if(player_vs_player_bounds.contains(mouse)) {
                                choosing_been_bot_and_player = false;
                                choosing_decks = true;
                            }
                            if(player_vs_bot_bounds.contains(mouse)) {
                                choosing_been_bot_and_player = false;
                                choosing_bot_difficulty = true;
                            }
                            break;
                        }
                        if(choosing_bot_difficulty) {
                            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            sf::FloatRect easy = sf::FloatRect(330, 325, 70, 50);
                            sf::FloatRect normal = sf::FloatRect(410, 325, 70, 50);
                            sf::FloatRect hard = sf::FloatRect (490, 325, 70, 50);
                            if(easy.contains(mouse)) gameLogic.player2 = Bot_src.player_weak;
                            else if(normal.contains(mouse)) gameLogic.player2 = Bot_src.player_normal;
                            else if(hard.contains(mouse)) gameLogic.player2 = Bot_src.player_hard;
                            choosing_bot_difficulty = false;
                            choosing_decks = 1;
                            break;
                        }
                        if(choosing_decks) {
                            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            sf::FloatRect d1 = sf::FloatRect(330, 325, 70, 50);
                            sf::FloatRect d2 = sf::FloatRect(410, 325, 70, 50);
                            sf::FloatRect d3 = sf::FloatRect (490, 325, 70, 50);
                            if(choosing_decks == 1) {
                                if (d1.contains(mouse)) gameLogic.player1 = Player(Player_src.deck_1, 0);
                                else if (d2.contains(mouse)) gameLogic.player1 = Player(Player_src.deck_2, 0);
                                else if (d3.contains(mouse)) gameLogic.player1 = Player(Player_src.deck_3, 0);
                                if(gameLogic.player2.is_bot) {
                                    choosing_decks = 0;
                                    is_menu_open = false;
                                }
                                else choosing_decks = 2;
                                break;
                            }
                            if(choosing_decks == 2) {
                                if (d1.contains(mouse)) gameLogic.player2 = Player(Player_src.deck_1, 0);
                                else if (d2.contains(mouse)) gameLogic.player2 = Player(Player_src.deck_2, 0);
                                else if (d3.contains(mouse)) gameLogic.player2 = Player(Player_src.deck_3, 0);
                                choosing_decks = 0;
                                is_menu_open = false;
                                break;
                            }
                        }
                    }
                    break;
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
                if(gameLogic.is_first_moving != moving && !gameLogic.now_moving().is_bot) is_waiting = true;
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

//.................................................................................................................................................//
void GameAnimation::update(){
    if(gameLogic.is_round_ended()){
        gameLogic.on_round_ended();
    }
    if(gameLogic.is_game_ended()){
        gameLogic.on_round_ended();
        gameLogic.player1.hand.clear();
        gameLogic.player1.deck.clear();
        gameLogic.player1.reset.clear();
        gameLogic.player2.hand.clear();
        gameLogic.player2.deck.clear();
        gameLogic.player2.reset.clear();
        is_game_ended = true;
        is_menu_open = true;
        is_first_menu_open = true;
    }
}

void GameAnimation::render(){
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
                InfoSprite.setScale(
                        targetSize.x / InfoSprite.getLocalBounds().width,
                        targetSize.y / InfoSprite.getLocalBounds().height);
                window.draw(InfoSprite);
            }
        }
        else {
            if(choosing_been_bot_and_player) {
                sf::Sprite player_vs_player(textureHolder.get("Player_vs_player"));
                player_vs_player.setPosition(390, 300);
                sf::Vector2f targetSizest(80.0f, 50.0f);
                player_vs_player.setScale(
                        targetSizest.x / player_vs_player.getLocalBounds().width,
                        targetSizest.y / player_vs_player.getLocalBounds().height);

                sf::Sprite player_vs_bot(textureHolder.get("Player_vs_bot"));
                player_vs_bot.setPosition(390, 350);
                player_vs_bot.setScale(
                        targetSizest.x / player_vs_bot.getLocalBounds().width,
                        targetSizest.y / player_vs_bot.getLocalBounds().height);

                window.draw(player_vs_player);
                window.draw(player_vs_bot);
            }
            if(choosing_bot_difficulty) {
                sf::Sprite Easy_dif(textureHolder.get("Easy_dif"));
                sf::Sprite Normal_dif(textureHolder.get("Normal_dif"));
                sf::Sprite Hard_dif(textureHolder.get("Hard_dif"));
                sf::Vector2f targetSizest(70.0f, 50.0f);

                Easy_dif.setPosition(330, 325);
                Normal_dif.setPosition(410, 325);
                Hard_dif.setPosition(490, 325);

                Easy_dif.setScale(
                        targetSizest.x / Easy_dif.getLocalBounds().width,
                        targetSizest.y / Easy_dif.getLocalBounds().height);
                Normal_dif.setScale(
                        targetSizest.x / Normal_dif.getLocalBounds().width,
                        targetSizest.y / Normal_dif.getLocalBounds().height);
                Hard_dif.setScale(
                        targetSizest.x / Hard_dif.getLocalBounds().width,
                        targetSizest.y / Hard_dif.getLocalBounds().height);
                window.draw(Easy_dif);
                window.draw(Normal_dif);
                window.draw(Hard_dif);
            }
            if(choosing_decks) {
                sf::Sprite deck1(textureHolder.get("deck1"));
                sf::Sprite deck2(textureHolder.get("deck2"));
                sf::Sprite deck3(textureHolder.get("deck3"));
                sf::Vector2f targetSizest(70.0f, 50.0f);

                deck1.setPosition(330, 325);
                deck2.setPosition(410, 325);
                deck3.setPosition(490, 325);

                deck1.setScale(
                        targetSizest.x / deck1.getLocalBounds().width,
                        targetSizest.y / deck1.getLocalBounds().height);
                deck2.setScale(
                        targetSizest.x / deck2.getLocalBounds().width,
                        targetSizest.y / deck2.getLocalBounds().height);
                deck3.setScale(
                        targetSizest.x / deck3.getLocalBounds().width,
                        targetSizest.y / deck3.getLocalBounds().height);
                window.draw(deck1);
                window.draw(deck2);
                window.draw(deck3);
            }
            if(is_game_ended) {
                sf::Vector2f targetSize(900.0f, 700.0f);
                if(gameLogic.player1.hp != 0) {
                    sf::Sprite player1_win(textureHolder.get("Player1_win"));
                    player1_win.setScale(
                            targetSize.x / player1_win.getLocalBounds().width,
                            targetSize.y / player1_win.getLocalBounds().height);
                    window.draw(player1_win);
                }
                else {
                    sf::Sprite player2_win(textureHolder.get("Player2_win"));
                    player2_win.setScale(
                            targetSize.x / player2_win.getLocalBounds().width,
                            targetSize.y / player2_win.getLocalBounds().height);
                    window.draw(player2_win);
                }
            }
        }
        window.display();
        return;
    }
    if (gameLogic.now_moving().is_bot) {
        Bot_logic().bot_move(gameLogic);
        return;
    }
    Player& curPlayer = gameLogic.now_moving();
    sf::Sprite deskSprite(textureHolder.get("Game_Table"));
    //deskSprite.setScale(window.getSize().x/deskSprite.getLocalBounds().width, 6.0/7.0*window.getSize().y/deskSprite.getLocalBounds().height);
    window.draw(deskSprite);
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


    std::string parent_path = std::filesystem::current_path().parent_path();
    parent_path+="/";
    sf::Font font;
    font.loadFromFile(parent_path + "src/font.ttf");

    sf::Text strength1;
    strength1.setFont(font);
    strength1.setString(std::to_string(gameLogic.now_moving().sum_strength));
    strength1.setCharacterSize(40);
    strength1.setFillColor(sf::Color::Blue);
    strength1. setPosition(90, 420);
    window.draw(strength1);

    sf::Text strength2;
    strength2.setFont(font);
    strength2.setString(std::to_string(gameLogic.not_now_moving().sum_strength));
    strength2.setCharacterSize(40);
    strength2.setFillColor(sf::Color::Blue);
    strength2. setPosition(90, 130);
    window.draw(strength2);

    sf::Text hp1;
    hp1.setFont(font);
    hp1.setString(std::to_string(gameLogic.now_moving().hp));
    hp1.setStyle(sf::Text::Style::Bold);
    hp1.setCharacterSize(40);
    hp1.setFillColor(sf::Color::Yellow);
    hp1. setPosition(840, 380);
    window.draw(hp1);

    sf::Text hp2;
    hp2.setFont(font);
    hp2.setString(std::to_string(gameLogic.not_now_moving().hp));
    hp2.setStyle(sf::Text::Style::Bold);
    hp2.setCharacterSize(40);
    hp2.setFillColor(sf::Color::Yellow);
    hp2. setPosition(840, 170);
    window.draw(hp2);

    window.display();
}

void GameAnimation::show_line_of_cards(const std::vector<Card*>& cards, size_t start_x, size_t end_x, size_t y, bool clickable){
    if(cards.size() == 0 ) {
        return;
    }
    std::string parent_path = std::filesystem::current_path().parent_path();
    parent_path+="/";
    size_t delta = (end_x - start_x) / cards.size();
    for(size_t i=0; i<cards.size(); ++i){
        sf::Sprite cardSprite(textureHolder.get(cards[i]->name));
        cardSprite.setPosition(start_x + i * delta, y);
        cardSprite.setScale(1.0/6.0, 1.0/6.0);
        if(clickable) clickSprites.push_back(cardSprite);
        window.draw(cardSprite);
        sf::Font font;
        font.loadFromFile(parent_path + "src/font.ttf");
        sf::Text strengthText;
        strengthText.setFont(font);
        std::string s = std::to_string(cards[i]->amount_of_strength_now);
        //strengthText.setOutlineColor(sf::Color::White);
        //strengthText.setColor(sf::Color::White);
        strengthText.setString(s);
        strengthText.setCharacterSize(10);
        strengthText.setFillColor(sf::Color::Red);
        strengthText. setPosition(start_x + i * delta + 5, y + 1);
        window.draw(strengthText);
    }

}