#ifndef I_UPDATABLE_HPP
#define I_UPDATABLE_HPP

#include <memory>

#include "Game.hpp"

namespace ddl
{
  class IUpdatable
  {
  public:
    virtual ~IUpdatable() = default;
    virtual void update() = 0;
  };
}

#endif