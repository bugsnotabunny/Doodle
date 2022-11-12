#ifndef PLATFORM_POOL_HPP
#define PLATFORM_POOL_HPP

#include <forward_list>
#include <memory>

#include "Platform.hpp"
#include "IUpdatable.hpp"
#include "GameData.hpp"
#include "MathFunc.hpp"
#include "Player.hpp"

namespace ddl
{
  class PlatformsPool
  {
  public:
    static PlatformsPool produce(GameData& data);
    bool anyIntersections(const Player& doodler);
    void shiftPlatforms(float height);
    void deleteOutdated() noexcept;
  private:
    PlatformsPool(GameData& data) noexcept;
    void generatePlatformsWithAverageHOf(long long int height);

    GameData& data_;
    std::forward_list< std::shared_ptr < Platform > > storage_;
    float lastGenerated;
    Random< unsigned char > rndPlatCount_;
    Random< long long int > rndX_;
  };
}

#endif