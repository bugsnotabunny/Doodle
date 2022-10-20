#ifndef ACCELERATION_HPP
#define ACCELERATION_HPP

#include <SFML/System/Vector2.hpp>

#include "IUpdatable.hpp"

namespace ddl
{
  const float gravity = 10;

  class Acceleration: IUpdatable
  {
  public:
    Acceleration(sf::Vector2f& speedref, const sf::Vector2f& acceleration);
    ~Acceleration() = default;
    void update() override;
    sf::Vector2f acceleration;
  private:
    sf::Vector2f& speed_;
  };
}

#endif
