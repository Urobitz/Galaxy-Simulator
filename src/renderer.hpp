#pragma once

#include <SFML/Graphics.hpp>
#include "universe.hpp"
#include "QuadTree.hpp"

class Renderer
{
    private:
        sf::RenderWindow window;

    public:
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

        void drawQuadTree(const QuadTree& qt)
        {
            drawNode(qt, 0);
        }

        void clearWindow()
        {
            window.clear(sf::Color(0X0B213C));
        }

        void displayWindow()
        {
            window.display();
        }

        sf::RenderWindow& getWindow()
        {
            return window;
        }

    private:
        void drawNode(const QuadTree& qt, int nodeIndex)
        {
            const QuadNode& node = qt.nodes[nodeIndex];

            // draw this node's boundary as a rectangle outline
            float size = node.nodeBoundary.halfSize * 2.f;
            sf::RectangleShape rect(sf::Vector2f(size, size));
            rect.setPosition(sf::Vector2f(
                node.nodeBoundary.center.x - node.nodeBoundary.halfSize,
                node.nodeBoundary.center.y - node.nodeBoundary.halfSize
            ));
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color(255, 255, 255, 30)); // white, mostly transparent
            rect.setOutlineThickness(1.f);
            window.draw(rect);

            // recurse into children
            if(!node.isLeaf())
            {
                for(int i = 0; i < 4; i++)
                    if(node.children[i] != -1)
                        drawNode(qt, node.children[i]);
            }
        }
};