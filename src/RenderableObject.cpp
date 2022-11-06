#include "RenderableObject.hpp"

ddl::RenderableObject::RenderableObject(sf::Sprite && sprite):
  sf::Sprite(sprite)
{}

void ddl::RenderableObject::render(sf::RenderWindow & window) const
{
  window.draw(*this);
}
