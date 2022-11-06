#ifndef LIMITED_VECTOR_HPP
#define LIMITED_VECTOR_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>

namespace ddl
{
  template < typename ValT >
  class LimitedVector
  {
  public:
    LimitedVector(const sf::Vector2< ValT >& vec, const sf::Vector2< ValT >& abslimit) noexcept;
    LimitedVector(const LimitedVector&) = default;
    LimitedVector(LimitedVector&&) noexcept = default;

    LimitedVector& operator=(const LimitedVector&) = default;
    LimitedVector& operator=(LimitedVector&&) noexcept = default;

    void setVec(const sf::Vector2< ValT >& newVec) noexcept;
    const sf::Vector2< ValT >& getVec() const noexcept;

    void setLimit(const sf::Vector2< ValT >& abslimit) noexcept;
    const sf::Vector2< ValT >& getLimit() const noexcept;

    LimitedVector& operator+=(const sf::Vector2< ValT >& vec) noexcept;
    LimitedVector& operator-=(const sf::Vector2< ValT >& vec) noexcept;
    LimitedVector& operator*=(ValT val) noexcept;
  private:
    sf::Vector2< ValT > vec_;
    sf::Vector2< ValT > abslimit_;
  };
}

template < typename ValT >
ddl::LimitedVector< ValT >::LimitedVector(const sf::Vector2< ValT >& vec, const sf::Vector2< ValT >& abslimit) noexcept:
  vec_(vec),
  abslimit_(abslimit)
{}

template < typename ValT >
void ddl::LimitedVector< ValT >::setVec(const sf::Vector2< ValT >& vec) noexcept
{
  vec_.x = std::abs(vec.x) < abslimit_.x ? vec.x : std::copysignf(abslimit_.x, vec.x);
  vec_.y = std::abs(vec.y) < abslimit_.y ? vec.y : std::copysignf(abslimit_.y, vec.y);
}

template < typename ValT >
const sf::Vector2< ValT >& ddl::LimitedVector< ValT >::getVec() const noexcept
{
  return vec_;
}

template < typename ValT >
void ddl::LimitedVector< ValT >::setLimit(const sf::Vector2< ValT >& abslimit) noexcept
{
  abslimit_ = abslimit;
}

template < typename ValT >
const sf::Vector2< ValT >& ddl::LimitedVector< ValT >::getLimit() const noexcept
{
  return abslimit_;
}

template < typename ValT >
ddl::LimitedVector< ValT >& ddl::LimitedVector< ValT >::operator+=(const sf::Vector2< ValT >& vec) noexcept
{
  sf::Vector2< ValT > newVec = vec_ + vec;
  setVec(newVec);
  return *this;
}

template < typename ValT >
ddl::LimitedVector< ValT >& ddl::LimitedVector< ValT >::operator-=(const sf::Vector2< ValT >& vec) noexcept
{
  sf::Vector2< ValT > newVec = vec_ - vec;
  setVec(newVec);
  return *this;
}

template < typename ValT >
ddl::LimitedVector< ValT >& ddl::LimitedVector< ValT >::operator*=(const ValT val) noexcept
{
  sf::Vector2< ValT > newVec = vec_ * val;
  setVec(newVec);
  return *this;
}

#endif
