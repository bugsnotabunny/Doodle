#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

#include "Events/Event.hpp"

int main()
{
    try {
        const unsigned gameHeight = 768;
        const unsigned gameWidth = gameHeight / 3 * 2;

        sf::RenderWindow window{sf::VideoMode(gameWidth, gameHeight, 32),
                                "Doodle Jump (not really)",
                                sf::Style::Titlebar | sf::Style::Close};

        Doodle::Game game{&window, 60, 120};
        game.run();
    } catch (const std::exception & e) {
        std::cerr << e.what();
        return 1;
    }
    return 0;
}