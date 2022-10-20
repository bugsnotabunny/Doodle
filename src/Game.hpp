#ifndef GAME_HPP
#define GAME_HPP

#include <deque>
#include <memory>

#include <SFML/Graphics.hpp>

#include "IRenderable.hpp"
#include "IUpdatable.hpp"
#include "GameClock.hpp"

namespace ddl
{
  class Game
  {
  public:
    Game(sf::RenderWindow& window, unsigned short wishedFPS, unsigned short updatesPerFrame);
    ~Game() = default;
    void run();
  private:
    template< typename T >
    std::shared_ptr< T > instantiate(T&& object);

    float updatesFrequency_;
    unsigned short updatesPerFrame_;
    sf::Window& window_;
    std::deque< std::shared_ptr< IUpdatable > > updatables_;
    std::deque< std::shared_ptr< IRenderable > > renderables_;
    GameClock clock_;
  };
}

template< typename T>
std::shared_ptr< T > ddl::Game::instantiate(T&& object)
{
  auto result = std::make_shared< T >(object);
  if (std::is_base_of< IRenderable, T >::value)
  {
    renderables_.push_front(*result);
  }
  if (std::is_base_of< IUpdatable, T >::value)
  {
    updatables_.push_front(*result);
  }
  return result;
}

#endif
