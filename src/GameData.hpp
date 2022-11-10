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
    GameData() noexcept;

    template< typename T >
    std::shared_ptr< T > instantiate(T&& object);
    template< typename T >
    void instantiate(std::shared_ptr< T >& object);

    void clearDeallocated() noexcept;
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
  private:
    using Renderables = Storage< std::weak_ptr< IRenderable > >;
    using Updatables = Storage< std::weak_ptr< IUpdatable > >;

    Updatables updatables_;
    Renderables renderables_;
  };
}

template< typename T>
std::shared_ptr< T > ddl::GameData::instantiate(T&& object)
{
  auto result = std::make_shared< T >(object);
  if constexpr(std::is_base_of< IRenderable, T >::value)
  {
    renderables_.push_front(result);
  }
  if constexpr(std::is_base_of< IUpdatable, T >::value)
  {
    updatables_.push_front(result);
  }
  return result;
}

template< typename T >
void ddl::GameData::instantiate(std::shared_ptr< T >& object)
{
  if constexpr(std::is_base_of< IRenderable, T >::value)
  {
    renderables_.push_front(object);
  }
  if constexpr(std::is_base_of< IUpdatable, T >::value)
  {
    updatables_.push_front(object);
  }
}

#endif
