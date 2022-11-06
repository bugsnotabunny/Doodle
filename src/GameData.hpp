#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include <memory>
#include <forward_list>

#include "IRenderable.hpp"
#include "IUpdatable.hpp"

namespace ddl
{
  struct GameData
  {
  private:
    template< typename T >
    using Storage = std::forward_list< T >;
  public:
    template< typename T >
    std::shared_ptr< T > instantiate(T&& object);

    using Renderables = Storage< std::weak_ptr< IRenderable > >;
    using Updatables = Storage< std::weak_ptr< IUpdatable > >;

    Updatables updatables;
    Renderables renderables;
  };

  struct GameTextures
  {
  public:
    sf::Texture doodler;
    sf::Texture platform;
  };
  GameTextures loadTextures();
}

template< typename T>
std::shared_ptr< T > ddl::GameData::instantiate(T&& object)
{
  auto result = std::make_shared< T >(object);
  if constexpr(std::is_base_of< IRenderable, T >::value)
  {
    renderables.push_front(result);
  }
  if constexpr(std::is_base_of< IUpdatable, T >::value)
  {
    updatables.push_front(result);
  }
  return result;
}

#endif
