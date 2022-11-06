#ifndef PLATFORM_POOL_HPP
#define PLATFORM_POOL_HPP

#include <forward_list>
#include <memory>

#include "Platform.hpp"
#include "IUpdatable.hpp"
#include "GameData.hpp"
#include "Player.hpp"

namespace ddl
{
  class PlatformsPool
  {
  public:
    PlatformsPool(GameData& data);
    bool anyIntersections(const Player& doodler);
    void shiftPlatforms(float height);
  private:
    GameData& data_;
    std::forward_list< std::shared_ptr < IPlatform > > storage_;
  };
}

#endif