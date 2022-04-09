#pragma once
#include<iostream>
#include<string>
#include "Class_Game.cpp"
#include<vector>

class Card {
public:
	std::string name;//просто название карточки
	std::string filename_of_image;//у каждой карты есть оответствующий есть рисунок
	std::string where_lies;//когда кладём на доску, выставляем для элемента его адрес

	Card(std::string Name, std::string Filename_of_image) : name(Name), filename_of_image(Filename_of_image) {};//конструктор

	virtual void set_where_lies(Game& game);//задаём куда кладём карту
	virtual void use_special_ability(Game& game);//для шпиона, лекаря и баферов нужны специальные функции, которые активируют уникальные способности
	virtual int recalculate(Game& game);//пересчёт для строки
	virtual bool can_card_be_changed();//можно ли повлиять на карту
};

//......................................................................................Силовые карты.....................................................................................//


class Strength_card : public Card {
public:
	int amount_of_strength_now;//у силовой карты есть текущая сила
	const int base_amount_of_strength;//у силовой карты есть изначальная сила
	int basic_strength = 1;//базовая сила-та сила, которая становится у карты при дебаффе
	const bool can_be_changed;//можно ли повлиять на карту
	std::string type_of_weapon;//melee, archer или siege

	Strength_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
		Card(Name, Filename_of_image), amount_of_strength_now(Amount_of_strength),
		base_amount_of_strength(Amount_of_strength), can_be_changed(Can_be_changed), type_of_weapon(Type_of_weapon) {};//конструктор


	//пересчёт - реализация
	int recalculate(Game& game) override {
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


	//можно ли повлиять
	bool can_card_be_changed() override {
		return can_be_changed;
	}

	virtual void use_special_ability(Game& game);
	virtual void set_where_lies(Game& game);
};



class Usual_card : public Strength_card {
public:

	Usual_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
		Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

	//Уникальная способность
	void use_special_ability(Game& game) override {};

	//Куда положить
	void set_where_lies(Game& game) override {
		where_lies = game.str_now_moving();
		where_lies += "_";
		where_lies += (type_of_weapon);
	}
};


class Spy_card : Strength_card {
public:

	Spy_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
		Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

	void set_where_lies(Game& game) override {
		where_lies = game.str_not_now_moving();
		where_lies += "_";
		where_lies += (type_of_weapon);
	}

	void use_special_ability(Game& game) override {
		//рандомно выбрать карты из колоды и добавить в руку
		std::vector<Card>& deck = game.now_moving().deck;
		int a = rand() % deck.size();
		int b = rand() % deck.size();
		while (a == b)  b = rand() % deck.size();
		game.spy_move(a, b);
	}
};


class Healing_card : Strength_card {
public:

	Healing_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
		Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

	void set_where_lies(Game& game) override {
		where_lies = game.str_now_moving();
		where_lies += "_";
		where_lies += (type_of_weapon);
	}

	void use_special_ability(Game& game) override {
		//рандомно выбрать карту из сброса и добавить в руку
		std::vector<Card>& reset = game.now_moving().reset;
		if (reset.size()) {
			int a = rand() % reset.size();
			game.healing_move(a);
		}
	}
};


class One_increase_card : Strength_card {
public:

	One_increase_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
		Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

	void set_where_lies(Game& game) {
		where_lies = game.str_now_moving();
		where_lies += "_";
		where_lies += (type_of_weapon);
	}


	void use_special_ability(Game& game) {
		std::pair<int&, int&> buffers = game.find_buffer(where_lies);
		buffers.first += 1;
	}
};

class Double_increase_card : Strength_card {
public:

	Double_increase_card(int Amount_of_strength, bool Can_be_changed, std::string Name, std::string Filename_of_image, std::string Type_of_weapon) :
		Strength_card(Amount_of_strength, Can_be_changed, Name, Filename_of_image, Type_of_weapon) {};

	void set_where_lies(Game& game) override {
		where_lies = game.str_now_moving();
		where_lies += "_";
		where_lies += (type_of_weapon);
	}

	void use_special_ability(Game& game) override {
		std::pair<int&, int&> buffers = game.find_buffer(where_lies);
		buffers.second *= 2;
	}
};



//......................................................................................погодные карты.....................................................................................//
class Weather_card : public Card {
public:
	Weather_card(std::string Name, std::string Filename_of_image) : Card(Name, Filename_of_image) {};

	virtual void use_special_ability(Game& game);
	virtual void set_where_lies(Game& game);


};

class Cold_card : public Weather_card {
public:
	Cold_card(std::string Filename_of_image) : Weather_card("Cold", Filename_of_image) {};

	void use_special_ability(Game& game) {
		bool& is_weather_bad = game.find_weather_buffer("Cold");
		if (!is_weather_bad) is_weather_bad = true;
	}

	void set_where_lies(Game& game) override {
		where_lies = "weather";
	}
};

class Rain_card : public Weather_card {
	Rain_card(std::string Filename_of_image) : Weather_card("Rain", Filename_of_image) {};

	void use_special_ability(Game& game) {
		bool& is_weather_bad = game.find_weather_buffer("Rain");
		if (!is_weather_bad) is_weather_bad = true;
	}

	void set_where_lies(Game& game) override {
		where_lies = "weather";
	}
};

class Haze_card : public Weather_card {
	Haze_card(std::string Filename_of_image) : Weather_card("Haze", Filename_of_image) {};

	void use_special_ability(Game& game) {
		bool& is_weather_bad = game.find_weather_buffer("Haze");
		if (!is_weather_bad) is_weather_bad = true;
	}

	void set_where_lies(Game& game) override {
		where_lies = "weather";
	}
};

class Good_weather_card : public Weather_card {
	Good_weather_card(std::string Filename_of_image) : Weather_card("Bright_day", Filename_of_image) {};

	void use_special_ability(Game& game) {
		game.find_weather_buffer("Haze") = false;
		game.find_weather_buffer("Cold") = false;
		game.find_weather_buffer("Rain") = false;
		game.weather_manager.weather.clear();
		//запустить анимацию удаления карт
	}

	void set_where_lies(Game& game) override {
		where_lies = "None";
	}
};


//......................................................................................Особые карты.....................................................................................//


class Double_buff_card : public Card {
	Double_buff_card(std::string Filename_of_image) : Card("Command Horn", Filename_of_image) {};

	void use_special_ability(Game& game) {
		//where_lies_copy - cоответствующее where_lies 
		std::string where_lies_copy = where_lies;
		where_lies_copy.resize(8);
		if (where_lies[13] == 'm') where_lies_copy.append("melee");
		if (where_lies[13] == 'a') where_lies_copy.append("archer");
		if (where_lies[13] == 's') where_lies_copy.append("siege");
		std::pair<int&, int&> buffers = game.find_buffer(where_lies_copy);
		buffers.second *= 2;
	}

	void set_where_lies(Game& game) override {
		//а здесь происходит ввод, куда надо положить
		//wheer_lies имеет вид playeri_buff_melee/archer/siege
	}
};




