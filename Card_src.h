#pragma once
#include "Class_Card.h"

class Src{
public:
    Src() {
        declare_Menno_Koegorn();
        declare_Dikstra();
        declare_Healer_of_Brown_Banner();
        declare_Insane_Lugos();
        declare_Leto_from_Guleto();
        declare_Moorvan_Voorhis();
        declare_Phillipa_Eilhart();
        declare_Sabrine_Glevissig();
        declare_Kaedven_siege_master();
        declare_Sheldon_Skaggs();
        declare_Stennis();
        declare_Taler();
        declare_Readan_trooper();
        declare_Readan_trooper1();
        declare_Ballista();
        declare_Belly();
        declare_Teabor_Eggerbraht();
        declare_Archer_support();
        declare_Avalakh();
        declare_Bright_day();
        declare_Ciri();
        declare_Cold();
        declare_Rain();
        declare_Haze();
        declare_Command_horn();
        declare_Demon();
        declare_Kagyr();
        declare_Healer_Gavenkar();
        declare_Lutik();
        declare_Shelard();
        declare_Siege_Support();
        declare_Stephan_Skellin();
        declare_Yorvet();
        declare_Shirru();
        declare_PrinceToad();
    }



    Healing_card Menno_Koegorn = Healing_card(10, 0,
    "Menno_Koegorn", "src/Coegorn.jpg", "melee");
    std::vector<Healing_card> Menno_Koegorn_vector;
    int index_Menno = 0;
    void declare_Menno_Koegorn() {
        for(int i = 0; i < 15; ++i) {
            Menno_Koegorn_vector.push_back(Menno_Koegorn);
        }
    }
    Card* get_Menno_Koegorn() {
        return &(Menno_Koegorn_vector[index_Menno++]);
    }



    Spy_card Dikstra = Spy_card(4, 1,
    "Dikstra", "src/Dikstra.jpg", "melee");
    std::vector<Spy_card> Dikstra_vector;
    int index_Dikstra = 0;
    void declare_Dikstra() {
        for(int i = 0; i < 15; ++i) {
            Dikstra_vector.push_back(Dikstra);
        }
    }
    Card* get_Dikstra() {
        return &(Dikstra_vector[index_Dikstra++]);
    }



    Healing_card Healer_of_Brown_Banner = Healing_card(5, 1,
    "Healer_of_Brown_Banner", "src/Healer.jpg", "siege");
    std::vector<Healing_card> Healer_of_Brown_Banner_vector;
    int index_Healer_of_Brown_Banner = 0;
    void declare_Healer_of_Brown_Banner() {
        for(int i = 0; i < 15; ++i) {
            Healer_of_Brown_Banner_vector.push_back(Healer_of_Brown_Banner);
        }
    }
    Card* get_Healer_of_Brown_Banner() {
        return &(Healer_of_Brown_Banner_vector[index_Healer_of_Brown_Banner++]);
    }



    Usual_card Leto_from_Guleto = Usual_card(10, 0,
     "Leto_from_Guleto", "src/Leto.jpg", "melee");
    std::vector<Usual_card> Leto_from_Guleto_vector;
    int index_Leto_from_Guleto = 0;
    void declare_Leto_from_Guleto() {
        for(int i = 0; i < 15; ++i) {
            Leto_from_Guleto_vector.push_back(Leto_from_Guleto);
        }
    }
    Card* get_Leto_from_Guleto() {
        return &(Leto_from_Guleto_vector[index_Leto_from_Guleto++]);
    }



    Usual_card Insane_Lugos = Usual_card(6, 1,
    "Insane_Lugos", "src/Lugos.jpg", "melee");
    std::vector<Usual_card> Insane_Lugos_vector;
    int index_Insane_Lugos = 0;
    void declare_Insane_Lugos() {
        for(int i = 0; i < 15; ++i) {
            Insane_Lugos_vector.push_back(Insane_Lugos);
        }
    }
    Card* get_Insane_Lugos() {
        return &(Insane_Lugos_vector[index_Insane_Lugos++]);
    }



    Usual_card Moorvan_Voorhis= Usual_card(10, 0,
    "Moorvan_Voorhis", "src/Moorvan.jpg", "siege");
    std::vector<Usual_card> Moorvan_Voorhis_vector;
    int index_Moorvan_Voorhis = 0;
    void declare_Moorvan_Voorhis() {
        for(int i = 0; i < 15; ++i) {
            Moorvan_Voorhis_vector.push_back(Moorvan_Voorhis);
        }
    }
    Card* get_Moorvan_Voorhis() {
        return &(Moorvan_Voorhis_vector[index_Moorvan_Voorhis++]);
    }



    Usual_card Phillipa_Eilhart = Usual_card(10, 1,
    "Phillipa_Eilhart", "src/Phillipa.jpg", "archer");
    std::vector<Usual_card> Phillipa_Eilhart_vector;
    int index_Phillipa_Eilhart = 0;
    void declare_Phillipa_Eilhart() {
        for(int i = 0; i < 15; ++i) {
            Phillipa_Eilhart_vector.push_back(Phillipa_Eilhart);
        }
    }
    Card* get_Phillipa_Eilhart() {
        return &(Phillipa_Eilhart_vector[index_Phillipa_Eilhart++]);
    }



    Usual_card Sabrine_Glevissig = Usual_card(5, 1,
    "Sabrine_Glevissig", "src/Sabrine.jpg", "archer");
    std::vector<Usual_card> Sabrine_Glevissig_vector;
    int index_Sabrine_Glevissig = 0;
    void declare_Sabrine_Glevissig() {
        for(int i = 0; i < 15; ++i) {
            Sabrine_Glevissig_vector.push_back(Sabrine_Glevissig);
        }
    }
    Card* get_Sabrine_Glevissig() {
        return &(Sabrine_Glevissig_vector[index_Sabrine_Glevissig++]);
    }



    One_increase_card Kaedven_siege_master = One_increase_card(1, 1,
    "Kaedven_siege_master", "src/Kaedven_siege_master.jpg", "siege");
    std::vector<One_increase_card> Kaedven_siege_master_vector;
    int index_Kaedven_siege_master = 0;
    void declare_Kaedven_siege_master() {
        for(int i = 0; i < 15; ++i) {
            Kaedven_siege_master_vector.push_back(Kaedven_siege_master);
        }
    }
    Card* get_Kaedven_siege_master() {
        return &(Kaedven_siege_master_vector[index_Kaedven_siege_master++]);
    }



    Usual_card Sheldon_Skaggs = Usual_card(4, 1,
    "Sheldon_Skaggs", "src/Skaggs.jpg", "archer");
    std::vector<Usual_card> Sheldon_Skaggs_vector;
    int index_Sheldon_Skaggs = 0;
    void declare_Sheldon_Skaggs() {
        for(int i = 0; i < 15; ++i) {
            Sheldon_Skaggs_vector.push_back(Sheldon_Skaggs);
        }
    }
    Card* get_Sheldon_Skaggs() {
        return &(Sheldon_Skaggs_vector[index_Sheldon_Skaggs++]);
    }



    Spy_card Stennis = Spy_card(4, 1,
    "Stennis", "src/Stennis.jpg", "melee");
    std::vector<Spy_card> Stennis_vector;
    int index_Stennis = 0;
    void declare_Stennis() {
        for(int i = 0; i < 15; ++i) {
            Stennis_vector.push_back(Stennis);
        }
    }
    Card* get_Stennis() {
        return &(Stennis_vector[index_Stennis++]);
    }



    Spy_card Taler = Spy_card(1, 1,
    "Taler", "src/Taler.jpg", "siege");
    std::vector<Spy_card> Taler_vector;
    int index_Taler = 0;
    void declare_Taler() {
        for(int i = 0; i < 15; ++i) {
            Taler_vector.push_back(Taler);
        }
    }
    Card* get_Taler() {
        return &(Taler_vector[index_Taler++]);
    }



    Usual_card Readan_trooper = Usual_card(1, 1,
    "Readan_trooper", "src/Trooper.jpg", "melee");
    std::vector<Usual_card> Readan_trooper_vector;
    int index_Readan_trooper = 0;
    void declare_Readan_trooper() {
        for(int i = 0; i < 15; ++i) {
            Readan_trooper_vector.push_back(Readan_trooper);
        }
    }
    Card* get_Readan_trooper() {
        return &(Readan_trooper_vector[index_Readan_trooper++]);
    }



    Usual_card Readan_trooper1 = Usual_card(1, 1,
    "Readan_trooper", "src/Trooper1.jpg", "melee");
    std::vector<Usual_card> Readan_trooper1_vector;
    int index_Readan_trooper1 = 0;
    void declare_Readan_trooper1() {
        for(int i = 0; i < 15; ++i) {
            Readan_trooper1_vector.push_back(Readan_trooper1);
        }
    }
    Card* get_Readan_trooper1() {
        return &(Readan_trooper1_vector[index_Readan_trooper1++]);
    }



    Usual_card Ballista = Usual_card(6, 1,
     "Ballista", "src/Ballista.jpg", "siege");
    std::vector<Usual_card> Ballista_vector;
    int index_Ballista = 0;
    void declare_Ballista() {
        for(int i = 0; i < 15; ++i) {
            Ballista_vector.push_back(Ballista);
        }
    }
    Card* get_Ballista() {
        return &(Ballista_vector[index_Ballista++]);
    }



    Usual_card Belly = Usual_card(6, 1,
    "Belly", "src/Belly.jpg", "siege");
    std::vector<Usual_card> Belly_vector;
    int index_Belly = 0;
    void declare_Belly() {
        for(int i = 0; i < 15; ++i) {
            Belly_vector.push_back(Belly);
        }
    }
    Card* get_Belly() {
        return &(Belly_vector[index_Belly++]);
    }



    Usual_card Teabor_Eggerbraht = Usual_card(10, 0,
    "Teabor_Eggerbraht", "src/Teabor.jpg", "archer");
    std::vector<Usual_card> Teabor_Eggerbraht_vector;
    int index_Teabor_Eggerbraht = 0;
    void declare_Teabor_Eggerbraht() {
        for(int i = 0; i < 15; ++i) {
            Teabor_Eggerbraht_vector.push_back(Teabor_Eggerbraht);
        }
    }
    Card* get_Teabor_Eggerbraht() {
        return &(Teabor_Eggerbraht_vector[index_Teabor_Eggerbraht++]);
    }



    Healing_card Archer_support = Healing_card(3, 1,
    "Archer_support", "src/Archer_support.jpg", "archer");
    std::vector<Healing_card> Archer_support_vector;
    int index_Archer_support = 0;
    void declare_Archer_support() {
        for(int i = 0; i < 15; ++i) {
            Archer_support_vector.push_back(Archer_support);
        }
    }
    Card* get_Archer_support() {
        return &(Archer_support_vector[index_Archer_support++]);
    }



    Spy_card Avalakh = Spy_card(0, 0,
    "Avalakh", "src/Avalakh.jpg", "melee");
    std::vector<Spy_card> Avalakh_vector;
    int index_Avalakh = 0;
    void declare_Avalakh() {
        for(int i = 0; i < 15; ++i) {
             Avalakh_vector.push_back(Avalakh);
        }
    }
    Card* get_Avalakh() {
        return &(Avalakh_vector[index_Avalakh++]);
    }



    Good_weather_card Bright_day = Good_weather_card("src/Bright_day.jpg");
    std::vector<Good_weather_card> Bright_day_vector;
    int index_Bright_day = 0;
    void declare_Bright_day() {
        for(int i = 0; i < 15; ++i) {
            Bright_day_vector.push_back(Bright_day);
        }
    }
    Card* get_Bright_day() {
        return &(Bright_day_vector[index_Bright_day++]);
    }



    Usual_card Ciri = Usual_card(15, 0,
    "Ciri", "src/Ciri.jpg", "melee");
    std::vector<Usual_card> Ciri_vector;
    int index_Ciri = 0;
    void declare_Ciri() {
        for(int i = 0; i < 15; ++i) {
            Ciri_vector.push_back(Ciri);
        }
    }
    Card* get_Ciri() {
        return &(Ciri_vector[index_Ciri++]);
    }



    Cold_card Cold = Cold_card("src/Cold.jpg");
    std::vector<Cold_card> Cold_vector;
    int index_Cold = 0;
    void declare_Cold() {
        for(int i = 0; i < 15; ++i) {
            Cold_vector.push_back(Cold);
        }
    }
    Card* get_Cold() {
        return &(Cold_vector[index_Cold++]);
    }



    Rain_card Rain = Rain_card("src/Rain.jpg");
    std::vector<Rain_card> Rain_vector;
    int index_Rain = 0;
    void declare_Rain() {
        for(int i = 0; i < 15; ++i) {
            Rain_vector.push_back(Rain);
        }
    }
    Card* get_Rain() {
        return &(Rain_vector[index_Rain++]);
    }



    Haze_card Haze = Haze_card("src/Haze.jpg");
    std::vector<Haze_card> Haze_vector;
    int index_Haze = 0;
    void declare_Haze() {
        for(int i = 0; i < 15; ++i) {
            Haze_vector.push_back(Haze);
        }
    }
    Card* get_Haze() {
        return &(Haze_vector[index_Haze++]);
    }



    Double_buff_card Command_horn = Double_buff_card("src/Command_horn.jpg");
    std::vector<Double_buff_card> Command_horn_vector;
    int index_Command_horn = 0;
    void declare_Command_horn() {
        for(int i = 0; i < 15; ++i) {
            Command_horn_vector.push_back(Command_horn);
        }
    }
    Card* get_Command_horn() {
        return &(Command_horn_vector[index_Command_horn++]);
    }



    Usual_card Demon = Usual_card(7, 1,
    "Demon", "src/Demon.jpg", "melee");
    std::vector<Usual_card> Demon_vector;
    int index_Demon = 0;
    void declare_Demon() {
        for(int i = 0; i < 15; ++i) {
            Demon_vector.push_back(Demon);
        }
    }
    Card* get_Demon() {
        return &(Demon_vector[index_Demon++]);
    }



    Healing_card Healer_Gavenkar = Healing_card(2, 1,
    "Healer-Gavenkar", "src/Healer-Gavenkar.jpg", "archer");
    std::vector<Healing_card> Healer_Gavenkar_vector;
    int index_Healer_Gavenkar = 0;
    void declare_Healer_Gavenkar() {
        for(int i = 0; i < 15; ++i) {
            Healer_Gavenkar_vector.push_back(Healer_Gavenkar);
        }
    }
    Card* get_Healer_Gavenkar() {
        return &(Healer_Gavenkar_vector[index_Healer_Gavenkar++]);
    }



    Usual_card Kagyr = Usual_card(7, 1,
     "Kagyr", "src/Kagyr.jpg", "melee");
    std::vector<Usual_card> Kagyr_vector;
    int index_Kagyr = 0;
    void declare_Kagyr() {
        for(int i = 0; i < 15; ++i) {
            Kagyr_vector.push_back(Kagyr);
        }
    }
    Card* get_Kagyr() {
        return &(Kagyr_vector[index_Kagyr++]);
    }



    Double_increase_card Lutik = Double_increase_card(7, 1,
    "Lutik", "src/Lutik.jpg", "melee");
    std::vector<Double_increase_card> Lutik_vector;
    int index_Lutik = 0;
    void declare_Lutik() {
        for(int i = 0; i < 15; ++i) {
            Lutik_vector.push_back(Lutik);
        }
    }
    Card* get_Lutik() {
        return &(Lutik_vector[index_Lutik++]);
    }



    Spy_card Shelard = Spy_card(7, 1,
    "Sherald", "src/Sherald.jpg", "melee");
    std::vector<Spy_card> Shelard_vector;
    int index_Shelard = 0;
    void declare_Shelard() {
        for(int i = 0; i < 15; ++i) {
            Shelard_vector.push_back(Shelard);
        }
    }
    Card* get_Shelard() {
        return &(Shelard_vector[index_Shelard++]);
    }



    Healing_card Siege_Support = Healing_card(2, 1,
    "Siege_Support", "src/Siege_Support.jpg", "siege");
    std::vector<Healing_card> Siege_Support_vector;
    int index_Siege_Support = 0;
    void declare_Siege_Support() {
        for(int i = 0; i < 15; ++i) {
            Siege_Support_vector.push_back(Siege_Support);
        }
    }
    Card* get_Siege_Support() {
        return &(Siege_Support_vector[index_Siege_Support++]);
    }



    Spy_card Stephan_Skellin = Spy_card(9, 1,
     "Stephan_Skellin", "src/Stephan.jpg", "melee");
    std::vector<Spy_card> Stephan_Skellin_vector;
    int index_Stephan_Skellin = 0;
    void declare_Stephan_Skellin() {
        for(int i = 0; i < 15; ++i) {
            Stephan_Skellin_vector.push_back(Stephan_Skellin);
        }
    }
    Card* get_Stephan_Skellin() {
        return &(Stephan_Skellin_vector[index_Stephan_Skellin++]);
    }



    Usual_card Yorvet = Usual_card(10, 0,
    "Yorvet", "src/Yorvet.jpg", "melee");
    std::vector<Usual_card> Yorvet_vector;
    int index_Yorvet = 0;
    void declare_Yorvet() {
        for(int i = 0; i < 15; ++i) {
            Yorvet_vector.push_back(Yorvet);
        }
    }
    Card* get_Yorvet() {
        return &(Yorvet_vector[index_Yorvet++]);
    }

    Delete_card Shirru = Delete_card(7, 1,
      "Shirru", "src/Shirru", "siege");
    std::vector<Delete_card> Shirru_vector;
    int index_Shirru = 0;
    void declare_Shirru() {
        for(int i = 0; i < 15; ++i) {
            Shirru_vector.push_back(Shirru);
        }
    }
    Card* get_Shirru() {
        return &(Shirru_vector[index_Shirru++]);
    }

    Delete_card PrinceToad = Delete_card(9, 0,
                                     "PrinceToad", "src/PrinceToad", "archer");
    std::vector<Delete_card> PrinceToad_vector;
    int index_PrinceToad = 0;
    void declare_PrinceToad() {
        for(int i = 0; i < 15; ++i) {
            Shirru_vector.push_back(Shirru);
        }
    }
    Card* get_PrinceToad() {
        return &(Shirru_vector[index_Shirru++]);
    }
};