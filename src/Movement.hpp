#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "IUpdatable.hpp"
#include "LimitedVector.hpp"

namespace ddl
{
  enum class Direction : int8_t
  {
    Left = -1,
    Stop,
    Right
  };

  class Movement: public IUpdatable
  {
   public:
    Movement(const sf::Vector2f & accelerationValue, const LimitedVector< float > & speed);
    Movement(const Movement &) = default;
    Movement(Movement &&) = default;

    const LimitedVector< float > & getSpeed() const;
    const sf::Vector2f & getAcceleration() const;

    virtual void update(float deltaTime) override;

    void setAccelerationValue(const sf::Vector2f & val);
    void setSpeedValue(const sf::Vector2f & val);

   private:
    LimitedVector< float > speed_;
    sf::Vector2f accelerationValue_;
  };
}

#endif
