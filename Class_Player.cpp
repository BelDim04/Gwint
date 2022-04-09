#pragma once
#include <vector>
#include "Class_Desk.cpp"
#include "Class_Card.cpp"

class Player {
public:
    static const size_t amount_in_hand = 10;
    std::vector<Card> hand;
    std::vector<Card> reset;
    std::vector<Card> deck;
    Desk desk;
    const bool is_bot;
    //type_of_fraction
    int sum_strength = 0;
    bool has_fold = false;

    Player(std::vector<Card> cards, bool is_bot) : is_bot(is_bot) {
        hand.reserve(amount_in_hand);
        deck.reserve(cards.size() - amount_in_hand);
        for (size_t i = 0; i < amount_in_hand; ++i) hand[i] = cards[i];
    };
};