#include "star.hpp"

Star::Star(sf::Vector2f position) : position(position)
{
    acceleration = sf::Vector2f(0.f, 0.f);
    velocity = sf::Vector2f(0.f, 0.f);
    mass = Random::getFloat(10.0f, 50.f);
}

sf::Vector2f Star::getPosition() const
{
    return position;
}

sf::Vector2f Star::getVelocity() const
{
    return velocity;
}

sf::Vector2f Star::getAcceleration() const
{
    return acceleration;
}

float Star::getMass() const
{
    return mass;
}

bool Star::getIsCenter() const
{
    return isCenter;
}

void Star::setPosition(sf::Vector2f newPosition)
{
    if (newPosition.x < SCREEN_WIDTH || newPosition.x > SCREEN_WIDTH ||
        newPosition.y < SCREEN_HEIGHT || newPosition.y > SCREEN_HEIGHT)
    {
    }

    position = newPosition;
}

void Star::setVelocity(sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}

void Star::setAcceleration(sf::Vector2f newAcceleration)
{
    acceleration = newAcceleration;
}

void Star::setMass(float newMass)
{
    mass = newMass;
}

void Star::setIsCenter(bool center)
{
    isCenter = center;
}
