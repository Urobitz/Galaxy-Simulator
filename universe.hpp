#pragma once
#include "star.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <algorithm>
//arbi
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define G 1.0f
#define SOFTENING 0.5f
#define Cell_SIZE 50.0f

struct Cell
{
    private:
    int x;
    int y;

    public:

    Cell(int x, int y) : x(x), y(y) {}

    //getters

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }
};

class Universe
{
    private:
        int starCount;
        std::vector<Star> stars;
        std::unordered_map<int, std::vector<Star*>> starGrid;
    public:

        Universe(int starCount = 1000) : starCount(starCount)
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

        void updateStars(float dt)
        {
            //Used to test the forces and movement of stars, will be removed later

           /* stars[0].setAcceleration(sf::Vector2f(0.f, 0.f));
            stars[0].setMass(1000.0f);
            stars[0].setIsCenter(true);*/

            //move half a step using current velocity
            for(Star& star : stars)
            {   

                star.setVelocity(star.getVelocity() + star.getAcceleration() * (dt/2));
            }
            
            //Update position by half step
            for(Star& star : stars) 
            {
                star.setPosition(star.getPosition() + star.getVelocity() * dt);
            }

            //Update grid
            buildGrid();

            checkCollision();

            stars.erase(std::remove_if(stars.begin(), stars.end(), [](const Star& s) { return s.getDeleteFlag(); }), stars.end());

            //Calculate forces and update acceleration
            for(Star& star : stars)
            {
                star.setAcceleration({0.f, 0.f});
                Cell cell = getCell(star.getPosition());
                for(int dx = -1; dx <= 1; dx++)
                {
                    for(int dy = -1; dy <= 1; dy++)
                    {
                        Cell neighborCell(cell.getX() + dx, cell.getY() + dy);
                        int key = hash(neighborCell);

                        if(starGrid.find(key) != starGrid.end())
                        {
                            for(Star* otherStar : starGrid[key])
                            {
                                if(&star != otherStar)
                                {
                                    star.setAcceleration(star.getAcceleration() + calculateForce(star, *otherStar) / star.getMass());
                                }
                            }
                        }
                    }
                }

                for(Star& star : stars) 
                {
                    star.setVelocity(star.getVelocity() + star.getAcceleration() * (dt * 0.5f));
                }
            }

    
        }


        sf::Vector2f gridCoordinate(const sf::Vector2f& position) const
        {
            return sf::Vector2f(std::floor(position.x / Cell_SIZE), std::floor(position.y / Cell_SIZE));
        }

        Cell getCell(const sf::Vector2f& position) const
        {
            return Cell{static_cast<int>(std::floor(position.x / Cell_SIZE)),static_cast<int>(std::floor(position.y / Cell_SIZE))};
        }

        int hash(const Cell& cell) const
        {
            return cell.getX() * 73856093 ^ cell.getY() * 19349663;
        }

        void buildGrid()
        {
            starGrid.clear();
            for(Star& star : stars)
            {
                Cell cell = getCell(star.getPosition());
                int key = hash(cell);
                starGrid[key].push_back(&star);
            }
        }

        void checkCollision()
        {
            for (Star& star : stars)
            {
                Cell cell = getCell(star.getPosition());

                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        Cell neighborCell(cell.getX() + dx, cell.getY() + dy);
                        int key = hash(neighborCell);

                        if (starGrid.find(key) != starGrid.end())
                        {
                            for (Star* otherStar : starGrid[key])
                            {
                                if (&star != otherStar)
                                {
                                    float distanceSquared = calculateDistanceSquared(star, *otherStar);
                                    float radiusSum = star.getRadius() + otherStar->getRadius();

                                    if (distanceSquared < (radiusSum * radiusSum))
                                    {
                                        star.setDeleteFlag(true);
                                        otherStar->setDeleteFlag(true);
                                    }
                                }
                            }
                        }
                    }
                }
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
};