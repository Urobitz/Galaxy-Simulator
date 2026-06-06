#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <algorithm>

//Project header
#include "star.hpp"
#include "universe.hpp"
#include "random.hpp"
#include "renderer.hpp"
#include "QuadTree.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main()
{

    //Initialize universe
    Universe universe(5000);
    //Initialize the main window
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, "Universe Generator");
    //Quadtree test
    QuadTree quadTree;
    //Create clock for deltatime
    sf::Clock clock;

    while(renderer.getWindow().isOpen())
    {
        float dt = clock.restart().asSeconds();

        while(const std::optional event = renderer.getWindow().pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                renderer.getWindow().close();
            }
        }
        
        universe.updateStars(dt);
        renderer.clearWindow();
        renderer.drawUniverse(universe);
        renderer.displayWindow();

    }


}