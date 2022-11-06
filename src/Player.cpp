#include "Player.hpp"

#include <functional>
#include <utility>

namespace
{
  const sf::Vector2f playerSpeedLimit = {20, 82};
  const sf::Vector2f jumpSpeed = {0, -200};
}

ddl::Player::Player(sf::Sprite&& sprite):
  Base(std::move(sprite)),
  speed({0, 0}, playerSpeedLimit)
{}

void ddl::Player::update()
{
  Base::move(speed.getVec());
}

void ddl::Player::jump() noexcept
{
  speed += jumpSpeed;
}