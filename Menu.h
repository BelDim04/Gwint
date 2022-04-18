#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;

void main_menu(RenderWindow& window) {
    Texture background, button_start_game, button_choose_cards, button_read_about, info_about;
    bool is_first_menu_open = 1;
    background.loadFromFile("filename");
    button_choose_cards.loadFromFile("filename");//эту можно пока не реализовывать, это так, на будущее
    button_start_game.loadFromFile("filename");
    button_read_about.loadFromFile("filename");
    info_about.loadFromFile("filename");
    Sprite button_choose_cards_spr(button_choose_cards), button_start_game_spr(button_start_game),
        button_read_about_spr(button_read_about), info_about_spr(info_about);
    button_start_game_spr.setPosition(1, 1);
    button_read_about_spr.setPosition(1, 1);
    button_choose_cards_spr.setPosition(1, 1);
    info_about_spr.setPosition(1, 1);
    int menuNum = 0;
    while(is_first_menu_open) {
        window.clear();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if (IntRect(1, 1, 1, 1).contains(Mouse::getPosition(window))) {
            //если нажали на read_about
            menuNum = 1;
        }
        if (IntRect(1, 1, 1, 1).contains(Mouse::getPosition(window))) {
            //если нажали на choose_cards
            menuNum = 2;
        }
        if (IntRect(1, 1, 1, 1).contains(Mouse::getPosition(window))) {
            //если нажали на start_game
            menuNum = 3;
        }
        if(Mouse::isButtonPressed(Mouse::Left)) {
            if(menuNum == 1) {
                window.draw(info_about_spr);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            if(menuNum == 2) {
                //пока ничего
            }
            if(menuNum == 3) {
                is_first_menu_open = false;
                //мы открываем следующую вкладку меню, где выбираем, против кого драться
            }
        }
        //Если нажимаешь на button_read_about, рисуем текстуру info_about_spr
        //Если нажимаешь на choose_cards, открывается выбор колоды
        //Если нажимаешь start_game, открывается выбор начала игры(т.е. выбираешь против бота или человека)
        window.draw(button_choose_cards_spr);
        window.draw(button_read_about_spr);
        window.draw(button_start_game_spr);
        window.display();
        menuNum = 0;
    }
}
