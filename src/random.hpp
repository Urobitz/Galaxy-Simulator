#pragma once
#include <SFML/System.hpp>

namespace Random
{
    int getInt(int min, int max);
    float getFloat(float min, float max);
    sf::Vector2f getVector2f(float width, float height);

}
