#include "Player.hpp"

#include <functional>
#include <utility>

#include "InputTexture.hpp"

namespace
{
  const sf::Texture texture = ddl::inputTexture("doodler.png");

  const float legsHitboxH = 30;

  const sf::Vector2f playerSpeedLimit = {5000, 10000};
  const sf::Vector2f jumpSpeed = {0, -900};

  const float gravity = 1000;
  const float horizontalAccelerationBase = 1000;
}

ddl::Player::Player(const sf::Vector2f& pos):
  Base(sf::Sprite{texture}),
  speed_({0, 0}, playerSpeedLimit),
  acceleration_({0, gravity}),
  xAccelerationDirection_(Stop)
{
  setScale(0.5, 0.5);
  setPosition(pos);
}

void ddl::Player::update(float deltaTime)
{
  acceleration_.x = horizontalAccelerationBase * xAccelerationDirection_;
  speed_ += acceleration_ * deltaTime;
  auto diff = speed_.getVec() * deltaTime;
  Base::move(diff);
}

void ddl::Player::jump() noexcept
{
  speed_.setVec(jumpSpeed);
}

void ddl::Player::setMoveDirection(Direction xDirection) noexcept
{
  xAccelerationDirection_ = xDirection;
}

bool ddl::Player::isLandedOn(const ddl::Platform& plat) const
{
  auto bounds = this->getGlobalBounds();
  bounds.top += bounds.height;
  bounds.height = 1;
  return plat.getGlobalBounds().intersects(bounds);
}
