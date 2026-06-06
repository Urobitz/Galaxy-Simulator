#pragma once
#include "star.hpp"
#include <SFML/Graphics.hpp>
#include "QuadTree.hpp"
//arbi
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define G 1.0f
#define SOFTENING 0.1f
#define THETA 0.5f

class Universe
{
    private:
        int starCount;
        std::vector<Star> stars;
        QuadTree quadTree;
    public:

        Universe(int starCount = 1000) : starCount(starCount), quadTree()
        {
            for(int i = 0; i < starCount; i++)
            {
                stars.emplace_back();
            }
        }

        //Used to regenerate stars with a new star count
        void generateStars(int newStarCount)
        {
            starCount = newStarCount;
            stars.clear();
            for(int i = 0; i < starCount; i++)
            {
                stars.emplace_back();
            }
        }

        //Getters
        int getStarCount() const
        {
            return starCount;
        }
        //getArray of stars
        const std::vector<Star>& getStars() const
        {
            return stars;
        }

        //Setters

        void setStarCount(int newStarCount)
        {
            starCount = newStarCount;
        }

        void updateStars(float dt)
        {

            quadTree.clearTree();

            for(Star& star : stars)
            {
                quadTree.insert(&star);
            }

            quadTree.calculateCenterOfMass();

            for(Star& star : stars)
            {
               sf::Vector2f force = barnesHutForce(star, 0, quadTree);
                star.setAcceleration(force / star.getMass());
                star.setVelocity(star.getVelocity() + star.getAcceleration() * dt);
                star.setPosition(star.getPosition() + star.getVelocity() * dt);
            }

            //move half a step using current velocity
            for(Star& star : stars)
            {   

                star.setVelocity(star.getVelocity() + star.getAcceleration() * (dt/2));
            }
            
            //recalculate acceleration based on new positions
            for(Star& star : stars)
            {
                star.setAcceleration({0.f, 0.f});

                for(Star& star2 : stars)
                {
                    if(&star != &star2)
                    {
                        star.setAcceleration(star.getAcceleration() + calculateForce(star, star2) / star.getMass());
                    }
                }
            }

            //move the other half of the step using new velocity
            for(Star& star : stars)
            {
                star.setVelocity(star.getVelocity() + star.getAcceleration() * (dt/2));
                star.setPosition(star.getPosition() + star.getVelocity() * dt);
            }
        }
        //used for testing purposes, will be removed later
        void printStarpos() const
        {
            std::cout << stars[0].getPosition().x << ", " << stars[0].getPosition().y << std::endl;
        }

        //Math functions
        sf::Vector2f normalize(const sf::Vector2f& vector)
        {
            float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
            if (length != 0.f)
            {
                return vector / length;
            }
            return sf::Vector2f(0.f, 0.f);
        }
        
        sf::Vector2f calculateDistance(const Star& first_object, const Star& second_object) const
        {
            return second_object.getPosition() - first_object.getPosition();
        }

        float calculateDistanceSquared(const Star& first_object, const Star& second_object) const
        {
            sf::Vector2f distance = calculateDistance(first_object, second_object);
            return distance.x * distance.x + distance.y * distance.y;
        }

        sf::Vector2f calculateForce(const Star& first_object, const Star& second_object)
        {
            sf::Vector2f direction = normalize(calculateDistance(first_object, second_object));
            float distSqr = calculateDistanceSquared(first_object, second_object) + SOFTENING; 
            float forceMagnitude = (G * first_object.getMass() * second_object.getMass()) / (distSqr);
            if(distSqr < 0.1)
            {
                std::cout << "low distance deteceted!!\n log: " << distSqr << std::endl << "force: " << forceMagnitude << std::endl;
            }
            return direction * forceMagnitude;
        }

        sf::Vector2f calculateForce(const Star& star, sf::Vector2f otherPos, float otherMass)
        {
            sf::Vector2f diff = otherPos - star.getPosition();
            sf::Vector2f direction = normalize(diff);
            float distSqr = (diff.x * diff.x + diff.y * diff.y) + SOFTENING;
            float forceMagnitude = (G * star.getMass() * otherMass) / distSqr;
            return direction * forceMagnitude;
        }

        sf::Vector2f barnesHutForce(const Star& star, int quadNodeIndex, const QuadTree& tree)
        {
            const QuadNode& node = tree.nodes[quadNodeIndex];
            sf::Vector2f force(0.f, 0.f);

            if(node.totalMass == 0.f)
            {
                return force;
            }

            if(node.isLeaf())
            {
                for(Star* otherStar : node.nodeStars)
                {
                    if(otherStar != &star)
                    {
                        force += calculateForce(star, *otherStar);
                    }
                }

                return force;
            }

            float s = node.nodeBoundary.halfSize * 2; // Size of the region
            float d = std::sqrt(calculateDistanceSquared(star, Star(node.centerOfMass))); // Distance from star to center of mass
            if(s/d < THETA)
            {
                return calculateForce(star, node.centerOfMass, node.totalMass);
            }
            
            for(int i  = 0; i < 4; i++)
            {
                if(node.children[i] != -1)
                {
                    force += barnesHutForce(star, node.children[i], tree);
                }
            }
            return force;
        }
};


/*
       sf::Vector2f calculateDistance(const sf::Vector2f& object)
        {
            sf::Vector2f center(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
            
            return normalize(center - object);
        }

        sf::Vector2f tangentDirection(const sf::Vector2f& direction)
        {
            sf::Vector2f tangent(direction.y, -direction.x);
            tangent = normalize(tangent);
        
            return tangent;
        }
*/