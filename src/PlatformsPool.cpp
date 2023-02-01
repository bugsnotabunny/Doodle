#include "PlatformsPool.hpp"

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

#include "MathFunc.hpp"
#include "RenderableObject.hpp"
#include "Game.hpp"

namespace
{
  const size_t BANKS_PER_SCREEN = 2;
  const size_t BANKS_LOWER_THAN_SCREEN = 0;
  const size_t BANKS_HIGHER_THAN_SCREEN = 1;

  const float BANK_H = ddl::gameHeight / BANKS_PER_SCREEN;
  const float BANK_W = ddl::gameWidth;

  const size_t MIN_PLATS = 1;
  const size_t MAX_PLATS = 5;
}

ddl::PlatformsPool::PlatformsBank ddl::PlatformsPool::PlatformsBank::produce(sf::Vector2f cords, sf::Vector2f size, size_t platsAmount)
{
  std::vector< std::shared_ptr < Platform > > platforms;

  using distr_t = std::uniform_real_distribution< float >;
  std::random_device rd;
  std::mt19937 gen(rd());
  distr_t distX(cords.x, size.x + cords.x);
  distr_t distY(cords.y, size.y + cords.y);

  for (size_t i = 0; i < platsAmount; ++i)
  {
    std::shared_ptr< Platform > plat = getRandomTypePlatform();
    plat->setPosition(sf::Vector2f{distX(gen), distY(gen)});
    platforms.push_back(std::move(plat));
  }

  return PlatformsBank{std::move(platforms)};
}

ddl::PlatformsPool::PlatformsBank::PlatformsBank(std::vector< std::shared_ptr < Platform > >&& platforms) noexcept:
  platforms_(platforms)
{}

void ddl::PlatformsPool::PlatformsBank::update(float deltaTime)
{
  for (auto&& plat: platforms_)
  {
    plat->update(deltaTime);
  }
}

void ddl::PlatformsPool::PlatformsBank::render(sf::RenderWindow& window) const
{
  for (auto&& plat: platforms_)
  {
    plat->render(window);
  }
}

bool ddl::PlatformsPool::PlatformsBank::anyIntersections(const Player& player) const
{
  struct PlayerIsLandedOn
  {
    const Player& player;

    bool operator()(const std::shared_ptr< Platform >& plat) const
    {
      return player.isLandedOn(*plat);
    }
  };

  return std::any_of(platforms_.begin(), platforms_.end(), PlayerIsLandedOn{player});
}

ddl::PlatformsPool ddl::PlatformsPool::produce()
{
  std::deque< PlatformsBank > banks;

  using distr_t = std::uniform_int_distribution< size_t >;
  std::random_device rd;
  std::mt19937 gen(rd());
  distr_t platsNumRnd(MIN_PLATS, MAX_PLATS);

  for (int i = -BANKS_LOWER_THAN_SCREEN; i < static_cast< int >(BANKS_PER_SCREEN + BANKS_HIGHER_THAN_SCREEN); ++i)
  {
    PlatformsBank bank = PlatformsBank::produce(sf::Vector2f{0, - i * BANK_H}, sf::Vector2f{BANK_W, BANK_H}, platsNumRnd(gen));
    banks.push_back(std::move(bank));
  }

  return PlatformsPool{std::move(banks)};
}

ddl::PlatformsPool::IntersectionStatus ddl::PlatformsPool::anyIntersections(const Player& player) const
{
  IntersectionStatus result{false, false};
  result.hasIntersected = banks_.begin()->anyIntersections(player);
  result.isInNewBank = !result.hasIntersected;
  if (result.isInNewBank)
  {
    result.hasIntersected = (++banks_.begin())->anyIntersections(player);
    result.isInNewBank = result.hasIntersected;
  }
  return result;
}

void ddl::PlatformsPool::update(const float deltaTime)
{
  for (auto&& bank: banks_)
  {
    bank.update(deltaTime);
  }
}

void ddl::PlatformsPool::render(sf::RenderWindow& window) const
{
  for (auto&& bank: banks_)
  {
    bank.render(window);
  }
}

ddl::PlatformsPool::PlatformsPool(std::deque< PlatformsBank >&& banks) noexcept:
  banks_(banks)
{}

size_t ddl::PlatformsPool::getNewBankVisitsCount() const noexcept
{
  return newBankVisitsCount_;
}

void ddl::PlatformsPool::onNewBankVisit()
{
  using distr_t = std::uniform_int_distribution< size_t >;
  std::random_device rd;
  std::mt19937 gen(rd());
  distr_t platsNumRnd(MIN_PLATS, MAX_PLATS);
  const size_t visitsCount = getNewBankVisitsCount();
  auto newBank = PlatformsBank::produce(sf::Vector2f{0, visitsCount * BANK_H}, sf::Vector2f{BANK_W, BANK_H}, platsNumRnd(gen));

  banks_.pop_front();
  banks_.push_back(std::move(newBank));
}
