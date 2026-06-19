#pragma once

#include <SFML/Graphics.hpp>
#include "random.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Star
{
    private:
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        bool isCenter = false;
        sf::CircleShape shape;
        float mass;

    public:
        Star(sf::Vector2f position = Random::getVector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

        //Getters
        sf::Vector2f getPosition() const;
        sf::Vector2f getVelocity() const;
        sf::Vector2f getAcceleration() const;
        float getMass() const;
        bool getIsCenter() const;

        //Setters
        void setPosition(sf::Vector2f newPosition);
        void setVelocity(sf::Vector2f newVelocity);
        void setAcceleration(sf::Vector2f newAcceleration);
        void setMass(float newMass);
        void setIsCenter(bool center);
};
