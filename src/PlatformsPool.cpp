#include "PlatformsPool.hpp"

ddl::PlatformsPool::PlatformsPool(GameData& data):
  data_(data),
  storage_()
{}

namespace
{
  bool intersectsLowerHigherBorders(const ddl::IPlatform& plat, const sf::Rect< float >& doodlerRect)
  {
    return plat.getGlobalBounds().intersects(doodlerRect);
  }
}

bool ddl::PlatformsPool::anyIntersections(const Player& doodler)
{
  using namespace std::placeholders;
  return std::any_of(storage_.begin(), storage_.end(), std::bind(intersectsLowerHigherBorders, _1, doodler.getGlobalBounds()));
}

void ddl::PlatformsPool::shiftPlatforms(float height)
{

}

