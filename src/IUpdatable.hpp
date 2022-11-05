#ifndef I_UPDATABLE_HPP
#define I_UPDATABLE_HPP

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