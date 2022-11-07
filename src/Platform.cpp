#include "Platform.hpp"

#include <map>
#include <limits>

#include "MathFunc.hpp"
#include "Game.hpp"
#include "InputTexture.hpp"

namespace
{
  template < typename PlatformT >
  PlatformT getPLatform(const sf::Vector2f& pos)
  {
    return PlatformT{pos};
  }
}

std::shared_ptr< ddl::Platform > ddl::getRandomTypePlatform()
{
  return std::make_shared< Platform >(getPLatform< Platform >({0, 0}));
}

namespace
{
  namespace PlatformDetail
  {
    const sf::Texture texture = ddl::inputTexture("platform.png");
  }
}

void ddl::Platform::update(float)
{}

ddl::Platform::Platform(const sf::Vector2f& pos):
  RenderableObject(sf::Sprite{PlatformDetail::texture})
{
  setPosition(pos);
}

void ddl::Platform::onPlayerLanding()
{}
