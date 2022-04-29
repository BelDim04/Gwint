#pragma once
#include "Card_src.h"
#include "Class_Game.h"

class Bot_deck_src {
public:
    std::vector<Card*> deck_weak;
    std::vector<Card*> deck_normal;
    std::vector<Card*> deck_hard;
    std::vector<Card*> empty;
    //std::vector<Card*> deck_7;
    void declare_deck_weak() {
        //pushing weather
        deck_weak.push_back(src.get_Cold());
        deck_weak.push_back(src.get_Rain());
        deck_weak.push_back(src.get_Haze());
        deck_weak.push_back(src.get_Bright_day());
        deck_weak.push_back(src.get_Rain());
        deck_weak.push_back(src.get_Bright_day());
        //pushing spy cards
        deck_weak.push_back(src.get_Stephan_Skellin());
        //pushing healing cards
        deck_weak.push_back(src.get_Healer_Gavenkar());
        deck_weak.push_back(src.get_Siege_Support());
        //pushing killing cards

        //pushing usual_cards
        deck_weak.push_back(src.get_Readan_trooper());
        deck_weak.push_back(src.get_Readan_trooper1());
        deck_weak.push_back(src.get_Readan_trooper());
        deck_weak.push_back(src.get_Readan_trooper1());
        deck_weak.push_back(src.get_Belly());
        deck_weak.push_back(src.get_Ballista());
        deck_weak.push_back(src.get_Belly());
        deck_weak.push_back(src.get_Ballista());
        deck_weak.push_back(src.get_Insane_Lugos());
        deck_weak.push_back(src.get_Demon());
        deck_weak.push_back(src.get_Phillipa_Eilhart());
        deck_weak.push_back(src.get_Kagyr());
        //pushing buffing_cards
        deck_weak.push_back(src.get_Lutik());
        deck_weak.push_back(src.get_Command_horn());
        deck_weak.push_back(src.get_Command_horn());
        deck_weak.push_back(src.get_Kaedven_siege_master());
        deck_weak.push_back(src.get_Kaedven_siege_master());
        deck_weak.push_back(src.get_Kaedven_siege_master());
    }

    void declare_deck_normal() {
        //pushing weather
        deck_normal.push_back(src.get_Cold());
        deck_normal.push_back(src.get_Cold());
        deck_normal.push_back(src.get_Rain());
        deck_normal.push_back(src.get_Haze());
        deck_normal.push_back(src.get_Bright_day());
        //pushing spy cards
        deck_normal.push_back(src.get_Dikstra());
        deck_normal.push_back(src.get_Stennis());
        deck_normal.push_back(src.get_Shelard());
        //pushing healing cards
        deck_normal.push_back(src.get_Archer_support());
        deck_normal.push_back(src.get_Healer_Gavenkar());
        //pushing killing cards
        deck_normal.push_back(src.get_Shirru());
        //pushing usual cards
        deck_normal.push_back(src.get_Belly());
        deck_normal.push_back(src.get_Ballista());
        deck_normal.push_back(src.get_Belly());
        deck_normal.push_back(src.get_Ballista());
        deck_normal.push_back(src.get_Leto_from_Guleto());
        deck_normal.push_back(src.get_Sabrine_Glevissig());
        deck_normal.push_back(src.get_Yorvet());
        deck_normal.push_back(src.get_Kagyr());
        deck_normal.push_back(src.get_Moorvan_Voorhis());
        deck_normal.push_back(src.get_Teabor_Eggerbraht());
        deck_normal.push_back(src.get_Demon());
        deck_normal.push_back(src.get_Demon());
        deck_normal.push_back(src.get_Readan_trooper());
        //pushing buffing cards
        deck_normal.push_back(src.get_Kaedven_siege_master());
        deck_normal.push_back(src.get_Kaedven_siege_master());
        deck_normal.push_back(src.get_Command_horn());
    }

    void declare_deck_hard() {
        //pushing weather
        deck_hard.push_back(src.get_Cold());
        deck_hard.push_back(src.get_Rain());
        deck_hard.push_back(src.get_Cold());
        deck_hard.push_back(src.get_Rain());
        deck_hard.push_back(src.get_Haze());
        deck_hard.push_back(src.get_Bright_day());
        //pushing spy cards
        deck_hard.push_back(src.get_Avalakh());
        deck_hard.push_back(src.get_Taler());
        deck_hard.push_back(src.get_Dikstra());
        deck_hard.push_back(src.get_Stennis());
        //pushing healing cards
        deck_hard.push_back(src.get_Archer_support());
        deck_hard.push_back(src.get_Healer_of_Brown_Banner());
        deck_hard.push_back(src.get_Archer_support());
        //pushing killing cards
        deck_hard.push_back(src.get_Shirru());
        deck_hard.push_back(src.get_PrinceToad());
        //pushing usual cards
        deck_hard.push_back(src.get_Ciri());
        deck_hard.push_back(src.get_Moorvan_Voorhis());
        deck_hard.push_back(src.get_Kagyr());
        deck_hard.push_back(src.get_Leto_from_Guleto());
        deck_hard.push_back(src.get_Phillipa_Eilhart());
        deck_hard.push_back(src.get_Teabor_Eggerbraht());
        deck_hard.push_back(src.get_Sabrine_Glevissig());
        deck_hard.push_back(src.get_Ballista());
        deck_hard.push_back(src.get_Ballista());
        deck_hard.push_back(src.get_Belly());
        deck_hard.push_back(src.get_Belly());
        deck_hard.push_back(src.get_Yorvet());
        deck_hard.push_back(src.get_Demon());
        deck_hard.push_back(src.get_Demon());
        //pushing buffing cards
        deck_hard.push_back(src.get_Command_horn());
        deck_hard.push_back(src.get_Lutik());
        deck_hard.push_back(src.get_Command_horn());
    }

public:
    Src src = Src();
    Player player_weak = Player(empty, 1);
    Player player_normal = Player(empty, 1);
    Player player_hard = Player(empty, 1);

    Bot_deck_src() {
        declare_deck_weak();
        declare_deck_normal();
        declare_deck_hard();
        player_weak = Player(deck_weak, 0);
        player_normal = Player(deck_normal, 0);
        player_hard = Player(deck_hard, 0);
    }
};