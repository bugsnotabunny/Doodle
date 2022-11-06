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
    GameClock(const GameClock&) = default;
    GameClock(GameClock&&) = default;

    GameClock& operator=(const GameClock&) = default;
    GameClock& operator=(GameClock&&) = default;

    sf::Time getTimeFromLaunch();
    sf::Time getTimeFromUpdate();

    void update() override;
  private:
    sf::Clock fromLaunch_;
    sf::Clock fromLastUpdate_;
  };
}

#endif