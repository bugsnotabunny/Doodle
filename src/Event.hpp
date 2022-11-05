#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <functional>

namespace ddl
{
  class Event
  {
  public:
    using StorageT = std::vector< std::function< void() > >;

    Event() noexcept;
    Event(const Event&) = default;
    Event(Event&&) noexcept = default;
    Event(const std::initializer_list< std::function< void() > >& subs);
    ~Event() = default;

    void subscribe(std::function< void() > subscriber);
    void unsubscribe() noexcept;
    void shrink() noexcept;

    void invoke();

    const StorageT& getSubs() const noexcept;
  private:
    StorageT subscribers_;
  };
}

#endif
