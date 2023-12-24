#pragma once
#include "Shape.h"
#include <memory>
#include <string>
#include "SFML/Graphics.hpp"

namespace myShapes
{
	class Rectangle : public Shape
	{
		float width;
		float height;
		std::shared_ptr<sf::RectangleShape> shape;
	public:
		Rectangle(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b, float w, float h);

		float getWidth() const { return width; }
		float getHeight() const { return height; }
		const sf::RectangleShape getShape() const { return *shape; }
		void move();
		void draw(sf::RenderWindow& window) override;
	};
}
