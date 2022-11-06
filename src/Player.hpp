#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>

#include "RenderableObject.hpp"
#include "Acceleration.hpp"
#include "LimitedVector.hpp"

namespace ddl
{
  class Player: public RenderableObject, public IUpdatable
  {
    using Base = RenderableObject;
  public:
    Player(sf::Sprite&& sprite);
    virtual ~Player() = default;

    virtual void update(float deltaTime) override;
    void jump() noexcept;

    LimitedVector< float > speed;
  };
}

#endif