#include "Acceleration.hpp"

ddl::Acceleration::Acceleration(sf::Vector2f& speedref, const sf::Vector2f& acceleration):
  acceleration(acceleration),
  speed_(speedref)
{}

void ddl::Acceleration::update()
{
  speed_ += acceleration;
}
