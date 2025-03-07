#pragma once

#include "ICanvas.h"
#include <iostream>
#include <sstream>
#include <vector>

class CMockCanvas : public ICanvas
{
public:
	explicit CMockCanvas(std::ostream& output)
		: m_output(output)
	{
	}

	void DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) const override
	{
		m_output << "Drawing line with color " << lineColor
				 << " from (" << startPoint.x << ", " << startPoint.y << ")"
				 << " to (" << endPoint.x << ", " << endPoint.y << ")" << std::endl;
	}

	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t outlineColor) const override
	{
		m_output << "Drawing polygon with fill color " << fillColor
				 << " and outline color " << outlineColor << " in vertexes:";
		for (const auto& point : points)
		{
			m_output << " (" << point.x << ", " << point.y << ")";
		}
		m_output << std::endl;
	}

	void FillRect(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor) const override
	{
		m_output << "Drawing rectangle " << width << "*" << height
				 << " from (" << coordinates.x << ", " << coordinates.y << ")"
				 << " with fill color " << fillColor
				 << " and outline color " << outlineColor << std::endl;
	}

	void FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) const override
	{
		m_output << "Drawing circle with fill color " << fillColor
				 << " and outline color " << outlineColor
				 << " in (" << center.x << ", " << center.y << ")"
				 << " with radius " << radius << std::endl;
	}

private:
	std::ostream& m_output;
};