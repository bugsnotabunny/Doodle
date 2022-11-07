#ifndef MATH_FUNC_HPP
#define MATH_FUNC_HPP

#include <random>

#include <SFML/System/Vector2.hpp>

namespace ddl
{
  float getVectorAbs(const sf::Vector2f& vector) noexcept;

  template < typename int_t >
  class Random
  {
  public:
    Random(int_t start, int_t stop, int seed) noexcept;
    int_t get() noexcept;
  private:
    std::mt19937 gen_;
    std::uniform_int_distribution< int_t > distr_;
  };
}

template < typename int_t >
ddl::Random< int_t >::Random(int_t start, int_t end, int seed) noexcept:
  gen_(seed),
  distr_(start, end)
{}

template < typename int_t >
int_t ddl::Random< int_t >::get() noexcept
{
  return distr_(gen_);
}

#endif
