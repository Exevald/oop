#pragma once

#include "CPoint.h"
#include "CSolidShape.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const final;
	double GetPerimeter() const final;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) override;

private:
	std::string GetShapeInfo() const final;

	CPoint m_coordinates;
	double m_width, m_height;
};
