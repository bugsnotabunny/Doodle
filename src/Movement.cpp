#include "Movement.hpp"

ddl::Movement::Movement(const sf::Vector2f & accelerationValue,
 const LimitedVector< float > & speed):
  speed_(speed),
  accelerationValue_(accelerationValue)
{}

const ddl::LimitedVector< float > & ddl::Movement::getSpeed() const
{
  return speed_;
}

const sf::Vector2f & ddl::Movement::getAcceleration() const
{
  return accelerationValue_;
}

void ddl::Movement::update(float deltaTime)
{
  speed_ += accelerationValue_ * deltaTime;
}

void ddl::Movement::setAccelerationValue(const sf::Vector2f & val)
{
  accelerationValue_ = val;
}

void ddl::Movement::setSpeedValue(const sf::Vector2f & val)
{
  speed_.setVec(val);
}
