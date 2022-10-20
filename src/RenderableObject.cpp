#include "RenderableObject.hpp"

ddl::RenderableObject::RenderableObject(sf::Sprite && sprite):
  sprite_(sprite)
{}

void ddl::RenderableObject::render(sf::RenderWindow & window) const
{
  window.draw(sprite_);
}
