#ifndef I_RENDERABLE_HPP
#define I_RENDERABLE_HPP

#include <SFML/Graphics.hpp>

namespace ddl
{
  class IRenderable
  {
   public:
    virtual ~IRenderable() = default;
    virtual void render(sf::RenderWindow & window) const = 0;
  };
}

#endif
