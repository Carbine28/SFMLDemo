#include "ShapeLoader.h"
#include <fstream>
#include <sstream>

#include "Rectangle.h"
#include "Circle.h"

namespace myShapes
{
    void myShapes::ShapeLoader::loadShapes(const std::string& fileName, std::vector<std::shared_ptr<Shape>>& shapes)
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
}