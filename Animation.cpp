//
// Created by dmitriy on 4/17/22.
//

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Class_Game.h"
#include "Card_src.h"
#include<filesystem>
#include "Bot_decks.h"
#include"Player_decks.h"
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

                    }
                    else if(is_first_menu_open && is_show_info_open) {
                        is_show_info_open = false;
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
                        }
                        if(choosing_bot_difficulty) {
                            Bot_deck_src bot = Bot_deck_src();
                            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            sf::FloatRect easy = sf::FloatRect(330, 325, 70, 50);
                            sf::FloatRect normal = sf::FloatRect(410, 325, 70, 50);
                            sf::FloatRect hard = sf::FloatRect (490, 325, 70, 50);
                            if(easy.contains(mouse)) {
                                gameLogic.player2 = bot.player_weak;
                                std::string parent_path = std::filesystem::current_path().parent_path();
                                parent_path+="/";
                                for(const auto& card: gameLogic.player2.hand){
                                    textureHolder.load(card->name, parent_path+card->filename_of_image);
                                }
                                for(const auto& card: gameLogic.player2.deck){
                                    textureHolder.load(card->name, parent_path+card->filename_of_image);
                                }
                                choosing_bot_difficulty = false;
                                is_menu_open = false;
                            }
                            if(normal.contains(mouse)) {
                                gameLogic.player2 = bot.player_normal;
                                choosing_bot_difficulty = false;
                                is_menu_open = false;
                            }
                            if(hard.contains(mouse)) {
                                gameLogic.player2 = bot.player_hard;
                                choosing_bot_difficulty = false;
                                is_menu_open = false;
                            }
                            //после этого мб стоит сделать выбор колоды самому игроку, пока не делал
                        }
                        if(choosing_decks) {
                            //здесь надо выбрать колоды игрокам, пока не делал
                            Player_deck_src src = Player_deck_src();
                            gameLogic.player1 = src.player2;
                            std::string parent_path = std::filesystem::current_path().parent_path();
                            parent_path+="/";
                            for(const auto& card: gameLogic.player1.hand){
                                textureHolder.load(card->name, parent_path+card->filename_of_image);
                            }
                            for(const auto& card: gameLogic.player1.deck){
                                textureHolder.load(card->name, parent_path+card->filename_of_image);
                            }
                            is_menu_open = false;
                        }
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

void GameAnimation::update(){
    if(gameLogic.is_round_ended()){
        gameLogic.on_round_ended();
    }
    if(gameLogic.is_game_ended()){
        gameLogic.on_game_ended();
        is_menu_open = true;
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

            }
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

void GameAnimation::show_line_of_cards(const std::vector<Card*>& cards, size_t start_x, size_t end_x, size_t y, bool clickable){
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

