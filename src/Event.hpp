#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <functional>

namespace ddl
{
  class Event
  {
  public:
    using SubT = std::function< void() >;
    using StorageT = std::vector< SubT >;

    Event() noexcept;
    Event(const Event &) = default;
    Event(Event&&) noexcept = default;
    Event(const std::initializer_list< SubT > subs);
    ~Event() = default;

    void subscribe(const SubT subscriber);
    void unsubscribe(const SubT subscriber) noexcept;
    void shrink() noexcept;

    void invoke();

    const StorageT& getSubs() const noexcept;

  private:
    StorageT subscribers_;
  };
}

#endif
