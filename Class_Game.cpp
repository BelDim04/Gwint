#include "Class_Game.h"
#include "Class_Card.h"
#include<vector>
#include<string>
#include <typeinfo>

Player::Player(std::vector<Card> cards, bool is_bot) : is_bot(is_bot) {
    hand.reserve(amount_in_hand);
    deck.reserve(cards.size() - amount_in_hand);
    for (size_t i = 0; i < amount_in_hand; ++i) hand[i] = cards[i];
};

Weather_manager::Weather_manager() {
    weather = {};
    is_weather_bad_melee = false;
    is_weather_bad_archer = false;
    is_weather_bad_siege = false;
}

Game::Game(Player p1, Player p2, bool is_first_moving) : player1(p1), player2(p2), is_first_moving(is_first_moving) {}

bool Game::both_alive() {
    return player1_hp && player2_hp;
}

void Game::switch_turn() {
    is_first_moving = !is_first_moving;
}

Player& Game::now_moving() {
    if (is_first_moving) return player1;
    return player2;
}

std::string Game::str_now_moving() {
    if (is_first_moving) return "player1";
    return "player2";
}


Player& Game::not_now_moving() {
    if (is_first_moving) return player2;
    return player1;
}

std::string Game::str_not_now_moving() {
    if (is_first_moving) return "player2";
    return "player1";
}

std::vector<Card>& Game::find_vector(std::string where_lies) {
    if (where_lies == "player1_melee") return player1.desk.strength_melee;
    if (where_lies == "player1_archer") return player1.desk.strength_archer;
    if (where_lies == "player1_siege") return player1.desk.strength_siege;
    if (where_lies == "player2_melee") return player2.desk.strength_melee;
    if (where_lies == "player2_archer") return player2.desk.strength_archer;
    if (where_lies == "player2_siege") return player2.desk.strength_siege;
    if (where_lies == "weather") return weather_manager.weather;
}


void Game::recalculate() {
    for (int i = 0; i < now_moving().desk.strength_melee.size(); ++i) {
        int a = now_moving().desk.strength_melee[i].recalculate(*this);
        now_moving().sum_strength+=a;
        now_moving().melee_sum_strength+=a;
    }
    for (int i = 0; i < now_moving().desk.strength_archer.size(); ++i) {
        int a = now_moving().desk.strength_archer[i].recalculate(*this);;
        now_moving().sum_strength += a;
        now_moving().archer_sum_strength += a;
    }
    for (int i = 0; i < now_moving().desk.strength_siege.size(); ++i) {
        int a = now_moving().desk.strength_siege[i].recalculate(*this);
        now_moving().sum_strength += a;
        now_moving().siege_sum_strength += a;
    }
    for (int i = 0; i < not_now_moving().desk.strength_melee.size(); ++i) {
        int a = not_now_moving().desk.strength_melee[i].recalculate(*this);
        not_now_moving().sum_strength += a;
        not_now_moving().melee_sum_strength += a;
    }
    for (int i = 0; i < not_now_moving().desk.strength_archer.size(); ++i) {
        int a = not_now_moving().desk.strength_archer[i].recalculate(*this);
        not_now_moving().sum_strength += a;
        not_now_moving().archer_sum_strength += a;
    }
    for (int i = 0; i < not_now_moving().desk.strength_siege.size(); ++i) {
        int a = not_now_moving().desk.strength_siege[i].recalculate(*this);
        not_now_moving().sum_strength += a;
        not_now_moving().siege_sum_strength += a;
    }
}

std::vector<Card>& Game::find_weather() {
    return weather_manager.weather;
}

bool Game::is_weather_bad(std::string where_lies) {
    if ((where_lies == "player1_melee" || where_lies == "player2_melee") && find_weather_buffer("Cold") ||
        (where_lies == "player1_melee" || where_lies == "player2_melee") && find_weather_buffer("Rain") ||
        (where_lies == "player1_melee" || where_lies == "player2_melee") && find_weather_buffer("Hase"))
        return true;
    return false;
}

bool& Game::find_weather_buffer(std::string bad_weather) {
    if (bad_weather == "Cold") return weather_manager.is_weather_bad_melee;
    if (bad_weather == "Rain") return weather_manager.is_weather_bad_archer;
    if (bad_weather == "Haze") return weather_manager.is_weather_bad_siege;
}

bool Game::is_there_Doublebuff(std::string where_lies) {
    if (where_lies == "player1_melee") return player1.desk.buff_melee.size();
    if (where_lies == "player2_melee") return player2.desk.buff_melee.size();
    if (where_lies == "player1_archer") return player1.desk.buff_archer.size();
    if (where_lies == "player2_archer") return player1.desk.buff_archer.size();
    if (where_lies == "player1_siege") return player2.desk.buff_siege.size();
    if (where_lies == "player2_siege") return player1.desk.buff_siege.size();
}

void Game::play_round() {
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

size_t Game::choose_card() {
    //графический выбор карты
}

void Game::make_turn(size_t card_index, std::string destination) {
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

void Game::spy_move(int a, int b) {
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

void Game::healing_move(int a) {
    Card mv = now_moving().reset[a];
    now_moving().reset.erase(now_moving().reset.begin() + a);
    now_moving().hand.push_back(mv);
    //анимация переноса
}

std::pair<int&, int&> Game::find_buffer(std::string where_lies) {
    if (where_lies == "player1_melee") return { player1.desk.buff_manager.buff_by_one_melee, player1.desk.buff_manager.buff_in_two_melee };
    if (where_lies == "player2_melee") return { player2.desk.buff_manager.buff_by_one_melee, player2.desk.buff_manager.buff_in_two_melee };
    if (where_lies == "player1_archer") return { player1.desk.buff_manager.buff_by_one_archer, player1.desk.buff_manager.buff_in_two_archer };
    if (where_lies == "player2_archer") return { player2.desk.buff_manager.buff_by_one_archer, player2.desk.buff_manager.buff_in_two_archer };
    if (where_lies == "player1_siege") return { player1.desk.buff_manager.buff_by_one_siege, player1.desk.buff_manager.buff_in_two_siege };
    if (where_lies == "player2_siege") return { player2.desk.buff_manager.buff_by_one_siege, player2.desk.buff_manager.buff_in_two_siege };
}


//new functions:
int Game::now_moving_hp() {
    if(str_now_moving() == "player1") return player1_hp;
    else return player2_hp;
}

int Game::not_now_moving_hp() {
    if(str_not_now_moving() == "player1") return player1_hp;
    else return player2_hp;
}