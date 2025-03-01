#include "CLineSegment.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t lineColor)
	: CShape(lineColor)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return GetLineLength(m_startPoint, m_endPoint);
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(CLineSegment::GetStartPoint(), CLineSegment::GetEndPoint(), CShape::GetOutlineColor());
}

std::string CLineSegment::GetShapeInfo() const
{
	return "Start point: (" + std::to_string(CLineSegment::GetStartPoint().x) + ", " + std::to_string(CLineSegment::GetStartPoint().y) + ")\n"
		+ "End point: (" + std::to_string(CLineSegment::GetEndPoint().x) + ", " + std::to_string(CLineSegment::GetEndPoint().y) + ")\n";
}