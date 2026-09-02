#include "universe.hpp"
#include <cmath>

Universe::Universe(int starCount) : starCount(starCount)
{
    for(int i = 0; i < starCount; i++)
    {
        stars.emplace_back();
    }
}

void Universe::generateStars(int newStarCount)
{
    starCount = newStarCount;
    stars.clear();
    for(int i = 0; i < starCount; i++)
    {
        stars.emplace_back();
    }
}

int Universe::getStarCount() const
{
    return starCount;
}

const std::vector<Star>& Universe::getStars() const
{
    return stars;
}

void Universe::setStarCount(int newStarCount)
{
    starCount = newStarCount;
}

void Universe::updateStars(float dt)
{
    for (int i = 0; i < starCount; i++)
    {
        sf::Vector2f totalForce(0.f, 0.f);

        for (int j = 0; j < starCount; j++)
        {
            if (i != j)
            {
                totalForce += calculateForce(stars[i], stars[j]);
            }
        }

        sf::Vector2f acceleration = totalForce / stars[i].getMass();
        sf::Vector2f velocity = stars[i].getVelocity() + acceleration * dt;
        sf::Vector2f position = stars[i].getPosition() + velocity * dt;

        stars[i].setAcceleration(acceleration);
        stars[i].setVelocity(velocity);
        stars[i].setPosition(position);
    }

}

void Universe::printStarpos() const
{
    std::cout << stars[0].getPosition().x << ", " << stars[0].getPosition().y << std::endl;
}

sf::Vector2f Universe::normalize(const sf::Vector2f& vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0.f)
    {
        return vector / length;
    }
    return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Universe::calculateDistance(const Star& first_object, const Star& second_object) const
{
    return second_object.getPosition() - first_object.getPosition();
}

float Universe::calculateDistanceSquared(const Star& first_object, const Star& second_object) const
{
    sf::Vector2f distance = calculateDistance(first_object, second_object);
    return distance.x * distance.x + distance.y * distance.y;
}

sf::Vector2f Universe::calculateForce(const Star& first_object, const Star& second_object)
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
