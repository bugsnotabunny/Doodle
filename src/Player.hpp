#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>

#include "RenderableObject.hpp"
#include "Acceleration.hpp"

namespace ddl
{
  class Player : public RenderableObject
  {
    using Base = RenderableObject;
  public:
    Player(sf::Sprite&& sprite);
    virtual ~Player() = default;

    virtual void update();

    virtual void modifySpeed(const sf::Vector2f & acceleration);

    virtual void modifyAcceleration(const sf::Vector2f & acceleration);
  private:
    void jump();
    sf::Vector2f speed_;
    Acceleration acceleration_;
  };
}

#endif