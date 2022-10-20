#ifndef GET_VECTOR_ABS_H
#define GET_VECTOR_ABS_H

#include <cmath>

#include <SFML/System/Vector2.hpp>

namespace ddl
{
    float getVectorAbs(const sf::Vector2f & vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }
}

#endif
