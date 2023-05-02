#include <iostream>

#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
  try
  {
    sf::RenderWindow window{};
    window.create(sf::VideoMode(ddl::gameWidth, ddl::gameHeight, 32),
     "Doodle Jump (not really)",
     sf::Style::Titlebar | sf::Style::Close);
    ddl::run(window, 120);
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
