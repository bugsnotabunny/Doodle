#include "Platform.hpp"

#include "AssetsLoad.hpp"

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
  if (getPosition().x - startingPos_.x > shift_)
  {
    sf::Vector2f accelerationVal = movement_.getAcceleration();
    accelerationVal.x *= -1;
    movement_.setAccelerationValue(accelerationVal);
  }
  movement_.update(deltaTime);
}
