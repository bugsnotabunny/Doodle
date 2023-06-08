#include "Platform.hpp"

#include <map>
#include <limits>

#include "MathFunc.hpp"
#include "Game.hpp"
#include "AssetsLoad.hpp"

namespace
{
  template < typename T >
  const T & chooseRandom(const std::vector< T > & collection)
  {
    std::random_device rd;
    std::uniform_int_distribution<> dis(0, collection.size() - 1);
    return collection[dis(rd)];
  }

  template < typename PlatformT >
  std::unique_ptr< ddl::Platform > getPlatform(const sf::Vector2f & pos)
  {
    return std::make_unique< ddl::Platform >(PlatformT{ pos });
  }

  std::unique_ptr< ddl::Platform > getMovingPlatform(const sf::Vector2f & pos)
  {
    static const std::vector< float > shifts = { ddl::gameWidth / 4, ddl::gameWidth / 4 * 2 };
    static const std::vector< sf::Vector2f > speedLimits = { { 50, 0 }, { 125, 0 } };
    static const std::vector< sf::Vector2f > accelerations = { { 50, 0 },
      { 125, 0 },
      { -50, 0 },
      { -125, 0 } };

    return std::unique_ptr< ddl::Platform >{ new ddl::MovingPlatform{ pos,
     chooseRandom(shifts),
     chooseRandom(speedLimits),
     chooseRandom(accelerations) } };
  }
}

std::unique_ptr< ddl::Platform > ddl::getRandomTypePlatform(const sf::Vector2f & cords)
{
  static const std::vector< std::unique_ptr< Platform > (*)(const sf::Vector2f &) > factories = {
    getPlatform< Platform >,
    // getPLatform< ShiftingPlatform >,
    // getPLatform< BreakingPlatform >,
    getMovingPlatform,
  };

  return chooseRandom(factories)(cords);
}

namespace
{
  const sf::Texture TEXTURE = ddl::inputTexture("platform.png");
}

void ddl::Platform::update(float)
{}

ddl::Platform::Platform(const sf::Vector2f & pos):
  RenderableObject(sf::Sprite{ TEXTURE })
{
  setPosition(pos);
}

void ddl::Platform::onPlayerLanding()
{}

std::shared_ptr< ddl::Platform > ddl::Platform::produce(const sf::Vector2f & pos)
{
  return std::make_shared< Platform >(pos);
}

ddl::Platform::Platform(const sf::Vector2f & pos, const sf::Texture & texture):
  RenderableObject(sf::Sprite{ texture })
{
  setPosition(pos);
}
