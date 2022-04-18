#include "Class_Card.h"

class Src{
private:
    bool is_created = false;
public:
    Src() {
        if(is_created) throw;
        else is_created = true;
    }
    Healing_card Menno_Koegorn = Healing_card(10, 0,
    "Menno_Koegorn", "src/Coegorn.jpg", "melee");
    Spy_card Dikstra = Spy_card(4, 1,
    "Dikstra", "src/Dikstra.jpg", "melee");
    Healing_card Healer_of_Brown_Banner = Healing_card(5, 1,
    "Healer_of_Brown_Banner", "src/Healer.jpg", "siege");
     Usual_card Leto_from_Guleto = Usual_card(10, 0,
     "Leto_from_Guleto", "src/Leto.jpg", "melee");
    Usual_card Insane_Lugos = Usual_card(6, 1,
    "Insane_Lugos", "src/Lugos.jpg", "melee");
    Usual_card Moorvan_Voorhis= Usual_card(10, 0,
    "Moorvan_Voorhis", "src/Moorvan.jpg", "siege");
    Usual_card Phillipa_Eilhart = Usual_card(10, 1,
    "Phillipa_Eilhart", "src/Phillipa.jpg", "archer");
    Usual_card Sabrine_Glevissig = Usual_card(5, 1,
    "Sabrine_Glevissig", "src/Sabrine.jpg", "archer");
    One_increase_card Kaedven_siege_master = One_increase_card(1, 1,
    "Kaedven_siege_master", "src/Kaedven_siege_master.jpg", "siege");
    Usual_card Sheldon_Skaggs = Usual_card(4, 1,
    "Sheldon_Skaggs", "src/Skaggs.jpg", "archer");
    Spy_card Stennis = Spy_card(4, 1,
    "Stennis", "src/Stennis.jpg", "melee");
    Spy_card Taler = Spy_card(1, 1,
    "Taler", "src/Taler.jpg", "siege");
    Usual_card Readan_trooper = Usual_card(1, 1,
    "Readan_trooper", "src/Trooper.jpg", "melee");
    Usual_card Readan_trooper1 = Usual_card(1, 1,
    "Readan_trooper", "src/Trooper1.jpg", "melee");
    Usual_card Ballista = Usual_card(6, 1,
     "Ballista", "src/Ballista.jpg", "siege");
    Usual_card Belly = Usual_card(6, 1,
    "Belly", "src/Belly.jpg", "siege");
    Usual_card Teabor_Eggerbraht = Usual_card(10, 0,
    "Teabor_Eggerbraht", "src/Teabor.jpg", "archer");
    Healing_card Archer_support = Healing_card(3, 1,
    "Archer_support", "src/Archer_support.jpg", "archer");
    Spy_card Avalakh = Spy_card(0, 0,
    "Avalakh", "src/Avalakh.jpg", "melee");
    Good_weather_card Bright_day = Good_weather_card("src/Bright_day.jpg");
    Usual_card Ciri = Usual_card(15, 0,
    "Ciri", "src/Ciri.jpg", "melee");
    Cold_card Cold = Cold_card("src/Cold.jpg");
    Rain_card Rain = Rain_card("src/Rain.jpg");
    Haze_card Haze = Haze_card("src/Haze.jpg");
    Double_buff_card Command_horn = Double_buff_card("src/Command_horn.jpg");
    Usual_card Demon = Usual_card(7, 1,
    "Demon", "src/Demon.jpg", "melee");
    Healing_card Healer_Gavenkar = Healing_card(2, 1,
    "Healer-Gavenkar", "src/Healer-Gavenkar.jpg", "archer");
    Usual_card Kagyr = Usual_card(7, 1,
     "Kagyr", "src/Kagyr.jpg", "melee");
    Double_increase_card Lutik = Double_increase_card(7, 1,
    "Lutik", "src/Lutik.jpg", "melee");
    Spy_card Shelard = Spy_card(7, 1,
    "Sherald", "src/Sherald.jpg", "melee");
    Healing_card Siege_Support = Healing_card(2, 1,
    "Siege_Support", "src/Siege_Support.jpg", "siege");
    Spy_card Stephan_Skellin = Spy_card(9, 1,
     "Stephan_Skellin", "src/Stephan.jpg", "melee");
    Usual_card Yorvet = Usual_card(10, 0,
    "Yorvet", "src/Yorvet.jpg", "melee");
};