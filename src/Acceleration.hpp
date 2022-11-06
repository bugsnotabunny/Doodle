#ifndef ACCELERATION_HPP
#define ACCELERATION_HPP

#include <SFML/System/Vector2.hpp>

#include "IUpdatable.hpp"

namespace ddl
{
  template < typename SpeedT, typename AccelerationT >
  class Acceleration: public IUpdatable
  {
  public:
    Acceleration(SpeedT& speedref, const AccelerationT& acceleration);
    Acceleration(const Acceleration&) = default;
    Acceleration(Acceleration&&) = default;

    Acceleration& operator=(const Acceleration&) = default;

    const SpeedT& getSpeed() const noexcept;

    virtual void update() override;
    AccelerationT acceleration;
  private:
    SpeedT& speed_;
  };
}

template < typename SpeedT, typename AccelerationT >
ddl::Acceleration< SpeedT, AccelerationT >::Acceleration(SpeedT& speedref, const AccelerationT& acceleration):
  acceleration(acceleration),
  speed_(speedref)
{}

template < typename SpeedT, typename AccelerationT >
void ddl::Acceleration< SpeedT, AccelerationT >::update()
{
  speed_ += acceleration;
}

template < typename SpeedT, typename AccelerationT >
const SpeedT& ddl::Acceleration< SpeedT, AccelerationT >::getSpeed() const noexcept
{
  return speed_;
}


#endif
