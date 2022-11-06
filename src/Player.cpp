#include "Player.hpp"

#include <functional>
#include <utility>

namespace
{
  const sf::Vector2f playerSpeedLimit = {5000, 10000};
  const sf::Vector2f jumpSpeed = {0, -900};
}

ddl::Player::Player(sf::Sprite&& sprite):
  Base(std::move(sprite)),
  speed({0, 0}, playerSpeedLimit)
{}

void ddl::Player::update(float deltaTime)
{
  auto diff = speed.getVec() * deltaTime;
  Base::move(diff);
}

void ddl::Player::jump() noexcept
{
  speed.setVec(jumpSpeed);
}