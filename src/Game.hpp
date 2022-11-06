#ifndef GAME_HPP
#define GAME_HPP

#include <deque>
#include <memory>

#include <SFML/Graphics.hpp>

#include "IRenderable.hpp"
#include "IUpdatable.hpp"

namespace ddl
{
  void run(sf::RenderWindow& window, unsigned short wishedFPS, unsigned short updatesPerFrame);
}

#endif
