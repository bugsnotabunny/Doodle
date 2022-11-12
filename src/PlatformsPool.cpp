#include "PlatformsPool.hpp"

#include "MathFunc.hpp"
#include "Game.hpp"

namespace
{
  const size_t minPlats = 1;
  const size_t maxPlats = 3;
  const size_t precision = 2;
  const long long epsilon = 100;
}

ddl::PlatformsPool ddl::PlatformsPool::produce(GameData& data)
{
  PlatformsPool result(data);
  result.shiftPlatforms(0);
  return result;
}

ddl::PlatformsPool::PlatformsPool(GameData& data) noexcept:
  data_(data),
  storage_(),
  lastGenerated(2 * epsilon),
  rndPlatCount_(minPlats, maxPlats, static_cast< int >(std::time(0))),
  rndX_(0, ddl::gameWidth, static_cast< int >(std::time(0)))
{}

namespace
{
  using IPlatPtrT = std::shared_ptr< ddl::Platform >;
  bool intersectsLowerHigherBorders(const IPlatPtrT plat, const sf::Rect< float >& doodlerRect)
  {
    return plat->getGlobalBounds().intersects(doodlerRect);
  }
}

bool ddl::PlatformsPool::anyIntersections(const Player& doodler)
{
  using namespace std::placeholders;
  return std::any_of(storage_.begin(), storage_.end(), std::bind(intersectsLowerHigherBorders, _1, doodler.getGlobalBounds()));
}

void ddl::PlatformsPool::shiftPlatforms(float height)
{
  if (lastGenerated - epsilon > height)
  {
    generatePlatformsWithAverageHOf(height);
    lastGenerated = height + epsilon / 2;
  }
}

void ddl::PlatformsPool::generatePlatformsWithAverageHOf(long long int height)
{
  using ddl::Random;

  unsigned char platsNum = rndPlatCount_.get();
  Random< long long int > rndY{(height - epsilon), (height + epsilon), static_cast< int >(std::time(0))};

  for (unsigned char i = 0; i < platsNum; ++i)
  {
    const float y = static_cast< float >(rndY.get());
    const float x = static_cast< float >(rndX_.get());

    auto plat = ddl::getRandomTypePlatform();
    plat->setPosition({x, y});

    storage_.push_front(std::move(plat));
    data_.instantiate(*(storage_.begin()));
  }
}

void ddl::PlatformsPool::deleteOutdated() noexcept
{}
