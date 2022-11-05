#ifndef GAME_HPP
#define GAME_HPP

#include <deque>
#include <memory>

#include <SFML/Graphics.hpp>

#include "IRenderable.hpp"
#include "IUpdatable.hpp"

namespace ddl
{
  struct GameData
  {
  private:
    template< typename T >
    using Storage = std::vector< T >;
  public:
    template< typename T >
    std::shared_ptr< T > instantiate(T&& object);

    using Renderables = Storage< std::weak_ptr< IRenderable > >;
    using Updatables = Storage< std::weak_ptr< IUpdatable > >;

    Updatables updatables;
    Renderables renderables;
  };

  void run(sf::RenderWindow& window, unsigned short wishedFPS, unsigned short updatesPerFrame);
}

template< typename T>
std::shared_ptr< T > ddl::GameData::instantiate(T&& object)
{
  auto result = std::make_shared< T >(object);
  if constexpr(std::is_base_of< IRenderable, T >::value)
  {
    renderables.push_back(result);
  }
  if constexpr(std::is_base_of< IUpdatable, T >::value)
  {
    updatables.push_back(result);
  }
  return result;
}

#endif
