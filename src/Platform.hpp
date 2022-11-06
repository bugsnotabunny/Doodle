#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "RenderableObject.hpp"

namespace ddl
{
  class IPlatform: public RenderableObject, public IUpdatable
  {
  public:
    virtual ~IPlatform() = default;
    virtual void onPlayerLanding() = 0;
    virtual void update(float) override;
  };

  std::shared_ptr< IPlatform > getRandomPlatform(float height);

  template < typename PlatformT >
  PlatformT getPLatform(const sf::Vector2f& pos)
  {
    return PlatformT{pos};
  }

  class RegularPlatform: public IPlatform
  {
  public:
    explicit RegularPlatform(const sf::Vector2f& pos);
    virtual ~RegularPlatform() = default;
    virtual void onPlayerLanding() override;
  };

  class BreakingPlatform: public IPlatform
  {
  public:
    explicit BreakingPlatform(const sf::Vector2f& pos);
    virtual ~BreakingPlatform() = default;
    virtual void onPlayerLanding() override;
  };

  class ShiftingPlatform: public IPlatform
  {
  public:
    explicit ShiftingPlatform(const sf::Vector2f& pos);
    virtual ~ShiftingPlatform() = default;
    virtual void onPlayerLanding() override;
  };

  class MovingPlatform: public IPlatform
  {
  public:
    explicit MovingPlatform(const sf::Vector2f& pos);
    virtual ~MovingPlatform() = default;
    virtual void onPlayerLanding() override;
    virtual void update(float deltaTime) override;
  };
}

#endif