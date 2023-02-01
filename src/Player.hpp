#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>

#include "RenderableObject.hpp"
#include "Acceleration.hpp"
#include "LimitedVector.hpp"
#include "Platform.hpp"

namespace ddl
{
  enum Direction: char
  {
    Left = -1,
    Stop,
    Right
  };

  class Player: public RenderableObject, public IUpdatable
  {
    using Base = RenderableObject;
  public:
    Player(const sf::Vector2f& pos);
    virtual ~Player() = default;

    virtual void update(float deltaTime) override;
    void jump() noexcept;
    void setMoveDirection(Direction xAccelerationDirection) noexcept;

    bool isLandedOn(const Platform& plat) const;
  private:
    using AccelerationT = Acceleration< LimitedVector< float >, sf::Vector2f >;
    LimitedVector< float > speed_;
    sf::Vector2f acceleration_;
    Direction xAccelerationDirection_;
  };
}

#endif