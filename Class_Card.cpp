#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include "Class_Card.h"
#include "Class_Game.h"

void deletefunction(Game& game, Card* card) {
    int n = game.find_vector(card->where_lies).size();
    for(int i = 0; i < n; ++i) {
        if(game.find_vector(card->where_lies)[i]->name == card->name) {
            game.find_vector(card->where_lies).erase(game.find_vector(card->where_lies).begin()+i);
            break;
        }
    }
}

Card::Card(std::string Name, std::string Filename_of_image, int Amount_of_strength_now) :
    name(Name), filename_of_image(Filename_of_image) , amount_of_strength_now(Amount_of_strength_now){}

void Card::set_where_lies(Game &game) {

}

void Card::bot_set_where_lies(Game &game) {

}

void Card::use_special_ability(Game &game) {

}

int Card::recalculate(Game &game) {
    return 0;
}

void Card::delete_card(Game &game) {

}
//......................................................................................Силовые карты.....................................................................................//

Strength_card::Strength_card(int Amount_of_strength, bool Can_be_changed,
                             std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
        Card(Name, Filename_of_image, amount_of_strength_now),
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

void Strength_card::delete_card(Game &game) {
    Card::delete_card(game);
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

void Usual_card::delete_card(Game &game) {
    deletefunction(game, this);
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
    std::vector<Card*>& deck = game.now_moving().deck;
    int a = rand() % deck.size();
    int b = rand() % deck.size();
    if(deck.size() <= 1) return;
    while (a == b)  b = rand() % deck.size();
    game.spy_move(a, b);
}

void Spy_card::delete_card(Game &game) {
    deletefunction(game, this);
}

Delete_card::Delete_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image,
                         std::string Type_of_weapon)  :
        Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

void Delete_card::set_where_lies(Game& game) {
    where_lies = game.str_now_moving();
    where_lies += "_";
    where_lies += (type_of_weapon);
}

void Delete_card::bot_set_where_lies(Game &game) {
    set_where_lies(game);
}

void Delete_card::use_special_ability(Game &game) {
    int max1 = -1, max2 = -1, max3 = -1;
    int ind1 = -1, ind2 = -1, ind3 = -1;

    for(int i = 0; i < game.not_now_moving().desk.strength_melee.size(); ++i) {
        if(game.not_now_moving().desk.strength_melee[i]->amount_of_strength_now > max1) {
            ind1 = i;
            max1 = game.not_now_moving().desk.strength_melee[i]->amount_of_strength_now;
        }
    }

    for(int i = 0; i < game.not_now_moving().desk.strength_archer.size(); ++i) {
        if(game.not_now_moving().desk.strength_archer[i]->amount_of_strength_now > max1) {
            ind2 = i;
            max2 = game.not_now_moving().desk.strength_archer[i]->amount_of_strength_now;
        }
    }

    for(int i = 0; i < game.not_now_moving().desk.strength_siege.size(); ++i) {
        if(game.not_now_moving().desk.strength_siege[i]->amount_of_strength_now > max1) {
            ind3 = i;
            max3 = game.not_now_moving().desk.strength_siege[i]->amount_of_strength_now;
        }
    }
    if(ind1 == -1 && ind2 == -1 && ind3 == -1) return;
    else {
        if(max1 >= max2 && max1>=max3) {
            deletefunction(game, game.not_now_moving().desk.strength_melee[ind1]);
        }
        else if(max2 >= max1 && max2 >= max3) {
            deletefunction(game, game.not_now_moving().desk.strength_archer[ind2]);
        }
        else {
            deletefunction(game, game.not_now_moving().desk.strength_siege[ind3]);
        }
    }
}

void Delete_card::delete_card(Game &game) {
    deletefunction(game, this);
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
    std::vector<Card*>& reset = game.now_moving().reset;
    if (reset.size()) {
        int a = rand() % reset.size();
        game.healing_move(a);
    }
}

void Healing_card::delete_card(Game &game) {
    deletefunction(game, this);
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

void One_increase_card::delete_card(Game &game) {
    deletefunction(game, this);
    std::pair<int&, int&> buffers = game.find_buffer(where_lies);
    buffers.first -= 1;
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

void Double_increase_card::delete_card(Game &game) {
    deletefunction(game, this);
    std::pair<int&, int&> buffers = game.find_buffer(where_lies);
    buffers.second /= 1;
}

//......................................................................................погодные карты.....................................................................................//
Weather_card::Weather_card(std::string Name, std::string Filename_of_image) : Card(Name, Filename_of_image, -1) {};

void Weather_card::use_special_ability(Game& game){

}
void Weather_card::set_where_lies(Game& game){

}

void Weather_card::bot_set_where_lies(Game &game) {
    Card::bot_set_where_lies(game);
}

void Weather_card::delete_card(Game &game) {
    Card::delete_card(game);
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

void Cold_card::delete_card(Game &game) {
    bool& is_weather_bad = game.find_weather_buffer("Cold");
    is_weather_bad = false;
    deletefunction(game, this);
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

void Rain_card::delete_card(Game &game) {
    bool& is_weather_bad = game.find_weather_buffer("Rain");
    is_weather_bad = false;
    deletefunction(game, this);
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

void Haze_card::delete_card(Game &game) {
    bool& is_weather_bad = game.find_weather_buffer("Haze");
    is_weather_bad = false;
    deletefunction(game, this);
}

Good_weather_card::Good_weather_card(std::string Filename_of_image) : Weather_card("Bright Day", Filename_of_image) {};

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

void Good_weather_card::delete_card(Game &game) {

}

//......................................................................................Особые карты.....................................................................................//

Double_buff_card::Double_buff_card(std::string Filename_of_image) : Card("Command Horn", Filename_of_image, -1) {};


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

void Double_buff_card::delete_card(Game &game) {
    deletefunction(game, this);
}