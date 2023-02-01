#include "Player.hpp"

#include <functional>
#include <utility>

#include "AssetsLoad.hpp"

namespace
{
  const sf::Texture TEXTURE = ddl::inputTexture("doodler.png");

  const float LEGS_HIT_BOX_H = 30;

  const sf::Vector2f PLAYER_SPEED_LIMIT = {5000, 10000};
  const sf::Vector2f JUMP_SPEED = {0, -700};

  const float GRAVITY = 600;
  const float HORIZINTAL_ACCELERATION_BASE = 1000;
}

ddl::Player::Player(const sf::Vector2f& pos):
  Base(sf::Sprite{TEXTURE}),
  speed_({0, 0}, PLAYER_SPEED_LIMIT),
  acceleration_({0, GRAVITY}),
  xAccelerationDirection_(Stop)
{
  setScale(0.5, 0.5);
  setPosition(pos);
}

void ddl::Player::update(float deltaTime)
{
  acceleration_.x = HORIZINTAL_ACCELERATION_BASE * xAccelerationDirection_;
  speed_ += acceleration_ * deltaTime;
  auto diff = speed_.getVec() * deltaTime;
  Base::move(diff);
}

void ddl::Player::jump() noexcept
{
  speed_.setVec(JUMP_SPEED);
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
