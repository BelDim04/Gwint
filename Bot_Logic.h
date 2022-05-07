#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "Class_Game.h"
#include "Class_Card.h"

class Bot_logic {
public:
    bool will_lose_if_pass(Game &game) {
        return (game.now_moving_hp() <= 1);
    }

    bool is_card_weather(std::string &name) {
        if (name == "Bright Day" ||
            name == "Cold" ||
            name == "Rain" ||
            name == "Haze")
            return true;
        return false;
    }

    int assume_sum_strength_of_bot(Game &game) {
        Game copy(game.player1, game.player2, game.is_first_moving);
        int i = 0;
        while (i < copy.now_moving().hand.size()) {
            if (copy.now_moving().hand[i]->name != "Command Horn" || is_card_weather(copy.now_moving().hand[i]->name)) {
                copy.now_moving().hand[i]->bot_set_where_lies(copy);
                copy.make_turn(i);
            } else {
                ++i;
            }
            //теперь решить как расставить погоду, легкий вариант-никак, тяжелый-надо подумать
            // на самом деле, стоит ли этот кусок кода того?
            //думаю нет
        }
        return copy.now_moving().sum_strength;
    };

    int find_useless_card(Game &game) {
        for (int i = 0; i < game.now_moving().hand.size(); ++i) {
            if (game.now_moving().hand[i]->amount_of_strength_now != -1 &&
                game.now_moving().hand[i]->amount_of_strength_now <= 4)
                return i;
        }
        return -1;
    }

    bool should_bot_pass(Game &game) {
        if (will_lose_if_pass(game)) return false;
        int assume_sum_strength_of_human = 4 * game.not_now_moving().hand.size();
        if (assume_sum_strength_of_human + game.not_now_moving().sum_strength > assume_sum_strength_of_bot(game)) {
            return true;
        }
        if (game.now_moving().hand.size() * 2 < game.not_now_moving().hand.size() * 3) {
            if (find_useless_card(game) != -1) {
                return false;
            }
            return true;
        }
        return true;
    }

    int bot_choose_card(Game &game) {
        std::vector<Card *> &hand = game.now_moving().hand;
        //простая версия
        //идея-для каждой карты смотрим как изменится баланс сил, и большее изменение - это то, что возвращаем
        //Game copy = game;
        int maxdif = 0;
        int dif;
        int res;
        //Еслм карта-шпион, надо класть её, но нужна проверка на то, является ли карта шпионом
        for (int i = 0; i < game.now_moving().hand.size(); ++i) {
            //сделать ход
            Game copy = game;//не сработает
            dif = (game.now_moving().sum_strength - game.not_now_moving().sum_strength) -
                  (copy.now_moving().sum_strength - game.not_now_moving().sum_strength);
            if (dif < 0 && !is_card_weather(game.now_moving().hand[i]->name)) {
                return i;
            } else if (dif > maxdif) {
                maxdif = dif;
                res = i;
            }

        }
        return res;
        //если карта не погода и maxdif < 0, то кладём её
    }

    void bot_move(Game &game) {//check
        if (should_bot_pass(game)) {
            game.now_moving().has_fold = true;
            game.switch_turn();
            return;
        } else if (game.now_moving().hand.size() * 2 < game.not_now_moving().hand.size() * 3) {
            int k = find_useless_card(game);
            game.now_moving().hand[k]->bot_set_where_lies(game);
            game.make_turn(k);
        } else {
            int k = bot_choose_card(game);
            if (k == -1) {
                game.now_moving().has_fold = true;
                return;
            }
            game.now_moving().hand[k]->bot_set_where_lies(game);
            game.make_turn(k);
        }
    }
};
