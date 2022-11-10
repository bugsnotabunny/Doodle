#include "PlatformsPool.hpp"

#include "MathFunc.hpp"
#include "Game.hpp"

namespace
{
  const size_t minPlats = 2;
  const size_t maxPlats = 5;
  const size_t precision = 2;
  const long long epsilon = 1000;
}

ddl::PlatformsPool ddl::PlatformsPool::produce(GameData& data)
{
  PlatformsPool result(data);
  result.shiftPlatforms(0);
  return result;
}

ddl::PlatformsPool::PlatformsPool(GameData& data) noexcept:
  data_(data),
  storage_()
{}

namespace
{
  constexpr long precMaker() noexcept
  {
    return std::pow(10, precision);
  }

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
  generatePlatformsWithAverageHOf(height);
}

void ddl::PlatformsPool::generatePlatformsWithAverageHOf(long long int height)
{
  using ddl::Random;

  unsigned char platsNum = 0;
  {
    Random< unsigned char > rndPlatCount{minPlats, maxPlats, static_cast< int >(std::time(0))};
    platsNum = rndPlatCount.get();
  }

  Random< long long int > rndY{(height - epsilon) * precMaker(), (height + epsilon) * precMaker(), static_cast< int >(std::time(0))};
  Random< long long int > rndX{0, ddl::gameWidth * precMaker(), static_cast< int >(std::time(0))};
  for (unsigned char i = 0; i < platsNum; ++i)
  {
    const float y = static_cast< float >(rndY.get()) / precMaker();
    const float x = static_cast< float >(rndX.get()) / precMaker();

    auto plat = ddl::getRandomTypePlatform();
    plat->setPosition({x, y});

    storage_.push_front(std::move(plat));
    data_.instantiate(*(storage_.begin()));
  }
}

void ddl::PlatformsPool::deleteOutdated() noexcept
{
  auto prev = storage_.before_begin();
  for (auto it = storage_.begin(); it != storage_.end(); prev = it, ++it)
  {
    while (it != storage_.end() && (*it)->getPosition().y > ddl::gameHeight + epsilon)
    {
      storage_.erase_after(prev);
      ++it;
    }
  }
  data_.clearDeallocated();
}
