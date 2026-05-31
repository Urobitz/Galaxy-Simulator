#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

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
    Universe universe(1000);

    //Initialize the main window

    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, "Universe Generator");

    //Create clock for deltatime
    sf::Clock clock;

    QuadTree tree;

    tree.insert(0, {100,200});
    tree.insert(0, {110,210});

    /*while(renderer.getWindow().isOpen())
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

    }*/


}