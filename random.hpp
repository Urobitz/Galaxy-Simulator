#pragma once

#include <random>
#include <SFML/System/Vector2.hpp>

namespace Random
{
    // Random engine
    inline std::mt19937 engine(std::random_device{}());

    // Integer random
    inline int getInt(int min, int max)
    {
        static std::uniform_int_distribution<int> dist;

        return dist(
            engine,
            decltype(dist)::param_type(min, max)
        );
    }

    // Float random
    inline float getFloat(float min, float max)
    {
        static std::uniform_real_distribution<float> dist;

        return dist(
            engine,
            decltype(dist)::param_type(min, max)
        );
    }

    // 0.0 -> 1.0 float
    inline float getNormalizedFloat()
    {
        static std::uniform_real_distribution<float> dist(0.f, 1.f);

        return dist(engine);
    }

    // Random 2D vector
    inline sf::Vector2f getVector2f(float width, float height)
    {
        return {
            getFloat(0.f, width),
            getFloat(0.f, height)
        };
    }

    // Optional: deterministic seed
    inline void setSeed(unsigned int seed)
    {
        engine.seed(seed);
    }
}