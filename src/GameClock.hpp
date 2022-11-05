#ifndef GAME_CLOCK_HPP
#define GAME_CLOCK_HPP

#include <SFML/System.hpp>

#include "IUpdatable.hpp"

namespace ddl
{
  class GameClock: public IUpdatable
  {
  public:
    GameClock();
    sf::Time getTimeFromLaunch();
    sf::Time getTimeFromUpdate();
    void update() override;
  private:
    sf::Clock fromLaunch_;
    sf::Clock fromLastUpdate_;
  };
}

#endif