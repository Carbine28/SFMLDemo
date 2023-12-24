#include "Circle.h"

namespace myShapes {
    Circle::Circle(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b, float radius)
        : Shape(n, x, y, sX, sY, r, g, b), circleRadius{ radius }
    {
        shape = std::make_shared<sf::CircleShape>(circleRadius, circleSegments);
        shape->setOrigin(circleRadius, circleRadius);
        shape->setPosition(x, y);
        shape->setPointCount(circleSegments);
        shape->setFillColor(sf::Color(
            (int)shapeColor[0] * 255,
            (int)shapeColor[1] * 255,
            (int)shapeColor[2] * 255
        ));
    }

    void Circle::move()
    {
        if (getPosX() + getSpeedX() + (circleRadius * shape->getScale().x) > 1280 || getPosX() + getSpeedX() - (circleRadius * shape->getScale().x) < 0)     // Ball hit right wall
        {
            setSpeedX(getSpeedX() * (-1.0f));
        }

        if (getPosY() + getSpeedY() + (circleRadius * shape->getScale().x) > 720 || getPosY() + getSpeedY() - (circleRadius * shape->getScale().x) < 0)     // Ball hit right wall
        {
            setSpeedY(getSpeedY() * (-1.0f));
        }
        posX += getSpeedX();
        posY += getSpeedY();
    }

    void Circle::draw(sf::RenderWindow& window)
    {
        move();
        shape->setScale(*(getScale()), *(getScale()));
        shape->setOrigin(circleRadius, circleRadius);
        shape->setPosition(getPosX(), getPosY());
        shape->setPointCount(circleSegments);
        shape->setFillColor(sf::Color(
            static_cast<sf::Uint8>(shapeColor[0] * 255),
            static_cast<sf::Uint8>(shapeColor[1] * 255),
            static_cast<sf::Uint8>(shapeColor[2] * 255)
        ));
        window.draw(getShape());
        text = sf::Text(name, myFont, 20);
        text.setOrigin(circleRadius / 1.8f, circleRadius / 1.8f);
        text.setPosition(getPosX(), getPosY());
        window.draw(text);
    }

}
