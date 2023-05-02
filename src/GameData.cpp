#include "GameData.hpp"

ddl::GameData::GameData() noexcept:
  updatables_(),
  renderables_()
{}

namespace
{
  template < typename IterT >
  IterT findBeforeFreed(IterT beforeBegin, IterT end) noexcept
  {
    auto prev = beforeBegin;
    for (auto it = beforeBegin++; it != end; prev = it, ++it)
    {
      if (it->expired())
      {
        return prev;
      }
    }
    return end;
  }

  template < typename T >
  void clearDeallocatedImpl(std::forward_list< std::weak_ptr< T > > & arr) noexcept
  {
    if (arr.empty())
    {
      return;
    }
    for (auto it = findBeforeFreed(arr.before_begin(), arr.end()); it != arr.end();
         it = findBeforeFreed(it, arr.end()))
    {
      if (it == arr.end())
      {
        return;
      }
      arr.erase_after(it);
    }
  }
}

void ddl::GameData::clearDeallocated() noexcept
{}

void ddl::GameData::update(float deltaTime)
{
  for (auto && item: updatables_)
  {
    item.lock()->update(deltaTime);
  }
}

void ddl::GameData::render(sf::RenderWindow & window)
{
  for (auto && item: renderables_)
  {
    item.lock()->render(window);
  }
}
