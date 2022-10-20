#include "GameClock.hpp"

ddl::GameClock::GameClock():
  fromLaunch_(),
  fromLastUpdate_()
{}

sf::Time ddl::GameClock::getTimeFromLaunch()
{
  return fromLaunch_.getElapsedTime();
}

sf::Time ddl::GameClock::getTimeFromUpdate()
{
  return fromLastUpdate_.getElapsedTime();
}

void ddl::GameClock::update()
{
  fromLastUpdate_.restart();
}
