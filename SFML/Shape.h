#pragma once
#include <iostream>
#include <string>
#include <sfml/Graphics.hpp>

namespace myShapes
{
    class Shape
    {
    protected:
        std::string name;
        float posX;
        float posY;
        float speedX;
        float speedY;
        float R;
        float G;
        float B;
        float shapeColor[3];
        bool shapeExists{ true };
        float scale{ 1.0f };
        sf::Font myFont;
        sf::Text text;
    public:
        Shape(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b);

        std::string* getName() { return &name; }
        float getPosX() const { return posX; }
        float getPosY() const { return posY; }
        float getSpeedX() const { return speedX; }
        float getSpeedY() const { return speedY; }
        float getR() const { return R; }
        float getG() const { return G; }
        float getB() const { return B; }

        float* getScale() { return &scale; }

        void setSpeedX(float x) { speedX = x; }
        void setSpeedY(float y) { speedY = y; }

        void show() { shapeExists = true; }
        void hide() { shapeExists = false; }
        bool exists() const { return shapeExists; }
        bool* getExists() { return &shapeExists; }

        float* getSpeedXRef() { return &speedX; }
        float* getSpeedYRef() { return &speedY; }
        float* getColor() { return shapeColor; }
        void setText(std::string newText) { text.setString(newText); }

        virtual void draw(sf::RenderWindow& window) = 0;
    };
}


