#include<iostream>
#include<vector>

class Card;

class Buff_manager {
public:
    int buff_by_one_melee;
    int buff_by_one_archer;
    int buff_by_one_siege;
    int buff_in_two_melee;
    int buff_in_two_archer;
    int buff_in_two_siege;
};

class Desk {
public:
    std::vector<Card*> buff_melee;
    std::vector<Card*> buff_archer;
    std::vector<Card*> buff_siege;
    std::vector<Card*> strength_melee;
    std::vector<Card*> strength_archer;
    std::vector<Card*> strength_siege;
    Buff_manager buff_manager;
};


class Player {
public:
    static const size_t amount_in_hand = 3;
    std::vector<Card*> hand;
    std::vector<Card*> reset;
    std::vector<Card*> deck;
    Desk desk;
    const bool is_bot;
    //type_of_fraction
    int sum_strength = 0;
    int melee_sum_strength = 0;
    int archer_sum_strength = 0;
    int siege_sum_strength = 0;
    bool has_fold = false;
    int hp = 2;
    Player(std::vector<Card*> cards, bool is_bot);

};

class Weather_manager {
public:
    std::vector<Card*> weather;
    bool is_weather_bad_melee;
    bool is_weather_bad_archer;
    bool is_weather_bad_siege;
    Weather_manager();
};

class Game {
public:
    Player player1;
    Player player2;
    bool is_first_moving;
    bool is_first_start_round;
    Weather_manager weather_manager;

    Game(Player p1, Player p2, bool is_first_moving);

    bool is_game_ended();
    void switch_turn();
    Player& now_moving();
    std::string str_now_moving();
    Player& not_now_moving();
    std::string str_not_now_moving();

    std::vector<Card*>& find_vector(std::string where_lies);
    void recalculate();

    std::vector<Card*>& find_weather();

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

