#pragma once
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

const int NODE_CAPACITY = 1;

struct quadrant
{    
    sf::Vector2f center;
    float size;
};

struct Node 
{
    int firstChild = -1;
    std::size_t firstBody = -1;
    std::size_t bodyCount = 0;
    quadrant bounds;
    sf::Vector2f centerOfMass;
    float totalMass = 0.0f;
};

struct QuadTree
{

std::vector<Node> nodes;
std::size_t root = 0;


    QuadTree()
    {
        Node rootNode;
        rootNode.bounds.center = sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
        rootNode.bounds.size = std::max(SCREEN_WIDTH, SCREEN_HEIGHT);
        rootNode.firstChild = -1;

        nodes.reserve(50000);
        nodes.push_back(rootNode);
        root = 0;
    }

    //Subdivide the node at the given index into four child nodes
    void subdivide(std::size_t nodeIndex)
    {
        Node& parentNode = nodes[nodeIndex];
        parentNode.firstChild = nodes.size();

        for(int i = 0; i < 4; i++)
        {
            Node childNode;
            childNode.firstChild = -1;
            childNode.bounds.size = parentNode.bounds.size/ 2.f;
            float center_offset = childNode.bounds.size / 2.f;

            switch(i)
            {
                case 0: // Top-left
                    childNode.bounds.center = sf::Vector2f(parentNode.bounds.center.x - center_offset, parentNode.bounds.center.y - center_offset);
                    break;
                case 1: // Top-right
                    childNode.bounds.center = sf::Vector2f(parentNode.bounds.center.x + center_offset, parentNode.bounds.center.y - center_offset);
                    break;
                case 2: // Bottom-left
                    childNode.bounds.center = sf::Vector2f(parentNode.bounds.center.x - center_offset, parentNode.bounds.center.y + center_offset);
                    break;
                case 3: // Bottom-right
                    childNode.bounds.center = sf::Vector2f(parentNode.bounds.center.x + center_offset, parentNode.bounds.center.y + center_offset);
                    break;
            }

            nodes.emplace_back(childNode);

        }
        
    }

    void insert(std::size_t nodeIndex, sf::Vector2f bodyPosition)
    {
        if(nodes[nodeIndex].firstChild == -1 && nodes[nodeIndex].bodyCount < NODE_CAPACITY)
        {
            nodes[nodeIndex].bodyCount++;
            std::cout << "\nadded sucesfully a body to the node " << nodeIndex << " their body count is now: " << nodes[nodeIndex].bodyCount;
        }
        else
        {
            sf::Vector2 center = nodes[nodeIndex].bounds.center;
            subdivide(nodeIndex);
            int target = nodes[nodeIndex].firstChild;

            if(bodyPosition.x >= center.x && bodyPosition.y < center.y)
            {
                target += 1;
            }
            else if(bodyPosition.x < center.x && bodyPosition.y >= center.y)
            {
                target += 2;
            }
            else if(bodyPosition.x >= center.x && bodyPosition.y >= center.y)
            {
                target += 3;
            }

            insert(target, bodyPosition);

            std::cout << "\nadded object to " << target << " which is " << nodeIndex << " son";
            std::cout << "\ntheir body count is now: " << nodes[target].bodyCount;
            
        }
    }
};