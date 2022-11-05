#include "Player.hpp"

#include <functional>

ddl::Player::Player(sf::Sprite&& sprite):
  Base(std::move(sprite)),
  speed_(0, 0),
  acceleration_(speed_, {0, gravity})
{}

void ddl::Player::update()
{
}