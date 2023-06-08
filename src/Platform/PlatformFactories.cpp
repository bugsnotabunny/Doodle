#include "Platform.hpp"

#include <memory>
#include <vector>
#include <random>

#include "Game.hpp"

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
    return std::unique_ptr< ddl::Platform >(new PlatformT{ pos });
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

  std::unique_ptr< ddl::Platform > getShiftingPlatform(const sf::Vector2f & pos)
  {
    static const std::vector< float > shifts = { ddl::gameWidth / 4,
      ddl::gameWidth / 4 * 2,
      -ddl::gameWidth / 4,
      -ddl::gameWidth / 4 * 2 };
    return std::unique_ptr< ddl::Platform >{ new ddl::ShiftingPlatform{ pos,
     chooseRandom(shifts) } };
  }
}

std::unique_ptr< ddl::Platform > ddl::getRandomTypePlatform(const sf::Vector2f & cords)
{
  static const std::vector< std::unique_ptr< Platform > (*)(const sf::Vector2f &) > factories = {
    getPlatform< Platform >,
    getPlatform< BreakingPlatform >,
    getShiftingPlatform,
    getMovingPlatform,
  };

  return chooseRandom(factories)(cords);
}
