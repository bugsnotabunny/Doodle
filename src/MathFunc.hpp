#ifndef MATH_FUNC_HPP
#define MATH_FUNC_HPP

#include <random>

#include <SFML/System/Vector2.hpp>

namespace ddl
{
  float getVectorAbs(const sf::Vector2f& vector) noexcept;

  class Random
  {
  public:
    Random(int start, int stop, int seed) noexcept;
    int get() noexcept;
  private:
    std::mt19937 gen_;
    std::uniform_int_distribution<> distr_;
  };
}

#endif
