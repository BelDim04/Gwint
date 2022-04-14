#include<iostream>
#include<vector>
#include<string>
#include "Class_Card.h"
#include "Class_Game.h"

Card::Card(std::string Name, std::string Filename_of_image) : name(Name), filename_of_image(Filename_of_image) {}

void Card::set_where_lies(Game &game) {

}

void Card::bot_set_where_lies(Game &game) {

}

void Card::use_special_ability(Game &game) {

}

int Card::recalculate(Game &game) {
    return 0;
}
//......................................................................................Силовые карты.....................................................................................//

Strength_card::Strength_card(int Amount_of_strength, bool Can_be_changed,
                             std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
        Card(Name, Filename_of_image), amount_of_strength_now(Amount_of_strength),
        base_amount_of_strength(Amount_of_strength), can_be_changed(Can_be_changed), type_of_weapon(Type_of_weapon) {};

int Strength_card::recalculate(Game& game) {
    if (can_be_changed) {
    std::pair<int&, int&> buffers = game.find_buffer(where_lies);

    amount_of_strength_now += buffers.first;
    amount_of_strength_now *= buffers.second;
    basic_strength += buffers.first;
    basic_strength *= buffers.second;

    if (game.is_weather_bad(where_lies)) {//смотрим плохая ли погода
        amount_of_strength_now = basic_strength;
    }
    }
    return amount_of_strength_now;
}

void Strength_card::use_special_ability(Game &game) {
    Card::use_special_ability(game);
}

void Strength_card::set_where_lies(Game &game) {
    Card::set_where_lies(game);
}

void Strength_card::bot_set_where_lies(Game &game) {
    Card::bot_set_where_lies(game);
}


Usual_card::Usual_card(int Amount_of_strength, bool Can_be_changed,
                       std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
        Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

void Usual_card::use_special_ability(Game& game) {};

void Usual_card::set_where_lies(Game &game) {
    where_lies = game.str_now_moving();
    where_lies += "_";
    where_lies += (type_of_weapon);
}
void Usual_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

Spy_card::Spy_card(int Amount_of_strength, bool Can_be_changed, std::string Name,
                   std::string Filename_of_image, std::string Type_of_weapon) :
        Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

void Spy_card::set_where_lies(Game& game) {
    where_lies = game.str_not_now_moving();
    where_lies += "_";
    where_lies += (type_of_weapon);
}
void Spy_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

void Spy_card::use_special_ability(Game& game){
    //рандомно выбрать карты из колоды и добавить в руку
    std::vector<Card>& deck = game.now_moving().deck;
    int a = rand() % deck.size();
    int b = rand() % deck.size();
    while (a == b)  b = rand() % deck.size();
    game.spy_move(a, b);
}


Healing_card::Healing_card(int Amount_of_strength, bool Can_be_changed, std::string Name,
                           std::string Filename_of_image, std::string Type_of_weapon) :
        Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

void Healing_card::set_where_lies(Game& game) {
    where_lies = game.str_now_moving();
    where_lies += "_";
    where_lies += (type_of_weapon);
}
void Healing_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

void Healing_card::use_special_ability(Game& game) {
    //рандомно выбрать карту из сброса и добавить в руку
    std::vector<Card>& reset = game.now_moving().reset;
    if (reset.size()) {
        int a = rand() % reset.size();
        game.
        healing_move(a);
    }
}

One_increase_card::One_increase_card(int Amount_of_strength, bool Can_be_changed, std::string Name,
                                     std::string Filename_of_image, std::string Type_of_weapon) :
        Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

void One_increase_card::set_where_lies(Game& game) {
    where_lies = game.str_now_moving();
    where_lies += "_";
    where_lies += (type_of_weapon);
}
void One_increase_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

void One_increase_card::use_special_ability(Game& game) {
    std::pair<int&, int&> buffers = game.find_buffer(where_lies);
    buffers.first += 1;
}

Double_increase_card::Double_increase_card(int Amount_of_strength, bool Can_be_changed,
                                           std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
        Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

void Double_increase_card::set_where_lies(Game& game) {
    where_lies = game.str_now_moving();
    where_lies += "_";
    where_lies += (type_of_weapon);
}
void Double_increase_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

void Double_increase_card::use_special_ability(Game& game) {
    std::pair<int&, int&> buffers = game.find_buffer(where_lies);
    buffers.second *= 2;
}

//......................................................................................погодные карты.....................................................................................//
Weather_card::Weather_card(std::string Name, std::string Filename_of_image) : Card(Name, Filename_of_image) {};

void Weather_card::use_special_ability(Game& game){

}
void Weather_card::set_where_lies(Game& game){

}

void Weather_card::bot_set_where_lies(Game &game) {
    Card::bot_set_where_lies(game);
}

Cold_card::Cold_card(std::string Filename_of_image) : Weather_card("Cold", Filename_of_image) {};

void Cold_card::use_special_ability(Game& game) {
    bool& is_weather_bad = game.find_weather_buffer("Cold");
    if (!is_weather_bad) is_weather_bad = true;
}

void Cold_card::set_where_lies(Game& game) {
where_lies = "weather";
}
void Cold_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

Rain_card::Rain_card(std::string Filename_of_image) : Weather_card("Rain", Filename_of_image) {};

void Rain_card::use_special_ability(Game& game) {
    bool& is_weather_bad = game.find_weather_buffer("Rain");
    if (!is_weather_bad) is_weather_bad = true;
}

void Rain_card::set_where_lies(Game& game) {
where_lies = "weather";
}
void Rain_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

Haze_card::Haze_card(std::string Filename_of_image) : Weather_card("Haze", Filename_of_image) {};

void Haze_card::use_special_ability(Game& game) {
    bool& is_weather_bad = game.find_weather_buffer("Haze");
    if (!is_weather_bad) is_weather_bad = true;
}

void Haze_card::set_where_lies(Game& game) {
where_lies = "weather";
}
void Haze_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

Good_weather_card::Good_weather_card(std::string Filename_of_image) : Weather_card("Bright_day", Filename_of_image) {};

void Good_weather_card::use_special_ability(Game& game) {
    game.find_weather_buffer("Haze") = false;
    game.find_weather_buffer("Cold") = false;
    game.find_weather_buffer("Rain") = false;
    game.weather_manager.weather.clear();
    //запустить анимацию удаления карт
}

void Good_weather_card::set_where_lies(Game& game) {
    where_lies = "None";
}
void Good_weather_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

//......................................................................................Особые карты.....................................................................................//

Double_buff_card::Double_buff_card(std::string Filename_of_image) : Card("Command Horn", Filename_of_image) {};


void Double_buff_card::use_special_ability(Game& game) {
    //where_lies_copy - cоответствующее where_lies
    std::string where_lies_copy = where_lies;
    where_lies_copy.resize(8);
    if (where_lies[13] == 'm') where_lies_copy.append("melee");
    if (where_lies[13] == 'a') where_lies_copy.append("archer");
    if (where_lies[13] == 's') where_lies_copy.append("siege");
    std::pair<int&, int&> buffers = game.find_buffer(where_lies_copy);
    buffers.second *= 2;
}

void Double_buff_card::set_where_lies(Game& game) {
//а здесь происходит ввод, куда надо положить
//wheer_lies имеет вид playeri_buff_melee/archer/siege
}

void Double_buff_card::bot_set_where_lies(Game& game) {
    int t = std::max(game.now_moving().siege_sum_strength, game.now_moving().archer_sum_strength);
    t = std::max(game.now_moving().melee_sum_strength, t);
    if(t == game.now_moving().melee_sum_strength) {
        where_lies = "melee";
    }
    else if(t == game.now_moving().archer_sum_strength) {
        where_lies = "archer";
    }
    else {
        where_lies = "siege";
    }
}