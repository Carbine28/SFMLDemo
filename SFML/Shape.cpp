#include "Shape.h"
#include <string>

namespace myShapes
{
    Shape::Shape(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b)
        : name{ n }, posX{ x }, posY{ y }, speedX{ sX }, speedY{ sY }, R{ r }, G{ g }, B{ b }, shapeColor{ R / 255.0f, G / 255.0f, B / 255.0f }
    {
        if (!myFont.loadFromFile("fonts/Roboto-Regular.ttf"))
        {
            std::cerr << "Could not load file";
            exit(-1);
        }
        text = sf::Text(name, myFont, 16);
    }
}


