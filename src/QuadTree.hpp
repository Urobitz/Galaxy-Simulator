#pragma once
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

// NOTE: Comments in this file were generated with AI and are intended as temporary guidance.
//       Review and update them as needed for your final implementation.

/*
QUADTREE 

Root contains entire space, each node contains 4 quadrants.
If a quadrant has more bodies than a certain constant, it
subdivides into 4 children.

RULES:

If a point is added to a leaf that is already at maximum capacity
that node is split into 4 children.

The existing points and the new point are then distributed among the children.

A maximum depth constant can be set.
*/

struct boundary
{
    sf::Vector2f center;
    float halfSize;

    bool containsStar(Star* star) const
    {
        sf::Vector2f pos = star->getPosition();
        // Return true when the star is within this node's square boundary.
        return (pos.x >= center.x - halfSize && pos.x <= center.x + halfSize &&
                pos.y >= center.y - halfSize && pos.y <= center.y + halfSize);
    }
};

struct QuadNode
{
    //General node data
    boundary nodeBoundary;
    int maxCapacity = 1;
    int children[4] = {-1, -1, -1, -1}; // NW, NE, SW, SE child node indices
    std::vector<Star*> nodeStars;

    //Barnes-Hut Data
    float totalMass = 0.0f;
    sf::Vector2f centerOfMass = sf::Vector2f(0.f, 0.f);

    bool isLeaf() const {
        return children[0] == -1;
    }

    bool isDivided() const {
        return !isLeaf();
    }

    boundary calculateBoundary(int quadrant)
    {
        boundary childrenBoundary;
        float offset = nodeBoundary.halfSize / 2.0f;
        switch (quadrant)
        {
            case 0: // NW
                childrenBoundary.center = sf::Vector2f(nodeBoundary.center.x - offset, nodeBoundary.center.y - offset);
                break;
            case 1: // NE
                childrenBoundary.center = sf::Vector2f(nodeBoundary.center.x + offset, nodeBoundary.center.y - offset);
                break;
            case 2: // SW
                childrenBoundary.center = sf::Vector2f(nodeBoundary.center.x - offset, nodeBoundary.center.y + offset);
                break;
            case 3: // SE
                childrenBoundary.center = sf::Vector2f(nodeBoundary.center.x + offset, nodeBoundary.center.y + offset);
                break;
        }
        childrenBoundary.halfSize = nodeBoundary.halfSize / 2.0f;
        return childrenBoundary;
    }

    int getQuadrant(Star* star) const
    {
        sf::Vector2f pos = star->getPosition();
        // Determine which quadrant the star belongs to based on the node center.
        if (pos.x < nodeBoundary.center.x && pos.y < nodeBoundary.center.y)
        {
            return 0; // NW
        }
        else if (pos.x >= nodeBoundary.center.x && pos.y < nodeBoundary.center.y)
        {
            return 1; // NE
        }
        else if (pos.x < nodeBoundary.center.x && pos.y >= nodeBoundary.center.y)
        {
            return 2; // SW
        }
        else
        {
            return 3; // SE
        }
    }

    
};

struct QuadTree
{
    int freeNodeIndex = 0;
    std::vector<QuadNode> nodes;

    QuadTree()
    {
        nodes.reserve(5000); // Reserve space to avoid frequent reallocations.
        nodes.emplace_back();
        nodes[0].nodeBoundary.center = sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
        freeNodeIndex++;
    }

    void insert(Star* star)
    {
        insert(0, star);
    }

    void calculateCenterOfMass()
    {
        calculateCenterOfMass(0);
    }

    void clearTree()
    {
        // Reset root node to initial empty state.
        freeNodeIndex = 1;
        nodes[0].children[0] = nodes[0].children[1] = nodes[0].children[2] = nodes[0].children[3] = -1;
        nodes[0].nodeStars.clear();
        nodes[0].totalMass = 0.0f;
        nodes[0].centerOfMass = sf::Vector2f(0.f, 0.f);
    }




private:

    void insert(int nodeIndex, Star* star, int depth = 0)
{
    if (depth > 20) return; // evitar recursión infinita

    QuadNode& node = nodes[nodeIndex];

    if (node.isLeaf() && node.nodeStars.size() < node.maxCapacity)
    {
        node.nodeStars.push_back(star);
    }
    else
    {
        if (node.isLeaf())
        {
            subdivide(nodeIndex);

            for (Star* currentStar : node.nodeStars)
            {
                int quadrant = node.getQuadrant(currentStar);
                insert(node.children[quadrant], currentStar, depth + 1);
            }
            node.nodeStars.clear();
        }

        int quadrant = node.getQuadrant(star);
        insert(node.children[quadrant], star, depth + 1);
    }
}

    void subdivide(int parentIndex)
{
    boundary parentBoundary = nodes[parentIndex].nodeBoundary; // guardar ANTES del loop

    for (int i = 0; i < 4; i++)
    {
        if (freeNodeIndex >= (int)nodes.size())
            nodes.emplace_back();

        nodes[parentIndex].children[i] = freeNodeIndex;
        QuadNode& child = nodes[freeNodeIndex];
        child.nodeBoundary = nodes[parentIndex].calculateBoundary(i); // usar copia local
        child.children[0] = child.children[1] = child.children[2] = child.children[3] = -1;
        child.nodeStars.clear();
        child.totalMass = 0.0f;
        child.centerOfMass = {0.0f, 0.0f};
        freeNodeIndex++;
    }
}
    void calculateCenterOfMass(int nodeIndex)
    {
        QuadNode& node = nodes[nodeIndex];

        if (node.isLeaf())
        {
            if (node.nodeStars.empty())
            {
                node.totalMass = 0.0f;
                node.centerOfMass = sf::Vector2f(0.f, 0.f);
            }
            else
            {
                for (Star* star : node.nodeStars)
                {
                    node.totalMass += star->getMass();
                    node.centerOfMass += star->getPosition() * star->getMass();
                }
                if(node.totalMass > 0.f)
                {
                    node.centerOfMass /= node.totalMass;
                }
                
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                if (node.children[i] != -1)
                {
                    calculateCenterOfMass(node.children[i]);
                    node.totalMass += nodes[node.children[i]].totalMass;
                    node.centerOfMass += nodes[node.children[i]].centerOfMass * nodes[node.children[i]].totalMass;
                }
            }
            if(node.totalMass > 0.f)
            {
                node.centerOfMass /= node.totalMass;
            }
        }
    }
};

    