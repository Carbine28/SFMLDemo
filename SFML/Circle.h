#pragma once
#include "Shape.h"
#include "SFML/Graphics.hpp"
#include <memory>

#include <string>
namespace myShapes
{
	class Circle : public Shape
	{
		float circleRadius;
		size_t circleSegments{ 100 };
		std::shared_ptr<sf::CircleShape> shape;
	public:
		Circle(const std::string& n, float x, float y, float sX, float sY, float r, float g, float b, float radius);

		const float getRadius() const { return circleRadius; }
		const size_t getSegments() const { return circleSegments; }
		const sf::CircleShape getShape() const { return *shape; }

		void move();
		void draw(sf::RenderWindow& window) override;
	};
}
