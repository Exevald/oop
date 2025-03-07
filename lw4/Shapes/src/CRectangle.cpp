#include "CRectangle.h"
#include <iostream>

CRectangle::CRectangle(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor)
	: CSolidShape(fillColor, outlineColor)
	, m_coordinates(coordinates)
{
	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("invalid rectangle size");
	}

	m_width = width;
	m_height = height;
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_coordinates;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_coordinates.x + m_width, m_coordinates.y + m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::Draw(ICanvas& canvas)
{
	canvas.FillRect(m_coordinates, m_width, m_height, CSolidShape::GetFillColor(), CSolidShape::GetOutlineColor());
}

std::string CRectangle::GetShapeInfo() const
{
	return "LeftTop point: (" + std::to_string(CRectangle::GetLeftTop().x) + ", " + std::to_string(CRectangle::GetLeftTop().y) + ")\n"
		+ "RightBottom point: (" + std::to_string(CRectangle::GetRightBottom().x) + ", " + std::to_string(CRectangle::GetRightBottom().y) + ")\n"
		+ "Width: " + std::to_string(CRectangle::GetWidth()) + "\n"
		+ "Height: " + std::to_string(CRectangle::GetHeight()) + "\n";
}
