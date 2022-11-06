#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include <SFML/Graphics.hpp>

#include "IRenderable.hpp"
#include "IUpdatable.hpp"

namespace ddl
{
  class RenderableObject : public IUpdatable, public IRenderable, public sf::Sprite
  {
  public:
    RenderableObject(sf::Sprite&& sprite);
    RenderableObject(const RenderableObject & object) = default;
    virtual ~RenderableObject() = default;

    virtual void render(sf::RenderWindow & window) const override;
  };
}

#endif
