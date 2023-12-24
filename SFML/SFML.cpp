#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <memory>
#include <vector>

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

/*
* Shape | Name | PosX | Pos Y | SpeedX | SpeedY | R | G | B 
* Rectangle | Text | PosX | PosY | SpeedX | SpeedY | R | G | B | Width | Height
* Circle | Text | PosX | PosY | SpeedX | SpeedY | R | G | B | Radius
*/

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
    float circleColor[3];
    bool shapeExists{true};
    float scale{ 1.0f };
    sf::Font myFont;
    sf::Text text;
public:
    Shape(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b)
        : name{ n }, posX{ x }, posY{ y }, speedX{sX}, speedY{sY}, R{r}, G{g}, B{b} 
    {
        circleColor[0] = R / 255;
        circleColor[1] = G / 255;
        circleColor[2] = B / 255;
        if (!myFont.loadFromFile("fonts/Roboto-Regular.ttf"))
        {
            std::cerr << "Could not load file";
            exit(-1);
        }
        text = sf::Text(name, myFont, 16);
    }

    std::string* getName() { return &name; }
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getSpeedX() const { return speedX; }
    float getSpeedY() const { return speedY; }
    float getR() const { return R; }
    float getG() const { return G; }
    float getB() const { return B; }

    float* getScale() { return &scale; }

    void setSpeedX(float x) { speedX = x;}
    void setSpeedY(float y) { speedY = y; }

    void show() { shapeExists = true; }
    void hide() { shapeExists = false; }
    bool exists() const { return shapeExists; }
    bool* getExists() { return &shapeExists; }

    float* getSpeedXRef() { return &speedX; }
    float* getSpeedYRef() { return &speedY; }
    float* getColor() { return circleColor; }
    void setText(std::string newText) { text.setString(newText); }

    virtual void draw(sf::RenderWindow& window) = 0;
};

class Circle : public Shape
{
    float circleRadius;
    size_t circleSegments{ 100 };
    std::shared_ptr<sf::CircleShape> shape;
public:
    Circle(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b, float radius)
        : Shape(n, x, y, sX, sY, r, g, b), circleRadius{radius} 
    {
        shape = std::make_shared<sf::CircleShape>(circleRadius, circleSegments);
        shape->setOrigin(circleRadius, circleRadius);
        shape->setPosition(x, y);
        shape->setPointCount(circleSegments);
        shape->setFillColor(sf::Color(
            (int)circleColor[0] * 255,
            (int)circleColor[1] * 255,
            (int)circleColor[2] * 255
        ));
    }
    const float getRadius() const { return circleRadius; }
    const size_t getSegments() const { return circleSegments; }
    const sf::CircleShape getShape() const { return *shape; }

    void move()
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

    void draw(sf::RenderWindow& window) override
    {
        move();
        shape->setScale(*(getScale()), *(getScale()));
        shape->setOrigin(circleRadius, circleRadius);
        shape->setPosition(getPosX(), getPosY());
        shape->setPointCount(circleSegments);
        shape->setFillColor(sf::Color(
            static_cast<sf::Uint8>(circleColor[0] * 255),
            static_cast<sf::Uint8>(circleColor[1] * 255),
            static_cast<sf::Uint8>(circleColor[2] * 255)
        ));
        window.draw(getShape());
        text = sf::Text(name, myFont, 20);
        text.setOrigin(circleRadius/1.8f, circleRadius/1.8f);
        text.setPosition(getPosX(), getPosY());
        window.draw(text);
    }
};

class Rectangle : public Shape
{
    float width;
    float height;
    std::shared_ptr<sf::RectangleShape> shape;
public:
    Rectangle(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b, float w, float h)
        : Shape(n, x, y, sX, sY, r, g, b), width{ w }, height{ h } 
    {
        shape = std::make_shared <sf::RectangleShape>(sf::Vector2f(getWidth(), getHeight()));
        shape->setFillColor(sf::Color(
            (int)circleColor[0] * 255,
            (int)circleColor[1] * 255,
            (int)circleColor[2] * 255
        ));
        shape->setOrigin(width / 2, height / 2);
        shape->setPosition(x, y);
    }

    float getWidth() { return width; }
    float getHeight() { return height; }
    const sf::RectangleShape getShape() const { return *shape; }

    void move()
    {
        if (getPosX() + getSpeedX() + ((getWidth() * shape->getScale().x)/2.0f) > 1280 || getPosX() + getSpeedX() - ((getWidth() * shape->getScale().x) / 2.0f) < 0)     // Ball hit right wall
        {
            setSpeedX(getSpeedX() * (-1.0f));
        }

        if (getPosY() + getSpeedY() + ((getHeight() * shape->getScale().y)/2.0f)  > 720 || getPosY() + getSpeedY() - ((getHeight() * shape->getScale().y) / 2.0f) < 0)     // Ball hit right wall
        {
            setSpeedY(getSpeedY() * (-1.0f));
        }
        posX += getSpeedX();
        posY += getSpeedY();
    }

    void draw(sf::RenderWindow& window) override
    {
        move();

        shape->setFillColor(sf::Color(
            static_cast<sf::Uint8>(circleColor[0] * 255),
            static_cast<sf::Uint8>(circleColor[1] * 255),
            static_cast<sf::Uint8>(circleColor[2] * 255)
        ));
        shape->setScale(*getScale(), *getScale());
        shape->setOrigin(getWidth() / 2.0f, getHeight() / 2.0f);
        shape->setPosition(getPosX(), getPosY());
        window.draw(getShape());
        text = sf::Text(name, myFont, 18);
        text.setOrigin(getWidth() / 2.0f, getHeight() / 2.0f);
        text.setPosition(getPosX(), getPosY());
        window.draw(text);
    }
};

static void loadShapes(std::string fileName, std::vector<std::shared_ptr<Shape>>& shapes);

int main()
{
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 720;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Window Title");                    // Create a window with specified size.
    window.setFramerateLimit(60);                                                                           // Limit the framerate to be below 60, no guarantee it will be 60

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    
    std::vector<std::shared_ptr<Shape>> myShapes;
    loadShapes("config.txt", myShapes);

    //// Circle properties
    //bool circleExists{true};
    //float circleRadius = 200.0f;
    //int circleSegments = 100;
    //float circleColor[3] =
    //{
    //    static_cast<float>(204) / 255,
    //    static_cast<float>(77) / 255,
    //    static_cast<float>(5) / 255
    //};
    //sf::CircleShape shape(circleRadius, circleSegments);
    //shape.setFillColor(sf::Color
    //(
    //    static_cast<int>(circleColor[0] * 255),
    //    static_cast<int>(circleColor[1] * 255),
    //    static_cast<int>(circleColor[2] * 255)
    //)); // Color circle
    //shape.setOrigin(circleRadius, circleRadius);
    //shape.setPosition( (static_cast<float>(SCREEN_WIDTH) / 2) , (static_cast<float>(SCREEN_HEIGHT) / 2)); // Center circle

    //sf::Font myFont;
    //if (!myFont.loadFromFile("fonts/Roboto-Regular.ttf"))
    //{
    //    std::cerr << "Could not load file";
    //    exit(-1);
    //}

    //sf::Text text("Sample text", myFont, 24);
    //text.setPosition(0, SCREEN_HEIGHT - (float)text.getCharacterSize());
    //char displayText[255] = "Sample text";

    std::vector<std::string> items;
    for (const auto& s : myShapes)
    {
        items.push_back(*(s->getName()));
    }
    size_t current_item_index{};
    static const char* current_item = items[0].c_str();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Shape Properties");
        if (ImGui::BeginCombo("Selected Shape", current_item))
        {
            for (size_t n = 0; n < items.size(); ++n)
            {
                const bool is_selected = (current_item == items[n]);
                if (ImGui::Selectable(items[n].c_str(), is_selected))
                {
                    current_item = items[n].c_str();
                    current_item_index = n;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();               
            }
            ImGui::EndCombo();

        }

        ImGui::PushItemWidth(100);
        ImGui::Checkbox("Draw Circle", myShapes[current_item_index]->getExists());
        ImGui::SliderFloat("Scale", myShapes[current_item_index]->getScale(), 0.0f, 3.0f);
        //ImGui::SliderFloat("Radius", &circleRadius, 100.0f, 300.0f);
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * .33f);
        ImGui::SliderFloat("##x", myShapes[current_item_index]->getSpeedXRef(), -6.0f, 6.0f);
        ImGui::SameLine();
        ImGui::SliderFloat("Velocity", myShapes[current_item_index]->getSpeedYRef(), -6.0f, 6.0f);
        //ImGui::SliderInt("Segments", &circleSegments, 3, 150);
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * .68f);
        ImGui::ColorEdit3("Color Circle", myShapes[current_item_index]->getColor());
        ImGui::InputText("Name", myShapes[current_item_index]->getName());
        if (ImGui::Button("Set Text"))
        {
            myShapes[current_item_index]->setText(*(myShapes[current_item_index]->getName()));
            items[current_item_index] = *(myShapes[current_item_index]->getName());
        }
        ImGui::End();
        //text.setPosition(0, SCREEN_HEIGHT - (float)text.getCharacterSize());
        // ---------------- Rendering ---------------------------- //
        window.clear(sf::Color(18, 33, 43)); // Color background

        for (const auto& shape : myShapes)
        {
            if (shape->exists())
            {
                shape->draw(window);
            }
        }

        ImGui::SFML::Render(window);                                            // Render UI
        window.display();                                                       // Swaps buffers
    }

    ImGui::SFML::Shutdown();
    return 0;
}



static void loadShapes(std::string fileName, std::vector<std::shared_ptr<Shape>>& shapes)
{
    std::ifstream file{ fileName };
    if (!file.is_open())
    {
        std::cerr << "failed to open" << fileName << "\n";
        exit(-1);
    }

    std::string line{};
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string shape; std::string name;
        float posX{}; float posY{};
        float speedX{}; float speedY{};
        float R{}; float G{}; float B{};

        iss >> shape >> name >> posX >> posY >> speedX >> speedY >> R >> G >> B;
        if (shape == "Circle")
        {
            float radius;
            iss >> radius;
            shapes.push_back(std::make_shared<Circle>(name, posX, posY, speedX, speedY, R, G, B, radius));
        }
        else if (shape == "Rectangle")
        {
            float width; 
            float height;
            iss >> width >> height;
            shapes.push_back(std::make_shared<Rectangle>(name, posX, posY, speedX, speedY, R, G, B, width, height));
        }
        else
        {
            std::cerr << "Error in reading shape: " << shape << "\n";
            exit(-1);
        }
    }
}