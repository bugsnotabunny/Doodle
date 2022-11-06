#include "MathFunc.hpp"

#include <cmath>

float ddl::getVectorAbs(const sf::Vector2f& vector) noexcept
{
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}