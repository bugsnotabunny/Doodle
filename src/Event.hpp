#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

namespace ddl
{
  template< typename ReturnT = void, typename Args = void >
  class Event
  {
  public:
    using SubT = std::function< ReturnT(Args) >;
    using StorageT = std::vector< SubT >;

    constexpr Event() noexcept;
    constexpr Event(const Event &) = default;
    constexpr Event(Event&&) noexcept = default;
    constexpr Event(const std::initializer_list< SubT > subs);
    ~Event() = default;

    void subscribe(const SubT subscriber);
    void unsubscribe(const SubT subscriber) noexcept;
    void shrink() noexcept;

    void invoke(Args args);

    const StorageT& getSubs() const noexcept;

  private:
    StorageT subscribers_;
  };
}

template< typename ReturnT, typename Args >
constexpr ddl::Event<ReturnT, Args>::Event() noexcept:
  subscribers_()
{}

template< typename ReturnT, typename Args >
constexpr ddl::Event<ReturnT, Args>::Event(const std::initializer_list< SubT > subs) noexcept:
  subscribers_(subs)
{}

template< typename ReturnT, typename Args >
void ddl::Event<ReturnT, Args>::subscribe(const SubT subscriber)
{
  subscribers_.push_back(std::move(subscriber));
}

template< typename ReturnT, typename Args >
void ddl::Event<ReturnT, Args>::unsubscribe(const SubT subscriber) noexcept
{
  subscribers_.erase(std::find(subscriber));
}

template< typename ReturnT, typename Args >
void ddl::Event<ReturnT, Args>::shrink() noexcept
{
  subscribers_.shrink_to_fit();
}

template< typename ReturnT, typename Args >
void ddl::Event<ReturnT, Args>::invoke(Args args)
{
  for (auto&& sub : subscribers_)
  {
    sub(args);
  }
}

template< typename ReturnT, typename Args >
const ddl::Event<ReturnT, Args>::StorageT& ddl::Event<ReturnT, Args>::getSubs() const noexcept
{
  return subscribers_;
}

#endif
