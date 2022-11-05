#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

int main()
{
  try
  {
    const unsigned gameHeight = 768;
    const unsigned gameWidth = gameHeight / 3 * 2;

    sf::RenderWindow window;
    window.setActive(false);
    std::string test("Hello World!");
    window.setTitle(test);

    // sf::RenderWindow window{};
    // window.create(sf::VideoMode(gameWidth, gameHeight, 32), "Doodle Jump (not really)", sf::Style::Titlebar | sf::Style::Close);

    // ddl::run(window, 60, 2);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error\n";
    return 1;
  }
  return 0;
}