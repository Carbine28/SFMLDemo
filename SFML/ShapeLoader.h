#pragma once
#include "Shape.h"
#include <vector>
#include <memory>

namespace myShapes
{
	class ShapeLoader {
	public:
		static void loadShapes(const std::string& fileName, std::vector<std::shared_ptr<Shape>>& shapes);
	};
}
