#include "random.hpp"
#include <random>

namespace Random {
    static std::random_device rd;
    static std::mt19937 engine(rd());

    int getInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }

    float getFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(engine);
    }

    sf::Vector2f getVector2f(float width, float height)
    {
        return sf::Vector2f(getFloat(0.f, width), getFloat(0.f, height));
    }
}
