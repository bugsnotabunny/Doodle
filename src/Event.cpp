#include "Event.hpp"

#include <algorithm>

ddl::Event::Event() noexcept:
  subscribers_()
{}

ddl::Event::Event(const std::initializer_list< SubT > subs) noexcept:
  subscribers_(subs)
{}

void ddl::Event::subscribe(const SubT subscriber)
{
  subscribers_.push_back(std::move(subscriber));
}

void ddl::Event::unsubscribe(const SubT subscriber) noexcept
{
  subscribers_.erase(std::find(subscribers_.begin(), subscribers_.end(), subscriber));
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