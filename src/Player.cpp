#include "Player.hpp"

#include <functional>
#include <utility>
#include <type_traits>

#include "AssetsLoad.hpp"

namespace
{
  const sf::Texture TEXTURE = ddl::inputTexture("doodler.png");

  const float LEGS_HIT_BOX_H = 30;

  const sf::Vector2f PLAYER_SPEED_LIMIT = { 5000, 10000 };
  const sf::Vector2f JUMP_SPEED = { 0, -700 };

  const float GRAVITY = 600;
  const float HORIZONTAL_ACCELERATION_BASE = 1000;
}

ddl::Player::Player(const sf::Vector2f & pos):
  Base(sf::Sprite{ TEXTURE }),
  movement_({ 0, GRAVITY }, { { 0, 0 }, PLAYER_SPEED_LIMIT })
{
  setScale(0.5, 0.5);
  setPosition(pos);
}

void ddl::Player::update(float deltaTime)
{
  movement_.update(deltaTime);
  sf::Vector2f diff = movement_.getSpeed().getVec() * deltaTime;
  Base::move(diff);
}

void ddl::Player::jump() noexcept
{
  movement_.setSpeedValue(JUMP_SPEED);
}

void ddl::Player::setMoveDirection(Direction xDirection) noexcept
{
  sf::Vector2f newVal = movement_.getAcceleration();
  using under_t = std::underlying_type< Direction >::type;
  newVal.x = HORIZONTAL_ACCELERATION_BASE * static_cast< under_t >(xDirection);
  movement_.setAccelerationValue(newVal);
}

bool ddl::Player::isLandedOn(const ddl::Platform & plat) const
{
  auto bounds = this->getGlobalBounds();
  bounds.top += bounds.height;
  bounds.height = 1;
  return plat.getGlobalBounds().intersects(bounds);
}
