#pragma once

#include "IShape.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <istream>
#include <memory>
#include <unordered_map>

using ActionMap = std::unordered_map<std::string, std::function<void()>>;

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	void HandleCommand();
	void PrintResult();
	void DrawShapes(sf::RenderWindow& window);

private:
	void PrintShape(const IShape* shape);
	void AddRectangle();
	void AddLine();
	void AddCircle();
	void AddTriangle();
	IShape* GetMaxAreaShape() const;
	IShape* GetMinPerimeterShape() const;
	static uint32_t StringToUint32(const std::string& value);


	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_actionMap;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
