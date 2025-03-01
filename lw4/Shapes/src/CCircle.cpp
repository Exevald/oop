#include "CCircle.h"
#include <cmath>

CCircle::CCircle(CPoint centerCoordinates, double radius, uint32_t fillColor, uint32_t outlineColor)
	: CSolidShape(fillColor, outlineColor)
	, m_centerCoordinates(centerCoordinates)
	, m_radius(radius)
{
}

double CCircle::GetArea() const
{
	return M_PI * std::pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_centerCoordinates;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.FillCircle(CCircle::GetCenter(), CCircle::GetRadius(), CSolidShape::GetFillColor(), CSolidShape::GetOutlineColor());
}

std::string CCircle::GetShapeInfo() const
{
	return "Center point: (" + std::to_string(CCircle::GetCenter().x) + ", " + std::to_string(CCircle::GetCenter().y) + ")\n"
		+ "Radius: " + std::to_string(CCircle::GetRadius()) + ")\n";
}