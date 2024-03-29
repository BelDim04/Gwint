#pragma once
#include<iostream>
#include<vector>
#include<memory>

class Card;

class Buff_manager {
public:
    int buff_by_one_melee = 0;
    int buff_by_one_archer = 0;
    int buff_by_one_siege = 0;
    int buff_in_two_melee = 1;
    int buff_in_two_archer = 1;
    int buff_in_two_siege = 1;
};

class Desk {
public:
    std::vector<std::shared_ptr<Card>> buff_melee;
    std::vector<std::shared_ptr<Card>> buff_archer;
    std::vector<std::shared_ptr<Card>> buff_siege;
    std::vector<std::shared_ptr<Card>> strength_melee;
    std::vector<std::shared_ptr<Card>> strength_archer;
    std::vector<std::shared_ptr<Card>> strength_siege;
    Buff_manager buff_manager;
};


class Player {
public:
    static const size_t amount_in_hand = 6;
    std::vector<std::shared_ptr<Card>> hand;
    std::vector<std::shared_ptr<Card>> drop;
    std::vector<std::shared_ptr<Card>> deck;
    Desk desk;
    bool is_bot;
    //type_of_fraction
    int sum_strength = 0;
    int melee_sum_strength = 0;
    int archer_sum_strength = 0;
    int siege_sum_strength = 0;
    bool has_fold = false;
    int hp = 2;
    Player(std::vector<std::shared_ptr<Card>> cards, bool is_bot);
    Player();
    Player& operator=(Player p2) {
        hand.clear();
        deck.clear();
        desk.strength_archer.clear();
        desk.strength_melee.clear();
        desk.strength_siege.clear();
        desk.buff_archer.clear();
        desk.buff_melee.clear();
        desk.buff_siege.clear();
        is_bot = p2.is_bot;
        for(int i = 0; i < p2.hand.size(); ++i) {
            hand.push_back(p2.hand[i]);
        }
        for(int i = 0; i < p2.deck.size(); ++i) {
            deck.push_back(p2.deck[i]);
        }
        for(int i = 0; i < p2.desk.strength_archer.size(); ++i) {
            desk.strength_archer.push_back(p2.desk.strength_archer[i]);
        }
        for(int i = 0; i < p2.desk.strength_melee.size(); ++i) {
            desk.strength_melee.push_back(p2.desk.strength_melee[i]);
        }
        for(int i = 0; i < p2.desk.strength_archer.size(); ++i) {
            desk.strength_siege.push_back(p2.desk.strength_siege[i]);
        }
        for(int i = 0; i < p2.desk.buff_archer.size(); ++i) {
            desk.buff_archer.push_back(p2.desk.buff_archer[i]);
        }
        for(int i = 0; i < p2.desk.buff_melee.size(); ++i) {
            desk.buff_melee.push_back(p2.desk.buff_melee[i]);
        }
        for(int i = 0; i < p2.desk.buff_archer.size(); ++i) {
            desk.buff_siege.push_back(p2.desk.buff_siege[i]);
        }
    }
    void clear();
    void reset();
};

class Weather_manager {
public:
    std::vector<std::shared_ptr<Card>> weather;
    bool is_weather_bad_melee;
    bool is_weather_bad_archer;
    bool is_weather_bad_siege;
    Weather_manager();
    void clear();
};

class Game {
public:
    Player player1;
    Player player2;
    bool is_first_moving;
    bool is_first_start_round;
    Weather_manager weather_manager;

    Game(Player p1, Player p2, bool is_first_moving);
    Game(bool is_first_moving);

    bool is_game_ended();
    void switch_turn();
    Player& now_moving();
    std::string str_now_moving();
    Player& not_now_moving();
    std::string str_not_now_moving();

    std::vector<std::shared_ptr<Card>>& find_vector(std::string where_lies);
    void recalculate();

    std::vector<std::shared_ptr<Card>>& find_weather();

    bool is_weather_bad(std::string where_lies);

    bool& find_weather_buffer(std::string bad_weather);

    bool is_there_Doublebuff(std::string where_lies);

    void play_round();

    size_t choose_card();

    void move_card(size_t card_index, std::string destination);

    void spy_move(int a, int b);

    void healing_move(int a);

    std::pair<int&, int&> find_buffer(std::string where_lies);

    //new functions
    int now_moving_hp();
    int not_now_moving_hp();

    void make_turn(size_t n);

    bool is_round_ended();

    void on_round_ended();

    void on_game_ended();
};

