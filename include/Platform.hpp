#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "RenderableObject.hpp"
#include "Movement.hpp"

namespace ddl
{
  class Platform: public RenderableObject, public IUpdatable
  {
   public:
    Platform(const sf::Vector2f & pos);
    virtual ~Platform() = default;
    virtual std::shared_ptr< Platform > produce(const sf::Vector2f & pos);
    virtual void onPlayerLanding();
    virtual void update(float deltaTime) override;

   protected:
    Platform(const sf::Vector2f & pos, const sf::Texture & texture);
  };

  std::unique_ptr< Platform > getRandomTypePlatform(const sf::Vector2f & cords);

  class BreakingPlatform: public Platform
  {
   public:
    explicit BreakingPlatform(const sf::Vector2f & pos);
    virtual ~BreakingPlatform() = default;
    virtual void onPlayerLanding() override;
  };

  class ShiftingPlatform: public Platform
  {
   public:
    explicit ShiftingPlatform(const sf::Vector2f & pos, float shift);
    virtual ~ShiftingPlatform() = default;
    virtual void update(float deltaTime) override;
    virtual void onPlayerLanding() override;

   private:
    float nextShift_;
    sf::Vector2f shiftTo_;
    Movement movement_;
  };

  class MovingPlatform: public Platform
  {
   public:
    explicit MovingPlatform(const sf::Vector2f & pos,
     float shift,
     const sf::Vector2f & speedLimit,
     const sf::Vector2f & acceleration);
    virtual ~MovingPlatform() = default;
    virtual void update(float deltaTime) override;

   private:
    Movement movement_;
    sf::Vector2f startingPos_;
    float shift_;
  };
}

#endif
