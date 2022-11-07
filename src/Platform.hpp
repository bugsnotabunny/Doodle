#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "RenderableObject.hpp"

namespace ddl
{
  class Platform: public RenderableObject, public IUpdatable
  {
  public:
    Platform(const sf::Vector2f& pos);
    virtual ~Platform() = default;
    virtual void onPlayerLanding();
    virtual void update(float) override;
  };

  std::shared_ptr< Platform > getRandomTypePlatform();

  class BreakingPlatform: public Platform
  {
  public:
    explicit BreakingPlatform(const sf::Vector2f& pos);
    virtual ~BreakingPlatform() = default;
    virtual void onPlayerLanding() override;
  };

  class ShiftingPlatform: public Platform
  {
  public:
    explicit ShiftingPlatform(const sf::Vector2f& pos);
    virtual ~ShiftingPlatform() = default;
    virtual void onPlayerLanding() override;
  };

  class MovingPlatform: public Platform
  {
  public:
    explicit MovingPlatform(const sf::Vector2f& pos);
    virtual ~MovingPlatform() = default;
    virtual void onPlayerLanding() override;
    virtual void update(float deltaTime) override;
  };
}

#endif