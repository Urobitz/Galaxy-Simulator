#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Universe;

class Renderer
{
    private:
        sf::RenderWindow window;

    public:
        Renderer(unsigned int width, unsigned int height, const std::string& title);

        void drawUniverse(const Universe& universe);

        void clearWindow();

        void displayWindow();

        //Getters
        sf::RenderWindow& getWindow();
};
