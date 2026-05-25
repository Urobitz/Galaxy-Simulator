#pragma once

#include <SFML/Graphics.hpp>
#include "universe.hpp"

class Renderer
{
    private:
        sf::RenderWindow window;

    public:
        //Initializes the main window
        Renderer(unsigned int width, unsigned int height, const std::string& title)
        {
            window.create(sf::VideoMode({width, height}), title);
        }

        void drawUniverse(const Universe& universe)
        {
            for(int i = 0; i < universe.getStarCount(); i++)
            {
                if(universe.getStars()[i].getIsCenter() != true)
                {
                    sf::CircleShape starShape(universe.getStars()[i].getMass() * 0.05f);
                    starShape.setFillColor(sf::Color::White);
                    starShape.setPosition(universe.getStars()[i].getPosition());
                    window.draw(starShape);
                }
                else
                {

                    //for testing purposes, will be removed later
                    sf::CircleShape starShape(2.0f);
                    starShape.setFillColor(sf::Color::Red);
                    starShape.setPosition(universe.getStars()[i].getPosition());
                    window.draw(starShape);
                }
            }
        }

        void clearWindow()
        {
            window.clear(sf::Color(0X0B213C));
        }

        void displayWindow()
        {
            window.display();
        }

        //Getters

        sf::RenderWindow& getWindow()
        {
            return window;
        }
};      
