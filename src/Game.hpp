#ifndef GAME_HPP
#define GAME_HPP

#include <deque>
#include <memory>

#include <SFML/Graphics.hpp>

#include "IRenderable.hpp"
#include "IUpdatable.hpp"

namespace ddl
{
  const unsigned gameHeight = 768;
  const unsigned gameWidth = gameHeight / 3 * 2;

  void run(sf::RenderWindow& window, unsigned short wishedFPS);
}

#endif
