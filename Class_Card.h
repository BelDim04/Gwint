#include<iostream>
#include<vector>
#include<string>

class Game;

class Card {
public:
    std::string name;
    std::string filename_of_image;
    std::string where_lies;
    Card(std::string Name, std::string Filename_of_image);
    virtual void set_where_lies(Game& game);//задаём куда кладём карту
    virtual void bot_set_where_lies(Game& game);//задаём куда кладём карту
    virtual void use_special_ability(Game& game);
    virtual int recalculate(Game& game);
    virtual void delete_card(Game& game);
};


class Strength_card : public Card {
public:
    int amount_of_strength_now;//у силовой карты есть текущая сила
    const int base_amount_of_strength;//у силовой карты есть изначальная сила
    int basic_strength = 1;//базовая сила-та сила, которая становится у карты при дебаффе
    const bool can_be_changed;//можно ли повлиять на карту
    std::string type_of_weapon;//melee, archer или siege

    Strength_card(int Amount_of_strength, bool Can_be_changed,
                  std::string Name, std::string Filename_of_image, std::string Type_of_weapon);

    //пересчёт - реализация
    int recalculate(Game& game);

    virtual void use_special_ability(Game& game);
    virtual void set_where_lies(Game& game);
    virtual void bot_set_where_lies(Game& game);
    virtual void delete_card(Game& game);
};

class Usual_card : public Strength_card {
public:

    Usual_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image,
               std::string Type_of_weapon);

    //Уникальная способность
    void use_special_ability(Game& game) override;

    //Куда положить
    void set_where_lies(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};


class Spy_card : public Strength_card {
public:

    Spy_card(int Amount_of_strength, bool Can_be_changed, std::string Name,
             std::string Filename_of_image, std::string Type_of_weapon);

    void set_where_lies(Game& game) override;
    void use_special_ability(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};

class Healing_card : public Strength_card {
public:

    Healing_card(int Amount_of_strength, bool Can_be_changed,
                 std::string Name, std::string Filename_of_image, std::string Type_of_weapon);

    void set_where_lies(Game& game) override;

    void use_special_ability(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};

class One_increase_card : public Strength_card {
public:

    One_increase_card(int Amount_of_strength, bool Can_be_changed,
                      std::string Name, std::string Filename_of_image, std::string Type_of_weapon);

    void set_where_lies(Game& game) override;

    void use_special_ability(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};

class Double_increase_card : public Strength_card {
public:

    Double_increase_card(int Amount_of_strength, bool Can_be_changed,
                         std::string Name, std::string Filename_of_image, std::string Type_of_weapon);

    void set_where_lies(Game& game) override;

    void use_special_ability(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};

class Weather_card : public Card {
public:
    Weather_card(std::string Name, std::string Filename_of_image);

    virtual void use_special_ability(Game& game);
    virtual void set_where_lies(Game& game);
    virtual void bot_set_where_lies(Game& game);
    virtual void delete_card(Game& game);
};

class Cold_card : public Weather_card {
public:
    Cold_card(std::string Filename_of_image);

    void use_special_ability(Game& game) override;

    void set_where_lies(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};

class Rain_card : public Weather_card {
public:
    Rain_card(std::string Filename_of_image);

    void use_special_ability(Game& game);

    void set_where_lies(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};

class Haze_card : public Weather_card {
public:
    Haze_card(std::string Filename_of_image);

    void use_special_ability(Game& game) override;

    void set_where_lies(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};

class Good_weather_card : public Weather_card {
public:
    Good_weather_card(std::string Filename_of_image);

    void use_special_ability(Game& game);

    void set_where_lies(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};


//......................................................................................Особые карты.....................................................................................//


class Double_buff_card : public Card {
public:
    Double_buff_card(std::string Filename_of_image);

    void use_special_ability(Game& game);

    void set_where_lies(Game& game) override;
    void bot_set_where_lies(Game& game) override;
    void delete_card(Game& game) override;
};