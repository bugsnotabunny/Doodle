#include "MathFunc.hpp"

#include <cmath>
#include <random>

float ddl::getVectorAbs(const sf::Vector2f& vector) noexcept
{
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

ddl::Random::Random(int start, int end, int seed) noexcept:
  gen_(seed),
  distr_(start, end)
{}

int ddl::Random::get() noexcept
{
  return distr_(gen_);
}