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
    Game game(true);
    GameAnimation animation(game);
    animation.run();
    return 0;
}
