#pragma once
#include <vector>
#include "Class_Card.cpp"


class Desk {
public:
    std::vector<Card> buff_melee;
    std::vector<Card> buff_archer;
    std::vector<Card> buff_siege;
    std::vector<Card> strength_melee;
    std::vector<Card> strength_archer;
    std::vector<Card> strength_siege;

    Buff_manager buff_manager;
};

class Buff_manager {
public:
    int buff_by_one_melee;
    int buff_by_one_archer;
    int buff_by_one_siege;
    int buff_in_two_melee;
    int buff_in_two_archer;
    int buff_in_two_siege;
};