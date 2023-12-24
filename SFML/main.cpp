#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Shape.h"          // Custom Shape class
#include "ShapeLoader.h"    // Custom Utils Class to load shapes

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

/*
*  A Demo Program created to learn and showcase SFML and ImGui functionality.
*  The shape objects are loaded in based on the "config.txt" file
*/

int main()
{
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 720;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Window Title");                    // Create a window with specified size.
    window.setFramerateLimit(60);                                                                           // Limit the framerate to be below 60, no guarantee it will be 60

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;
    
    std::vector<std::shared_ptr<myShapes::Shape>> myShapes;
    myShapes::ShapeLoader::loadShapes("config.txt", myShapes);

    // Load the names of each shape object into a vector to be used in ImGui Combo drop down list.
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

        // -- Rendering -- // 
        window.clear(sf::Color(18, 33, 43)); 
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