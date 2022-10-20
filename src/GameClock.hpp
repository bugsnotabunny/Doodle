#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H

#include <SFML/System.hpp>

#include "IUpdatable.hpp"

namespace ddl
{
  class GameClock: IUpdatable
  {
  public:
    GameClock();
    sf::Time getTimeFromLaunch();
    sf::Time getTimeFromUpdate();
    void update() override;
  private:
    sf::Clock fromLastUpdate_;
    sf::Clock fromLaunch_;
  };
}

#endif