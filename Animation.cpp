#include <SFML/Graphics.hpp>
#include <iostream>
class Animation{
public:
    sf::RenderWindow& window;

    float window_basic_width;
    float window_basic_height;
    float card_width;

    float strength_text_basic_scale_x;
    float strength_text_basic_scale_y;
    float strength_text_delta_x;
    float strength_text_delta_y;

    float choosable_basic_start_x;
    float choosable_basic_end_x;
    float choosable_basic_y;

    float close_melee_basic_up;
    float close_archer_basic_up;
    float close_siege_basic_up;

    float remote_melee_basic_up;
    float remote_archer_basic_up;
    float remote_siege_basic_up;

    float strength_cards_left_coordinate;
    float strength_cards_right_coordinate;

    float weather_left_coordinate;
    float weather_right_coordinate;
    float weather_y;

    float close_buff_melee_basic_up;
    float close_buff_archer_basic_up;
    float close_buff_siege_basic_up;
    float remote_buff_melee_basic_up;
    float remote_buff_archer_basic_up;
    float remote_buff_siege_basic_up;

    float buff_cards_left_coordinate;
    float buff_cards_right_coordinate;

    std::vector<sf::Sprite> choosable_cards;

    bool now_choosing = false;
    size_t chosen = -1;

    bool waiting_next_player;

    Animation(sf::RenderWindow& window): window(window){};

    void show_desk(){
        sf::Texture texture;
        texture.loadFromFile("/home/dmitriy/CLionProjects/Gwint/Doska_dlya_gvinta.png");
        sf::Sprite sprite(texture);
        float scale_x = window.getSize().x/sprite.getLocalBounds().width;
        float scale_y = window.getSize().y/sprite.getLocalBounds().height;
        sprite.setScale(scale_x, scale_y);
        window.draw(sprite);
    }

    void show_line_of_cards(std::vector<Card>& cards, float start_x, float end_x, float y, bool is_choosable){
        std::vector<sf::Sprite> res;
        float scale_x = window.getSize().x / window_basic_width;
        float scale_y = window.getSize().y / window_basic_height;
        float cur_x = start_x;
        float delta_x = (end_x - start_x - card_width*scale_x)/(cards.size()-1);
        for(size_t i = 0; i < cards.size(); ++i){
            sf::Texture texture;
            texture.loadFromFile(cards[i].filename_of_image);
            sf::Sprite sprite(texture);
            sprite.setScale(scale_x, scale_y);
            sprite.setPosition(cur_x, y);
            cur_x+=delta_x;
            sf::Text text;
            text.setString(std::to_string(cards[i].amount_of_strength_now));
            text.setScale(strength_text_basic_scale_x * scale_x, strength_text_basic_scale_y * scale_y);
            text.setPosition(cur_x + strength_text_delta_x * scale_x, y + strength_text_delta_y * scale_y);
            window.draw(sprite);
            window.draw(text);
            if(is_choosable) res.push_back(sprite);
        }
        if(is_choosable) choosable_cards = res;
    }

    size_t choose_card(std::vector<Card>& cards){
        float scale_x = window.getSize().x / window_basic_width;
        float scale_y = window.getSize().y / window_basic_height;
        show_line_of_cards(cards, choosable_basic_start_x*scale_x, choosable_basic_end_x*scale_x, choosable_basic_y*scale_y, true);
        now_choosing = true;
        chosen = -1;
        while(chosen == -1){
        }
        now_choosing = false;
        return chosen;
    }

    void wait_next_player(){
        waiting_next_player = true;
        sf::Text text;
        text.setString("Is next player ready?");
        text.setPosition(window.getSize().x/2, window.getSize().y/2);
        window.draw(text);
        now_choosing = true;
        chosen = -1;
        while(chosen == -1){
        }
        now_choosing = false;
        waiting_next_player = false;
    }

    void redraw_board(Game& game) {
        show_line_of_cards(game.now_moving().desk.strength_melee, strength_cards_left_coordinate,
                           strength_cards_right_coordinate, close_melee_basic_up, false);
        show_line_of_cards(game.now_moving().desk.strength_archer, strength_cards_left_coordinate,
                           strength_cards_right_coordinate, close_archer_basic_up, false);
        show_line_of_cards(game.now_moving().desk.strength_siege, strength_cards_left_coordinate,
                           strength_cards_right_coordinate, close_siege_basic_up, false);
        show_line_of_cards(game.not_now_moving().desk.strength_melee, strength_cards_left_coordinate,
                           strength_cards_right_coordinate, remote_melee_basic_up, false);
        show_line_of_cards(game.not_now_moving().desk.strength_archer, strength_cards_left_coordinate,
                           strength_cards_right_coordinate, remote_archer_basic_up, false);
        show_line_of_cards(game.not_now_moving().desk.strength_siege, strength_cards_left_coordinate,
                           strength_cards_right_coordinate, remote_siege_basic_up, false);

        show_line_of_cards(game.weather_manager.weather, weather_left_coordinate,
                           weather_right_coordinate), weather_y);

        show_line_of_cards(game.now_moving().desk.buff_melee, buff_cards_left_coordinate,
                           buff_cards_right_coordinate, close_buff_melee_basic_up, false);
        show_line_of_cards(game.now_moving().desk.buff_archer, buff_cards_left_coordinate,
                           buff_cards_right_coordinate, close_buff_archer_basic_up, false);
        show_line_of_cards(game.now_moving().desk.buff_siege, buff_cards_left_coordinate,
                           buff_cards_right_coordinate, close_buff_siege_basic_up, false);
        show_line_of_cards(game.not_now_moving().desk.buff_melee, buff_cards_left_coordinate,
                           buff_cards_right_coordinate, remote_buff_melee_basic_up, false);
        show_line_of_cards(game.not_now_moving().desk.buff_archer, buff_cards_left_coordinate,
                           buff_cards_right_coordinate, remote_buff_archer_basic_up, false);
        show_line_of_cards(game.not_now_moving().desk.buff_siege, buff_cards_left_coordinate,
                           buff_cards_right_coordinate, remote_buff_siege_basic_up, false);

    }

};

void main_cycle(Game& game){
    sf::RenderWindow window(sf::VideoMode(900, 600), "Gwint!");

    Animation animation(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::Resized)
            {
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
            }

            if(animation.now_choosing && event.type == sf::Event::KeyPressed){
                animation.chosen = event.key.code;
            }
        }

        window.clear();
        if(animation.waiting_next_player){
            animation.wait_next_player();
        }
        else{
            animation.redraw_board(game);
        }
        window.display();
    }
}
/* Amount of strength в Card, вызывать choosecard отдельно