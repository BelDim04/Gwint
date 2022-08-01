#include "Class_Game.h"
#include "Class_Card.h"
#include<vector>
#include<string>
#include <typeinfo>
#include <algorithm>
#include <time.h>

Player::Player(std::vector<std::shared_ptr<Card>> cards, bool is_bot) : is_bot(is_bot) {
    if(!cards.empty()) {
        srand(time(0));
        for(int i = 0; i < cards.size(); ++i) {
            int rnd = rand() % (cards.size() - 1);
            std::swap(cards[i], cards[rnd]);
        }
        for (size_t i = 0; i < amount_in_hand; ++i) {
            hand.push_back(cards[i]);
        }
        for (size_t i = 0; i < cards.size() - amount_in_hand; ++i) {
            deck.push_back(cards[i + amount_in_hand]);
        }
    }
}

void Player::clear() {
    sum_strength = 0;
    melee_sum_strength = 0;
    archer_sum_strength = 0;
    siege_sum_strength = 0;
    drop.insert(drop.end(), desk.buff_archer.begin(), desk.buff_archer.end());
    desk.buff_archer.clear();
    drop.insert(drop.end(), desk.buff_melee.begin(), desk.buff_melee.end());
    desk.buff_melee.clear();
    drop.insert(drop.end(), desk.buff_siege.begin(), desk.buff_siege.end());
    desk.buff_siege.clear();
    drop.insert(drop.end(), desk.strength_melee.begin(), desk.strength_melee.end());
    desk.strength_melee.clear();
    drop.insert(drop.end(), desk.strength_archer.begin(), desk.strength_archer.end());
    desk.strength_archer.clear();
    drop.insert(drop.end(), desk.strength_siege.begin(), desk.strength_siege.end());
    desk.strength_siege.clear();
}

void Player::reset() {
    hand.clear();
    deck.clear();
    drop.clear();
    hp = 2;
    is_bot = false;
}

Player::Player() = default;

Weather_manager::Weather_manager() {
    weather = {};
    is_weather_bad_melee = false;
    is_weather_bad_archer = false;
    is_weather_bad_siege = false;
}

void Weather_manager::clear() {
    weather.clear();
    is_weather_bad_archer = false;
    is_weather_bad_melee = false;
    is_weather_bad_siege = false;
}

Game::Game(Player p1, Player p2, bool is_first_moving) : player1(p1), player2(p2), is_first_moving(is_first_moving), is_first_start_round(is_first_moving) {}

bool Game::is_game_ended() {
    return !player1.hp || !player2.hp;
}

void Game::switch_turn() {
    if(!not_now_moving().has_fold) is_first_moving = !is_first_moving;
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

std::vector<std::shared_ptr<Card>>& Game::find_vector(std::string where_lies) {
    if (where_lies == "player1_melee") return player1.desk.strength_melee;
    if (where_lies == "player1_archer") return player1.desk.strength_archer;
    if (where_lies == "player1_siege") return player1.desk.strength_siege;
    if (where_lies == "player2_melee") return player2.desk.strength_melee;
    if (where_lies == "player2_archer") return player2.desk.strength_archer;
    if (where_lies == "player2_siege") return player2.desk.strength_siege;
    if (where_lies == "weather") return weather_manager.weather;
}


void Game::recalculate() {
    now_moving().sum_strength = 0;
    now_moving().melee_sum_strength = 0;
    now_moving().archer_sum_strength = 0;
    now_moving().siege_sum_strength = 0;
    not_now_moving().sum_strength = 0;
    not_now_moving().melee_sum_strength = 0;
    not_now_moving().archer_sum_strength = 0;
    not_now_moving().siege_sum_strength = 0;
    for (int i = 0; i < now_moving().desk.strength_melee.size(); ++i) {
        int a = now_moving().desk.strength_melee[i]->recalculate(*this);
        now_moving().sum_strength+=a;
        now_moving().melee_sum_strength+=a;
    }
    for (int i = 0; i < now_moving().desk.strength_archer.size(); ++i) {
        int a = now_moving().desk.strength_archer[i]->recalculate(*this);;
        now_moving().sum_strength += a;
        now_moving().archer_sum_strength += a;
    }
    for (int i = 0; i < now_moving().desk.strength_siege.size(); ++i) {
        int a = now_moving().desk.strength_siege[i]->recalculate(*this);
        now_moving().sum_strength += a;
        now_moving().siege_sum_strength += a;
    }
    for (int i = 0; i < not_now_moving().desk.strength_melee.size(); ++i) {
        int a = not_now_moving().desk.strength_melee[i]->recalculate(*this);
        not_now_moving().sum_strength += a;
        not_now_moving().melee_sum_strength += a;
    }
    for (int i = 0; i < not_now_moving().desk.strength_archer.size(); ++i) {
        int a = not_now_moving().desk.strength_archer[i]->recalculate(*this);
        not_now_moving().sum_strength += a;
        not_now_moving().archer_sum_strength += a;
    }
    for (int i = 0; i < not_now_moving().desk.strength_siege.size(); ++i) {
        int a = not_now_moving().desk.strength_siege[i]->recalculate(*this);
        not_now_moving().sum_strength += a;
        not_now_moving().siege_sum_strength += a;
    }
}

std::vector<std::shared_ptr<Card>>& Game::find_weather() {
    return weather_manager.weather;
}

bool Game::is_weather_bad(std::string where_lies) {
    if ((where_lies == "player1_melee" || where_lies == "player2_melee") && find_weather_buffer("Cold") ||
        (where_lies == "player1_archer" || where_lies == "player2_archer") && find_weather_buffer("Rain") ||
        (where_lies == "player1_siege" || where_lies == "player2_siege") && find_weather_buffer("Haze"))
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
            now_moving().hand[card_index]->set_where_lies(*this);
            std::string destination = now_moving().hand[card_index]->where_lies;
        }
        move_card(card_index, destination);
        now_moving().hand[card_index]->use_special_ability(*this);
        recalculate();
        is_first_moving = !is_first_moving;
    }
    //запустить анимацию после пересчёта

    if (player1.sum_strength <= player2.sum_strength) player1.hp--;
    if (player2.sum_strength <= player1.sum_strength) player2.hp--;
}

size_t Game::choose_card() {
    //графический выбор карты
}

void Game::move_card(size_t card_index, std::string destination) {
    std::shared_ptr<Card> card = now_moving().hand[card_index];
    now_moving().hand.erase(now_moving().hand.begin() + card_index);
    if (destination == "player1_buff_melee") player1.desk.buff_melee.push_back(card);
    else if (destination == "player1_buff_archer") player1.desk.buff_archer.push_back(card);
    else if (destination == "player1_buff_siege") player1.desk.buff_siege.push_back(card);
    else if (destination == "player1_melee") player1.desk.strength_melee.push_back(card);
    else if (destination == "player1_archer") player1.desk.strength_archer.push_back(card);
    else if (destination == "player1_siege") player1.desk.strength_siege.push_back(card);
    else if (destination == "player2_buff_melee") player2.desk.buff_melee.push_back(card);
    else if (destination == "player2_buff_archer") player2.desk.buff_archer.push_back(card);
    else if (destination == "player2_buff_siege") player2.desk.buff_siege.push_back(card);
    else if (destination == "player2_melee") player2.desk.strength_melee.push_back(card);
    else if (destination == "player2_archer") player2.desk.strength_archer.push_back(card);
    else if (destination == "player2_siege") player2.desk.strength_siege.push_back(card);
    else if (destination == "weather") weather_manager.weather.push_back(card);
    //анимация броска карты
}

void Game::spy_move(int a, int b) {
    std::shared_ptr<Card> mv_f = now_moving().deck[a];
    std::shared_ptr<Card> mv_s = now_moving().deck[b];
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
    std::shared_ptr<Card> mv = now_moving().drop[a];
    now_moving().drop.erase(now_moving().drop.begin() + a);
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
    if(str_now_moving() == "player1") return player1.hp;
    else return player2.hp;
}

int Game::not_now_moving_hp() {
    if(str_not_now_moving() == "player1") return player1.hp;
    else return player2.hp;
}

void Game::make_turn(size_t n) {
    now_moving().hand[n]->set_where_lies(*this);
    std::string destination = now_moving().hand[n]->where_lies;
    now_moving().hand[n]->use_special_ability(*this);
    move_card(n, destination);
    recalculate();
    switch_turn();
}

bool Game::is_round_ended() {
    return player1.has_fold && player2.has_fold;
}

void Game::on_round_ended() {
    if (player1.sum_strength <= player2.sum_strength) player1.hp--;
    if (player2.sum_strength <= player1.sum_strength) player2.hp--;
    player1.clear();
    player2.clear();
    player1.has_fold = false;
    player2.has_fold = false;
    is_first_moving = ! is_first_start_round;
    is_first_start_round = is_first_moving;
    player1.desk.buff_manager.buff_by_one_archer = 0;
    player1.desk.buff_manager.buff_by_one_melee = 0;
    player1.desk.buff_manager.buff_by_one_siege = 0;
    player1.desk.buff_manager.buff_in_two_archer = 1;
    player1.desk.buff_manager.buff_in_two_melee = 1;
    player1.desk.buff_manager.buff_in_two_siege = 1;
    player2.desk.buff_manager.buff_by_one_archer = 0;
    player2.desk.buff_manager.buff_by_one_melee = 0;
    player2.desk.buff_manager.buff_by_one_siege = 0;
    player2.desk.buff_manager.buff_in_two_archer = 1;
    player2.desk.buff_manager.buff_in_two_melee = 1;
    player2.desk.buff_manager.buff_in_two_siege = 1;
    weather_manager.clear();
}

void Game::on_game_ended() {
    on_round_ended();
    player1.reset();
    player2.reset();
}

Game::Game(bool is_first_moving): is_first_moving(is_first_moving), is_first_start_round(is_first_moving){};
