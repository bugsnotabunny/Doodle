#include "Event.hpp"

#include <algorithm>

ddl::Event::Event() noexcept:
  subscribers_()
{}

ddl::Event::Event(const std::initializer_list< std::function< void() > >& subs):
  subscribers_(subs)
{}

void ddl::Event::subscribe(const std::function< void() > subscriber)
{
  subscribers_.push_back(std::move(subscriber));
}

void ddl::Event::unsubscribe() noexcept
{
  subscribers_.pop_back();
}

void ddl::Event::shrink() noexcept
{
  subscribers_.shrink_to_fit();
}

void ddl::Event::invoke()
{
  for (auto&& sub : subscribers_)
  {
    sub();
  }
}

const ddl::Event::StorageT& ddl::Event::getSubs() const noexcept
{
  return subscribers_;
}