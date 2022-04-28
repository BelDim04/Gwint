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


    GameAnimation(Game& g): window(sf::VideoMode(900, 700), "Test"), gameLogic(g){
        std::string parent_path = std::filesystem::current_path().parent_path();
        textureHolder.load("Game_Table", parent_path+"/src/Game_table.jpg");
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
                    bool flag =false;
                    for(size_t i=0;i<clickSprites.size();++i){
                        sf::Sprite sprite = clickSprites[i];
                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        sf::FloatRect bounds = sprite.getGlobalBounds();
                        if (bounds.contains(mouse)){
                            gameLogic.make_turn(i);
                            flag =true;
                            break;
                        }
                    }
                    if(!flag) {
                        gameLogic.now_moving().has_fold = true;
                        gameLogic.switch_turn();
                    }
                    break;
                }
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
        /*if(is_menu_open){
            main_menu();
            window.display();
            return;
        }*/
        sf::Sprite deskSprite(textureHolder.get("Game_Table"));
        //deskSprite.setScale(window.getSize().x/deskSprite.getLocalBounds().width, 6.0/7.0*window.getSize().y/deskSprite.getLocalBounds().height);
        window.draw(deskSprite);
        Player& curPlayer = gameLogic.now_moving();
        Player& otherPlayer = gameLogic.not_now_moving();
        clickSprites.clear();
        show_line_of_cards(curPlayer.hand, 0, 900, 600, true);
        show_line_of_cards(curPlayer.desk.strength_melee, 330, 900, 300, false);
        show_line_of_cards(curPlayer.desk.strength_siege, 330, 900, 400, false);
        show_line_of_cards(curPlayer.desk.strength_archer, 330, 900, 500, false);
        show_line_of_cards(otherPlayer.desk.strength_melee, 330, 900, 200, false);
        show_line_of_cards(otherPlayer.desk.strength_siege, 330, 900, 100, false);
        show_line_of_cards(otherPlayer.desk.strength_archer, 330, 900, 0, false);
        window.display();
    }

    void show_line_of_cards(const std::vector<Card*>& cards, size_t start_x, size_t end_x, size_t y, bool clickable){
        if(cards.size() ==0 ) {
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

    void main_menu() {
        std::string parent_path = std::filesystem::current_path().parent_path();
        sf::Texture background, button_start_game, button_choose_cards, button_read_about, info_about;
        background.loadFromFile(parent_path + "/src/Background.jpg");
        //button_choose_cards.loadFromFile("filename");//эту можно пока не реализовывать, это так, на будущее
        button_start_game.loadFromFile(parent_path + "/src/Button_start_game.png");
        // button_read_about.loadFromFile("filename");
        info_about.loadFromFile(parent_path + "/src/Igry_v_Novigrade.png");
        sf::Sprite background_spr(background);
        sf::Vector2f targetSize(1777.0f, 1000.0f); //целевой размер
        background_spr.setScale(
                targetSize.x / background_spr.getLocalBounds().width,
                targetSize.y / background_spr.getLocalBounds().height);


        sf::Sprite button_choose_cards_spr(button_choose_cards), button_start_game_spr(button_start_game),
                button_read_about_spr(button_read_about), info_about_spr(info_about);

        button_start_game_spr.setPosition(12, 12);
        sf::Vector2f targetSizest(800.0f, 400.0f); //целевой размер
        button_start_game_spr.setScale(
                targetSizest.x / button_start_game_spr.getLocalBounds().width,
                targetSizest.y / button_start_game_spr.getLocalBounds().height);


        button_read_about_spr.setPosition(1, 1);

        //button_choose_cards_spr.setPosition(1, 1);
        //info_about_spr.setPosition(1, 1);
        info_about_spr.setScale(
                targetSize.x / info_about_spr.getLocalBounds().width,
                targetSize.y / info_about_spr.getLocalBounds().height);
        //Если нажимаешь на button_read_about, рисуем текстуру info_about_spr
        //Если нажимаешь на choose_cards, открывается выбор колоды
        //Если нажимаешь start_game, открывается выбор начала игры(т.е. выбираешь против бота или человека)
        //window.draw(button_choose_cards_spr);
        // window.draw(button_read_about_spr);
        window.draw(background_spr);
        window.draw(button_start_game_spr);
    }
};