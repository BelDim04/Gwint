#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Animation.h"

int main()
{
    /*sf::RenderWindow window(sf::VideoMode(900, 600), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::Resized)
            {
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
            }
        }

        window.clear();

        window.display();
    }*/

    /*std::vector<Card> a(10, Usual_card(10, false, "a", "a", "a"));
    std::vector<Card> b(10, Usual_card(10, false, "a", "a", "a"));

    Player p1(a, false);
    Player p2(b, false);

    Game g(p1, p2, true);
    GameAnimation game;
    game.run();*/
    Src src = Src();
    std::vector<Card*> cards;
    std::vector<Card*> card1, card2;
    card1.push_back(src.get_Command_horn());
    card1.push_back(src.get_Cold());
    card1.push_back(src.get_Archer_support());
    card1.push_back(src.get_Readan_trooper1());
    card1.push_back(src.get_Avalakh());
    card1.push_back(src.get_Ballista());
    card1.push_back(src.get_Command_horn());
    card1.push_back(src.get_Cold());
    card1.push_back(src.get_Archer_support());
    card1.push_back(src.get_Readan_trooper1());
    card1.push_back(src.get_Avalakh());
    card1.push_back(src.get_Ballista());
    Player player1 = Player(card1, 0);
    card2.push_back(src.get_Readan_trooper1());
    card2.push_back(src.get_Belly());
    card2.push_back(src.get_Stennis());
    card2.push_back(src.get_Kagyr());
    card2.push_back(src.get_Ciri());
    card2.push_back(src.get_Readan_trooper1());
    card2.push_back(src.get_Belly());
    card2.push_back(src.get_Stennis());
    card2.push_back(src.get_Kagyr());
    card2.push_back(src.get_Ciri());
    Player player2 = Player(card2, 0);
    Game game(player1, player2, 0);
    GameAnimation animation(game);
    animation.run();
    return 0;
}
