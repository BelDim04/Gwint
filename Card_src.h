#pragma once
#include "Class_Card.h"
#include <memory>

class Src{
public:
    std::vector<std::shared_ptr<Card>> Src_vector;
    Src() {
        Src_vector.push_back(get_Archer_support());
        Src_vector.push_back(get_Avalakh());
        Src_vector.push_back(get_Ballista());
        Src_vector.push_back(get_Belly());
        Src_vector.push_back(get_Bright_day());
        Src_vector.push_back(get_Ciri());
        Src_vector.push_back(get_Cold());
        Src_vector.push_back(get_Command_horn());
        Src_vector.push_back(get_Demon());
        Src_vector.push_back(get_Dikstra());
        Src_vector.push_back(get_Haze());
        Src_vector.push_back(get_Healer_Gavenkar());
        Src_vector.push_back(get_Healer_of_Brown_Banner());
        Src_vector.push_back(get_Insane_Lugos());
        Src_vector.push_back(get_Kaedven_siege_master());
        Src_vector.push_back(get_Kagyr());
        Src_vector.push_back(get_Leto_from_Guleto());
        Src_vector.push_back(get_Lutik());
        Src_vector.push_back(get_Menno_Koegorn());
        Src_vector.push_back(get_Moorvan_Voorhis());
        Src_vector.push_back(get_Phillipa_Eilhart());
        Src_vector.push_back(get_PrinceToad());
        Src_vector.push_back(get_Rain());
        Src_vector.push_back(get_Readan_trooper());
        Src_vector.push_back(get_Readan_trooper1());
        Src_vector.push_back(get_Sabrine_Glevissig());
        Src_vector.push_back(get_Shelard());
        Src_vector.push_back(get_Sheldon_Skaggs());
        Src_vector.push_back(get_Shirru());
        Src_vector.push_back(get_Siege_Support());
        Src_vector.push_back(get_Stennis());
        Src_vector.push_back(get_Stephan_Skellin());
        Src_vector.push_back(get_Taler());
        Src_vector.push_back(get_Teabor_Eggerbraht());
        Src_vector.push_back(get_Yorvet());
    }



    std::shared_ptr<Card> get_Menno_Koegorn() {
        return std::make_shared<Spy_card>(10, 0, "Menno_Koegorn", "src/Coegorn.jpg", "melee");
    }



    std::shared_ptr<Card> get_Dikstra() {
        return std::make_shared<Spy_card>(4, 1, "Dikstra", "src/Dikstra.jpg", "melee");
    }



    std::shared_ptr<Card> get_Healer_of_Brown_Banner() {
        return std::make_shared<Healing_card>(5, 1, "Healer_of_Brown_Banner", "src/Healer.jpg", "siege");
    }



    std::shared_ptr<Card> get_Leto_from_Guleto() {
        return std::make_shared<Usual_card>(10, 0, "Leto_from_Guleto", "src/Leto.jpg", "melee");
    }


    std::shared_ptr<Card> get_Insane_Lugos() {
        return std::make_shared<Usual_card>(6, 1, "Insane_Lugos", "src/Lugos.jpg", "melee");
    }


    std::shared_ptr<Card> get_Moorvan_Voorhis() {
        return std::make_shared<Usual_card>(10, 0, "Moorvan_Voorhis", "src/Moorvan.jpg", "siege");
    }


    std::shared_ptr<Card> get_Phillipa_Eilhart() {
        return std::make_shared<Usual_card>(10, 1, "Phillipa_Eilhart", "src/Phillipa.jpg", "archer");
    }


    std::shared_ptr<Card> get_Sabrine_Glevissig() {
        return std::make_shared<Usual_card>(5, 1, "Sabrine_Glevissig", "src/Sabrine.jpg", "archer");
    }


    std::shared_ptr<Card> get_Kaedven_siege_master() {
        return std::make_shared<One_increase_card>(1, 1, "Kaedven_siege_master", "src/Kaedven_siege_master.jpg", "siege");
    }


    std::shared_ptr<Card> get_Sheldon_Skaggs() {
        return std::make_shared<Usual_card>(4, 1, "Sheldon_Skaggs", "src/Skaggs.jpg", "archer");
    }


    std::shared_ptr<Card> get_Stennis() {
        return std::make_shared<Spy_card>(4, 1, "Stennis", "src/Stennis.jpg", "melee");
    }


    std::shared_ptr<Card> get_Taler() {
        return std::make_shared<Spy_card>(1, 1, "Taler", "src/Taler.jpg", "siege");
    }


    std::shared_ptr<Card> get_Readan_trooper() {
        return std::make_shared<Usual_card>(1, 1, "Readan_trooper", "src/Trooper.jpg", "melee");
    }


    std::shared_ptr<Card> get_Readan_trooper1() {
        return std::make_shared<Usual_card>(1, 1, "Readan_trooper", "src/Trooper1.jpg", "melee");
    }


    std::shared_ptr<Card> get_Ballista() {
        return std::make_shared<Usual_card>(6, 1, "Ballista", "src/Ballista.jpg", "siege");
    }


    std::shared_ptr<Card> get_Belly() {
        return std::make_shared<Usual_card>(6, 1, "Belly", "src/Belly.jpg", "siege");
    }


    std::shared_ptr<Card> get_Teabor_Eggerbraht() {
        return std::make_shared<Usual_card>(10, 0, "Teabor_Eggerbraht", "src/Teabor.jpg", "archer");
    }


    std::shared_ptr<Card> get_Archer_support() {
        return std::make_shared<Healing_card>(3, 1, "Archer_support", "src/Archer_support.jpg", "archer");
    }


    std::shared_ptr<Card> get_Avalakh() {
        return std::make_shared<Spy_card>(0, 0, "Avalakh", "src/Avalakh.jpg", "melee");
    }


    std::shared_ptr<Card> get_Bright_day() {
        return std::make_shared<Good_weather_card>("src/Bright_day.jpg");
    }


    std::shared_ptr<Card> get_Ciri() {
        return std::make_shared<Usual_card>(15, 0, "Ciri", "src/Ciri.jpg", "melee");
    }


    std::shared_ptr<Card> get_Cold() {
        return std::make_shared<Cold_card>("src/Cold.jpg");
    }


    std::shared_ptr<Card> get_Rain() {
        return std::make_shared<Rain_card>("src/Rain.jpg");
    }


    std::shared_ptr<Card> get_Haze() {
        return std::make_shared<Haze_card>("src/Haze.jpg");
    }


    std::shared_ptr<Card> get_Command_horn() {
        return std::make_shared<Double_buff_card>("src/Command_horn.jpg");
    }


    std::shared_ptr<Card> get_Demon() {
        return std::make_shared<Usual_card>(7, 1, "Demon", "src/Demon.jpg", "melee");
    }


    std::shared_ptr<Card> get_Healer_Gavenkar() {
        return std::make_shared<Healing_card>(2, 1, "Healer-Gavenkar", "src/Healer-Gavenkar.jpg", "archer");
    }


    std::shared_ptr<Card> get_Kagyr() {
        return std::make_shared<Usual_card>(7, 1, "Kagyr", "src/Kagyr.jpg", "melee");
    }


    std::shared_ptr<Card> get_Lutik() {
        return std::make_shared<Double_increase_card>(7, 1, "Lutik", "src/Lutik.jpg", "melee");
    }


    std::shared_ptr<Card> get_Shelard() {
        return std::make_shared<Spy_card>(7, 1, "Sherald", "src/Shelard.jpg", "melee");
    }


    std::shared_ptr<Card> get_Siege_Support() {
        return std::make_shared<Healing_card>(2, 1,"Siege_Support", "src/Siege_Support.jpg", "siege");
    }


    std::shared_ptr<Card> get_Stephan_Skellin() {
        return std::make_shared<Spy_card>(9, 1,"Stephan_Skellin", "src/Stephan.jpg", "melee");
    }


    std::shared_ptr<Card> get_Yorvet() {
        return std::make_shared<Usual_card>(10, 0, "Yorvet", "src/Yorvet.jpg", "melee");
    }


    std::shared_ptr<Card> get_Shirru() {
        return std::make_shared<Delete_card>(7, 1, "Shirru", "src/Shirru.jpg", "siege");
    }


    std::shared_ptr<Card> get_PrinceToad() {
        return std::make_shared<Delete_card>(9, 0, "PrinceToad", "src/PrinceToad.jpg", "archer");
    }
};