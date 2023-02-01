#ifndef PLATFORM_POOL_HPP
#define PLATFORM_POOL_HPP

#include <deque>
#include <memory>

#include "Platform.hpp"
#include "IUpdatable.hpp"
#include "GameData.hpp"
#include "MathFunc.hpp"
#include "Player.hpp"

namespace ddl
{
  class PlatformsPool: IUpdatable, IRenderable
  {
  public:
    PlatformsPool(const PlatformsPool&) = default;
    PlatformsPool(PlatformsPool&&) noexcept = default;
    ~PlatformsPool() = default;

    static PlatformsPool produce();
    

    struct IntersectionStatus
    {
      bool hasIntersected;
      bool isInNewBank;
    };
    IntersectionStatus anyIntersections(const Player& player) const;
    void onNewBankVisit();
    size_t getNewBankVisitsCount() const noexcept;

    void update(const float deltaTime);
    void render(sf::RenderWindow& window) const;
  private:
    class PlatformsBank: ddl::IRenderable, ddl::IUpdatable
    {
    public:
      PlatformsBank(const PlatformsBank&) = default;
      PlatformsBank(PlatformsBank&&) noexcept = default;
      ~PlatformsBank() = default;

      static PlatformsBank produce(sf::Vector2f cords, const sf::Vector2f size, size_t platsAmount);
      bool anyIntersections(const Player& doodler) const;

      void update(float deltaTime);
      void render(sf::RenderWindow & window) const;
    private:
      PlatformsBank(std::vector< std::shared_ptr < Platform > >&& platforms) noexcept;
      std::vector< std::shared_ptr < Platform > > platforms_;
    };
    PlatformsPool(std::deque< PlatformsBank >&& banks) noexcept;

    const sf::Vector2f screenSize_;
    size_t newBankVisitsCount_;
    std::deque< PlatformsBank > banks_;
  };
}

#endif