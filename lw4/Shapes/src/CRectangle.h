#pragma once

#include "CPoint.h"
#include "CSolidShape.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const final;
	[[nodiscard]] double GetPerimeter() const final;
	[[nodiscard]] CPoint GetLeftTop() const;
	[[nodiscard]] CPoint GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;
	void Draw(ICanvas& canvas) override;

private:
	[[nodiscard]] std::string GetShapeInfo() const final;

	CPoint m_coordinates;
	double m_width, m_height;
};
