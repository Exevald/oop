#pragma once

#include "IShape.h"

class CShape : public virtual IShape
{
public:
	explicit CShape(uint32_t color);

	[[nodiscard]] std::string ToString() const final
	{
		return "Area: " + std::to_string(GetArea()) + "\n"
			+ "Perimeter: " + std::to_string(GetPerimeter()) + "\n"
			+ GetShapeInfo();
	}

	[[nodiscard]] uint32_t GetOutlineColor() const override;

protected:
	[[nodiscard]] virtual std::string GetShapeInfo() const = 0;

	uint32_t m_outlineColor;
};