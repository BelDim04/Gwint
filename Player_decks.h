#pragma once
#include "Card_src.h"
#include "Class_Game.h"
#include<memory>

class Player_deck_src {
private:
    void declare_deck_1() {//то же самое что нормальная сложность бота
        //pushing weather
        deck_1.push_back(src.get_Cold());
        deck_1.push_back(src.get_Cold());
        deck_1.push_back(src.get_Rain());
        deck_1.push_back(src.get_Haze());
        deck_1.push_back(src.get_Bright_day());
        //pushing spy cards
        deck_1.push_back(src.get_Dikstra());
        deck_1.push_back(src.get_Stennis());
        deck_1.push_back(src.get_Shelard());
        //pushing healing cards
        deck_1.push_back(src.get_Archer_support());
        deck_1.push_back(src.get_Healer_Gavenkar());
        //pushing killing cards
        deck_1.push_back(src.get_Shirru());
        //pushing usual cards
        deck_1.push_back(src.get_Belly());
        deck_1.push_back(src.get_Ballista());
        deck_1.push_back(src.get_Belly());
        deck_1.push_back(src.get_Ballista());
        deck_1.push_back(src.get_Leto_from_Guleto());
        deck_1.push_back(src.get_Sabrine_Glevissig());
        deck_1.push_back(src.get_Yorvet());
        deck_1.push_back(src.get_Kagyr());
        deck_1.push_back(src.get_Moorvan_Voorhis());
        deck_1.push_back(src.get_Teabor_Eggerbraht());
        deck_1.push_back(src.get_Demon());
        deck_1.push_back(src.get_Demon());
        deck_1.push_back(src.get_Readan_trooper());
        //pushing buffing cards
        deck_1.push_back(src.get_Kaedven_siege_master());
        deck_1.push_back(src.get_Kaedven_siege_master());
        deck_1.push_back(src.get_Command_horn());
    }
    void declare_deck_2() {
        //pushing weather
        deck_2.push_back(src.get_Cold());
        deck_2.push_back(src.get_Rain());
        deck_2.push_back(src.get_Rain());
        deck_2.push_back(src.get_Haze());
        deck_2.push_back(src.get_Bright_day());
        //pushing spy cards
        deck_2.push_back(src.get_Dikstra());
        deck_2.push_back(src.get_Stennis());
        deck_2.push_back(src.get_Avalakh());
        deck_2.push_back(src.get_Taler());
        //pushing healing cards
        deck_2.push_back(src.get_Healer_Gavenkar());
        //pushing killing cards
        deck_2.push_back(src.get_PrinceToad());
        //pushing usual cards
        deck_2.push_back(src.get_Belly());
        deck_2.push_back(src.get_Ballista());
        deck_2.push_back(src.get_Ciri());
        deck_2.push_back(src.get_Insane_Lugos());
        deck_2.push_back(src.get_Moorvan_Voorhis());
        deck_2.push_back(src.get_Demon());
        deck_2.push_back(src.get_Kagyr());
        deck_2.push_back(src.get_Readan_trooper());
        deck_2.push_back(src.get_Readan_trooper1());
        deck_2.push_back(src.get_Belly());
        deck_2.push_back(src.get_Ballista());
        deck_2.push_back(src.get_Phillipa_Eilhart());
        deck_2.push_back(src.get_Sabrine_Glevissig());
        deck_2.push_back(src.get_Yorvet());
        //pushing buffing cards
        deck_2.push_back(src.get_Kaedven_siege_master());
        deck_2.push_back(src.get_Kaedven_siege_master());
        deck_2.push_back(src.get_Command_horn());
        deck_2.push_back(src.get_Lutik());
    }
    void declare_deck_3() {
        //pushing weather
        deck_3.push_back(src.get_Cold());
        deck_3.push_back(src.get_Cold());
        deck_3.push_back(src.get_Rain());
        deck_3.push_back(src.get_Haze());
        deck_3.push_back(src.get_Bright_day());
        //pushing spy cards
        deck_3.push_back(src.get_Avalakh());
        deck_3.push_back(src.get_Taler());
        deck_3.push_back(src.get_Dikstra());
        deck_3.push_back(src.get_Stennis());
        //pushing healing cards
        deck_3.push_back(src.get_Archer_support());
        deck_3.push_back(src.get_Menno_Koegorn());
        //pushing delete cards
        deck_3.push_back(src.get_Shirru());
        deck_3.push_back(src.get_PrinceToad());
        //pushing usual cards
        deck_3.push_back(src.get_Ciri());
        deck_3.push_back(src.get_Belly());
        deck_3.push_back(src.get_Belly());
        deck_3.push_back(src.get_Ballista());
        deck_3.push_back(src.get_Ballista());
        deck_3.push_back(src.get_Sheldon_Skaggs());
        deck_3.push_back(src.get_Demon());
        deck_3.push_back(src.get_Kagyr());
        deck_3.push_back(src.get_Moorvan_Voorhis());
        deck_3.push_back(src.get_Phillipa_Eilhart());
        deck_3.push_back(src.get_Sabrine_Glevissig());
        deck_3.push_back(src.get_Yorvet());

        //pushing buffing cards
        deck_3.push_back(src.get_Kaedven_siege_master());
        deck_3.push_back(src.get_Kaedven_siege_master());
        deck_3.push_back(src.get_Command_horn());
        deck_3.push_back(src.get_Lutik());
    }
public:
    Src src = Src();

    std::vector<std::shared_ptr<Card>> deck_1;
    std::vector<std::shared_ptr<Card>> deck_2;
    std::vector<std::shared_ptr<Card>> deck_3;
    std::vector<std::shared_ptr<Card>> empty;

    Player_deck_src() {
        declare_deck_1();
        declare_deck_2();
        declare_deck_3();
    }
};
