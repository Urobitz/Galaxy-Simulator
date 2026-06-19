#pragma once
#include "star.hpp"
#include "QuadTree.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
//arbi
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define G 1.0f
#define SOFTENING 0.1f

class Universe
{
    private:
        int starCount;
        std::vector<Star> stars;
        QuadTree tree();
    public:
        Universe(int starCount = 1000);

        //Used to regenerate stars with a new star count
        void generateStars(int newStarCount);

        //Getters
        int getStarCount() const;
        //getArray of stars
        const std::vector<Star>& getStars() const;

        //Setters
        void setStarCount(int newStarCount);

        void updateStars(float dt);

        //used for testing purposes, will be removed later
        void printStarpos() const;

        //Math functions
        sf::Vector2f normalize(const sf::Vector2f& vector);
        sf::Vector2f calculateDistance(const Star& first_object, const Star& second_object) const;
        float calculateDistanceSquared(const Star& first_object, const Star& second_object) const;
        sf::Vector2f calculateForce(const Star& first_object, const Star& second_object);
};
