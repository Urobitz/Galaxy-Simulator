#pragma once
#include <sfml/Graphics.hpp>
#include "Star.hpp"

class Star;

struct Boundary
{
    sf::Vector2f center;
    float halfWidth;

    Boundary(const sf::Vector2f& center, float halfWidth) : center(center), halfWidth(halfWidth){}

    bool contains(const sf::Vector2f& point) const
    {
        return (point.x >= center.x - halfWidth && point.x <= center.x + halfWidth &&
                point.y >= center.y - halfWidth && point.y <= center.y + halfWidth);
    }
};

struct QuadNode
{
    Boundary boundary;
    int children[4] = {-1, -1, -1, -1}; // NW, NE, SW, SE
    std::vector<Star*> stars;

    QuadNode(const Boundary& boundary) : boundary(boundary) {}

    bool isLeaf() const
    {
        return children[0] == -1;
    }

    //Calculate in which quadrant the star will end
    int calculateQuadrant(sf::Vector2f starPos)
    {
        bool isEast = starPos.x > boundary.center.x;
        bool isSouth = starPos.y > boundary.center.y;

        if (!isEast && !isSouth) return 0; // NW
        if ( isEast && !isSouth) return 1; // NE
        if (!isEast &&  isSouth) return 2; // SW
        if ( isEast &&  isSouth) return 3; // SE
    } 

    //function to calculate a new boundary for the children based on the parent
    Boundary calculateBoundary(int quadrantDirection) 
    {
        Boundary newBoundary({0,0},0);
        sf::Vector2f parentCenter = boundary.center;
        float parentWidth = boundary.halfWidth;
        sf::Vector2f newCenter;

        switch(quadrantDirection)
        {
            case 0:
                newCenter.x = parentCenter.x - parentWidth/2;
                newCenter.y = parentCenter.y - parentWidth/2;
                break;
            case 1:
                newCenter.x = parentCenter.x + parentWidth/2;
                newCenter.y = parentCenter.y - parentWidth/2;
                break;
            case 2:
                newCenter.x = parentCenter.x - parentWidth/2;
                newCenter.y = parentCenter.y + parentWidth/2;
                break;
            case 3: 
                newCenter.x = parentCenter.x + parentWidth/2;
                newCenter.y = parentCenter.y + parentWidth/2;
                break;
        }

        newBoundary.center = newCenter;
        newBoundary.halfWidth = parentWidth / 2;

        return newBoundary;
    }
};

class QuadTree
{
    private:
    
    std::vector<QuadNode> nodes;
    int availableSpaceIndex = 0;
    int nodeMaxCapacity = 1;

    QuadTree()
    {   
        Boundary initialBoundary({SCREEN_WIDTH/2,SCREEN_HEIGHT/2}, std::max(SCREEN_WIDTH, SCREEN_HEIGHT)/2);
        nodes.reserve(1000);
        nodes.emplace_back(initialBoundary);
        availableSpaceIndex++;
    }

      //subdivide parentNode
    void subdivide(int parentIndex)
    {
        nodes.reserve(nodes.size() + 4);
        for(int i = 0; i < 4; i++)
        {
            Boundary childBoundary = nodes[parentIndex].calculateBoundary(i);
            nodes.emplace_back(childBoundary);
            nodes[parentIndex].children[i] = availableSpaceIndex;
            availableSpaceIndex++;
        }
    }
    
    void insert(Star * star, int nodeIndex)
    {
        // if the star is not in the quadrant simply reject
        if(!nodes[nodeIndex].boundary.contains(star->getPosition()))
            return;

        // If the node is a leaf and has capacity, insert there
        if(nodes[nodeIndex].isLeaf() && nodes[nodeIndex].stars.size() < nodeMaxCapacity)
        {
            nodes[nodeIndex].stars.push_back(star);
            return; // <-- faltaba esto
        }

        // If leaf and full, subdivide
        if(nodes[nodeIndex].isLeaf())
        {
            subdivide(nodeIndex);
        }

        // Go down to the correct child
        int starQuadrant = nodes[nodeIndex].calculateQuadrant(star->getPosition());
        int childIndex = nodes[nodeIndex].children[starQuadrant];
        insert(star, childIndex);
    }

    void clear()
    {

        QuadNode root = nodes[0];
        root.stars.clear();
        root.children[0] = -1;         
        root.children[1] = -1;
        root.children[2] = -1;
        root.children[3] = -1;

        nodes.clear();
        nodes.push_back(root);
        availableSpaceIndex = 1;

    }

    public:

    void insert(Star* star)
    {
        insert(star,0);
    }

};