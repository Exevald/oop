#pragma once

#include "CPoint.h"
#include "CSolidShape.h"

class CCircle final : public CSolidShape
{
public:
	CCircle(CPoint centerCoordinates, double radius, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const final;
	double GetPerimeter() const final;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) override;

private:
	std::string GetShapeInfo() const final;

	CPoint m_centerCoordinates;
	double m_radius;
};
