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
    sf::CircleShape shape;
    bool delete_flag = false;
    float radius;
    float mass;

    public:

    //default constructor initialized with random position
    Star(sf::Vector2f position = Random::getVector2f(SCREEN_WIDTH, SCREEN_HEIGHT)) : position(position)
    {   
        

        acceleration = sf::Vector2f(0.f, 0.f);
        velocity = sf::Vector2f(0.f, 0.f);
        mass = Random::getFloat(1.0f, 25.f);
        radius = Random::getFloat(2.f, 10.f);
    }

    //Getters
    sf::Vector2f getPosition() const
    {
        return position;
    }

    float getRadius() const
    {
        return radius;
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

    bool getDeleteFlag() const
    {
        return delete_flag;
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
    void setDeleteFlag(bool flag)
    {
        delete_flag = flag;
    }

    
};