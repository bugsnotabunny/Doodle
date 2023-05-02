#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <SFML/Graphics.hpp>

#include "IRenderable.hpp"
#include "IUpdatable.hpp"

namespace ddl
{
  class RenderableObject: public IRenderable, public sf::Sprite
  {
   public:
    RenderableObject(sf::Sprite && sprite);
    RenderableObject(const RenderableObject & object) = default;
    virtual ~RenderableObject() = default;

    virtual void render(sf::RenderWindow & window) const override;
  };
}

#endif
