#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>

#include "RenderableObject.hpp"
#include "Acceleration.hpp"
#include "LimitedVector.hpp"
#include "Platform.hpp"

namespace ddl
{
  class Player: public RenderableObject, public IUpdatable
  {
    using Base = RenderableObject;

   public:
    Player(const sf::Vector2f & pos);
    virtual ~Player() = default;

    virtual void update(float deltaTime) override;
    void jump() noexcept;
    void setMoveDirection(Direction xAccelerationDirection) noexcept;

    bool isLandedOn(const Platform & plat) const;

   private:
    Movement movement_;
  };
}

#endif
