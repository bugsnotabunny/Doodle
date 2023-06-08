#include "Platform.hpp"

#include "AssetsLoad.hpp"

#include <iostream>

namespace
{
  const sf::Texture TEXTURE = ddl::inputTexture("platform_moving.png");
}

ddl::MovingPlatform::MovingPlatform(const sf::Vector2f & pos,
 float shift,
 const sf::Vector2f & speedLimit,
 const sf::Vector2f & acceleration):
  Platform(pos, TEXTURE),
  movement_(acceleration, { { 0, 0 }, speedLimit }),
  startingPos_(pos),
  shift_(shift)
{}

void ddl::MovingPlatform::update(float deltaTime)
{
  const bool touchedRightBorder = getPosition().x - startingPos_.x > shift_;
  const bool touchedLeftBorder = getPosition().x - startingPos_.x < -shift_;
  if (touchedRightBorder)
  {
    sf::Vector2f accelerationVal = movement_.getAcceleration();
    if (accelerationVal.x > 0)
    {
      accelerationVal.x *= -1;
    }
    movement_.setAccelerationValue(accelerationVal);
  }
  else if (touchedLeftBorder)
  {
    sf::Vector2f accelerationVal = movement_.getAcceleration();
    if (accelerationVal.x < 0)
    {
      accelerationVal.x *= -1;
    }
    movement_.setAccelerationValue(accelerationVal);
  }
  movement_.update(deltaTime);
  sf::Vector2f diff = movement_.getSpeed().getVec() * deltaTime;
  move(diff);
}
