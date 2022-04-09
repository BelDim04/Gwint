#pragma once
#include "Class_Player.cpp"
#include "Class_Desk.cpp"
#include "Class_Card.cpp"
#include<vector>
#include<string>
#include <typeinfo>

class Game {
public:
    Player player1;
    Player player2;
    int player1_hp = 2;
    int player2_hp = 2;
    bool is_first_moving;
    Weather_manager weather_manager;

    Game(Player p1, Player p2, bool is_first_moving) : player1(p1), player2(p2), is_first_moving(is_first_moving) {};

    bool both_alive() {
        return player1_hp && player2_hp;
    }

    void switch_turn() {
        is_first_moving = !is_first_moving;
    }

    Player& now_moving() {
        if (is_first_moving) return player1;
        return player2;
    }

    std::string str_now_moving() {
        if (is_first_moving) return "player1";
        return "player2";
    }


    Player& not_now_moving() {
        if (is_first_moving) return player2;
        return player1;
    }

    std::string str_not_now_moving() {
        if (is_first_moving) return "player2";
        return "player1";
    }

    std::vector<Card>& find_vector(std::string where_lies) {
        if (where_lies == "player1_melee") return player1.desk.strength_melee;
        if (where_lies == "player1_archer") return player1.desk.strength_archer;
        if (where_lies == "player1_siege") return player1.desk.strength_siege;
        if (where_lies == "player2_melee") return player2.desk.strength_melee;
        if (where_lies == "player2_archer") return player2.desk.strength_archer;
        if (where_lies == "player2_siege") return player2.desk.strength_siege;
    }

    void recalculate() {
        player1.sum_strength = 0;
        player2.sum_strength = 0;
        for (int i = 0; i < now_moving().desk.buff_melee.size(); ++i) {
            now_moving().sum_strength += now_moving().desk.buff_melee[i].recalculate(*this);
        }
        for (int i = 0; i < now_moving().desk.buff_archer.size(); ++i) {
            now_moving().sum_strength += now_moving().desk.buff_archer[i].recalculate(*this);
        }
        for (int i = 0; i < now_moving().desk.buff_siege.size(); ++i) {
            now_moving().sum_strength += now_moving().desk.buff_siege[i].recalculate(*this);
        }
        for (int i = 0; i < now_moving().desk.strength_melee.size(); ++i) {
            not_now_moving().sum_strength += not_now_moving().desk.strength_melee[i].recalculate(*this);
        }
        for (int i = 0; i < now_moving().desk.strength_archer.size(); ++i) {
            not_now_moving().sum_strength += not_now_moving().desk.strength_archer[i].recalculate(*this);
        }
        for (int i = 0; i < now_moving().desk.strength_siege.size(); ++i) {
            not_now_moving().sum_strength += not_now_moving().desk.strength_siege[i].recalculate(*this);
        }
    }

    std::vector<Card>& find_weather() {
        return weather_manager.weather;
    }

    bool is_weather_bad(std::string where_lies) {
        if ((where_lies == "player1_melee" || where_lies == "player2_melee") && find_weather_buffer("Cold") ||
            (where_lies == "player1_melee" || where_lies == "player2_melee") && find_weather_buffer("Rain") ||
            (where_lies == "player1_melee" || where_lies == "player2_melee") && find_weather_buffer("Hase"))
            return true;
        return false;
    }

    bool& find_weather_buffer(std::string bad_weather) {
        if (bad_weather == "Cold") return weather_manager.is_weather_bad_melee;
        if (bad_weather == "Rain") return weather_manager.is_weather_bad_archer;
        if (bad_weather == "Haze") return weather_manager.is_weather_bad_siege;
    }

    bool is_there_Doublebuff(std::string where_lies) {
        if (where_lies == "player1_melee") return player1.desk.buff_melee.size();
        if (where_lies == "player2_melee") return player2.desk.buff_melee.size();
        if (where_lies == "player1_archer") return player1.desk.buff_archer.size();
        if (where_lies == "player2_archer") return player1.desk.buff_archer.size();
        if (where_lies == "player1_siege") return player2.desk.buff_siege.size();
        if (where_lies == "player2_siege") return player1.desk.buff_siege.size();
    }

    void play_round() {
        bool is_first_moving_next_round = !is_first_moving;
        while (!(player1.has_fold && player2.has_fold)) {
            if (now_moving().has_fold) {
                is_first_moving = !is_first_moving;
                continue;
            }
            size_t card_index;
            std::string destination;
            if (now_moving().is_bot) {
                //Boooot
            }
            else {
                card_index = choose_card();
                now_moving().hand[card_index].set_where_lies(*this);
                std::string destination = now_moving().hand[card_index].where_lies;
            }
            make_turn(card_index, destination);
            now_moving().hand[card_index].use_special_ability(*this);
            recalculate();
            is_first_moving = !is_first_moving;
        }
        //запустить анимацию после пересчёта

        if (player1.sum_strength <= player2.sum_strength) player1_hp--;
        if (player2.sum_strength <= player1.sum_strength) player2_hp--;
    }

    size_t choose_card() {
        //графический выбор карты
    }

    void make_turn(size_t card_index, std::string destination) {
        Card card = now_moving().hand[card_index];
        now_moving().hand.erase(now_moving().hand.begin() + card_index);
        if (destination == "player1_buff_melee") player1.desk.buff_melee.push_back(card);
        else if (destination == "player1_buff_archer") player1.desk.buff_archer.push_back(card);
        else if (destination == "player1_buff_siege") player1.desk.buff_siege.push_back(card);
        else if (destination == "player1_melee") player1.desk.strength_melee.push_back(card);
        else if (destination == "player1_archer") player1.desk.strength_archer.push_back(card);
        else if (destination == "player1_siege") player1.desk.strength_siege.push_back(card);
        else if (destination == "player1_buff_melee") player2.desk.buff_melee.push_back(card);
        else if (destination == "player1_buff_archer") player2.desk.buff_archer.push_back(card);
        else if (destination == "player1_buff_siege") player2.desk.buff_siege.push_back(card);
        else if (destination == "player1_melee") player2.desk.strength_melee.push_back(card);
        else if (destination == "player1_archer") player2.desk.strength_archer.push_back(card);
        else if (destination == "player1_siege") player2.desk.strength_siege.push_back(card);
        else if (destination == "weather") weather_manager.weather.push_back(card);
        //анимация броска карты
    }

    void spy_move(int a, int b) {
        Card mv_f = now_moving().deck[a];
        Card mv_s = now_moving().deck[b];
        if (a > b) {
            now_moving().deck.erase(now_moving().deck.begin() + a);
            now_moving().deck.erase(now_moving().deck.begin() + b);
        }
        else {
            now_moving().deck.erase(now_moving().deck.begin() + b);
            now_moving().deck.erase(now_moving().deck.begin() + a);
        }
        now_moving().hand.push_back(mv_f);
        now_moving().hand.push_back(mv_s);
        //анимация переноса
    }

    void healing_move(int a) {
        Card mv = now_moving().reset[a];
        now_moving().reset.erase(now_moving().reset.begin() + a);
        now_moving().hand.push_back(mv);
        //анимация переноса
    }

    std::pair<int&, int&> find_buffer(std::string where_lies) {
        if (where_lies == "player1_melee") return { player1.desk.buff_manager.buff_by_one_melee, player1.desk.buff_manager.buff_in_two_melee };
        if (where_lies == "player2_melee") return { player2.desk.buff_manager.buff_by_one_melee, player2.desk.buff_manager.buff_in_two_melee };
        if (where_lies == "player1_archer") return { player1.desk.buff_manager.buff_by_one_archer, player1.desk.buff_manager.buff_in_two_archer };
        if (where_lies == "player2_archer") return { player2.desk.buff_manager.buff_by_one_archer, player2.desk.buff_manager.buff_in_two_archer };
        if (where_lies == "player1_siege") return { player1.desk.buff_manager.buff_by_one_siege, player1.desk.buff_manager.buff_in_two_siege };
        if (where_lies == "player2_siege") return { player2.desk.buff_manager.buff_by_one_siege, player2.desk.buff_manager.buff_in_two_siege };
    }


};

class Weather_manager {
public:
    std::vector<Card> weather;
    bool is_weather_bad_melee;
    bool is_weather_bad_archer;
    bool is_weather_bad_siege;
};