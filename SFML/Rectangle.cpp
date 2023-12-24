#include "Rectangle.h"

namespace myShapes
{
    Rectangle::Rectangle(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b, float w, float h)
        : Shape(n, x, y, sX, sY, r, g, b), width{ w }, height{ h }
    {
        shape = std::make_shared <sf::RectangleShape>(sf::Vector2f(getWidth(), getHeight()));
        shape->setFillColor(sf::Color(
            (int)shapeColor[0] * 255,
            (int)shapeColor[1] * 255,
            (int)shapeColor[2] * 255
        ));
        shape->setOrigin(width / 2, height / 2);
        shape->setPosition(x, y);
    }

    void Rectangle::move()
    {
        // Check X bounds
        if (getPosX() + getSpeedX() + ((getWidth() * shape->getScale().x) / 2.0f) > 1280 || getPosX() + getSpeedX() - ((getWidth() * shape->getScale().x) / 2.0f) < 0)     // Ball hit right wall
        {
            setSpeedX(getSpeedX() * (-1.0f));
        }
        // Checks Y bounds
        if (getPosY() + getSpeedY() + ((getHeight() * shape->getScale().y) / 2.0f) > 720 || getPosY() + getSpeedY() - ((getHeight() * shape->getScale().y) / 2.0f) < 0)     // Ball hit right wall
        {
            setSpeedY(getSpeedY() * (-1.0f));
        }
        posX += getSpeedX();
        posY += getSpeedY();
    }

    void Rectangle::draw(sf::RenderWindow& window)
    {
        move();
        shape->setFillColor(sf::Color(
            static_cast<sf::Uint8>(shapeColor[0] * 255),        // Cast to ensure colours remain in range 0-255
            static_cast<sf::Uint8>(shapeColor[1] * 255),
            static_cast<sf::Uint8>(shapeColor[2] * 255)
        ));
        shape->setScale(*getScale(), *getScale());
        shape->setOrigin(getWidth() / 2.0f, getHeight() / 2.0f);
        shape->setPosition(getPosX(), getPosY());
        window.draw(getShape());
        // Text inside shape goes here
        text = sf::Text(name, myFont, 18);
        text.setOrigin(getWidth() / 2.0f, getHeight() / 2.0f);
        text.setPosition(getPosX(), getPosY());
        window.draw(text);
    }
}
