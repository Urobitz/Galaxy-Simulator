#include <SFML/Graphics.hpp>
#include "random.hpp"
#include <iostream>
#pragma once

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

    //default constructor initialized with random position
    Star(sf::Vector2f position = Random::getVector2f(SCREEN_WIDTH, SCREEN_HEIGHT)) : position(position)
    {   
        

        velocity = sf::Vector2f(0.f, 0.f);
        mass = Random::getFloat(10.0f, 50.f);
    }

    //Getters
    sf::Vector2f getPosition() const
    {
        return position;
    }
    
    sf::Vector2f getVelocity() const
    {
        return velocity;
    }

    sf::Vector2f getAcceleration() const
    {
        return acceleration;
    }

    float getMass() const
    {
        return mass;
    }
    //for testing purposes, will be removed later
    bool getIsCenter() const
    {
        return isCenter;
    }

    //Setter
    void setPosition(sf::Vector2f newPosition)
    {
        if (newPosition.x < SCREEN_WIDTH || newPosition.x > SCREEN_WIDTH ||
            newPosition.y < SCREEN_HEIGHT || newPosition.y > SCREEN_HEIGHT)
        {
        }

        position = newPosition;
    }

    void setVelocity(sf::Vector2f newVelocity)
    {
        velocity = newVelocity;
    }

    void setAcceleration(sf::Vector2f newAcceleration)
    {
        acceleration = newAcceleration;
    }
    
    void setMass(float newMass)
    {
        mass = newMass;
    }

    //for testing purposes, will be removed later
    void setIsCenter(bool center)
    {
        isCenter = center;
    }

    
};