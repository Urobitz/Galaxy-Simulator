#pragma once

#include <SFML/Graphics.hpp>
#include "universe.hpp"
#include "QuadTree.hpp"

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

                sf::CircleShape starShape(universe.getStars()[i].getMass() * 0.1f);
                starShape.setPosition(universe.getStars()[i].getPosition());
                if(universe.getStars()[i].getMass() < 5.0f)
                {
                    starShape.setFillColor(sf::Color(255,243,59));
                    window.draw(starShape);
                }

                else if(universe.getStars()[i].getMass() < 10.0f)
                {
                    starShape.setFillColor(sf::Color(243,144,63));
                    window.draw(starShape);
                }
                else if(universe.getStars()[i].getMass() < 15.0f)
                {
                    starShape.setFillColor(sf::Color(237,104,60));
                    window.draw(starShape);
                }
                else
                {
                    starShape.setFillColor(sf::Color(233,62,58));
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
