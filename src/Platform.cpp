#include "Platform.hpp"

#include <map>
#include <limits>

#include "MathFunc.hpp"
#include "Game.hpp"

namespace
{
  template < typename PlatformT >
  PlatformT getPLatform(const sf::Vector2f& pos)
  {
    return PlatformT{pos};
  }
}

std::shared_ptr< ddl::IPlatform > ddl::getRandomTypePlatform()
{
  return std::make_shared< RegularPlatform >(getPLatform< RegularPlatform >({0, 0}));
}
