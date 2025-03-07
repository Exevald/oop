#pragma once

#include "CPoint.h"
#include "CSolidShape.h"

class CCircle final : public CSolidShape
{
public:
	CCircle(CPoint centerCoordinates, double radius, uint32_t fillColor, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const final;
	[[nodiscard]] double GetPerimeter() const final;
	[[nodiscard]] CPoint GetCenter() const;
	[[nodiscard]] double GetRadius() const;
	void Draw(ICanvas& canvas) override;

private:
	[[nodiscard]] std::string GetShapeInfo() const final;

	CPoint m_centerCoordinates;
	double m_radius;
};
