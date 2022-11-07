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

void ddl::IPlatform::update(float)
{}

ddl::PlatformsPool::PlatformsPool(GameData& data):
  data_(data),
  storage_()
{
  shiftPlatforms(0);
}

namespace
{
  constexpr long precMaker() noexcept
  {
    return std::pow(10, precision);
  }

  using IPlatPtrT = std::shared_ptr< ddl::IPlatform >;
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

namespace
{
  void deleteOutdated(std::forward_list< IPlatPtrT >& storage)
  {
    auto prev = storage.before_begin();
    for (auto it = storage.begin(); it != storage.end(); prev = it, ++it)
    {
      while (it != storage.end() && (*it)->getPosition().y > ddl::gameHeight + epsilon)
      {
        ++it;
        storage.erase_after(prev);
      }
    }
  }

  void generatePlatformsWithAverageHOf(long long int height, std::forward_list< IPlatPtrT >& storage)
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
      storage.push_front(std::move(plat));
    }
  }
}

void ddl::PlatformsPool::shiftPlatforms(float height)
{
  deleteOutdated(storage_);
  generatePlatformsWithAverageHOf(height, storage_);
}
