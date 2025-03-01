#include "CTriangle.h"
#include <iostream>

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor)
	: CSolidShape(fillColor, outlineColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

double CTriangle::GetArea() const
{
	auto matrixDeterminant = (m_vertex1.x - m_vertex3.x) * (m_vertex2.y - m_vertex3.y)
		- (m_vertex2.x - m_vertex3.x) * (m_vertex1.y - m_vertex3.y);
	if (matrixDeterminant == 0)
	{
		throw std::invalid_argument("Invalid triangle coordinates");
	}

	return matrixDeterminant > 0 ? 0.5 * matrixDeterminant : -0.5 * matrixDeterminant;
}

double CTriangle::GetPerimeter() const
{
	const auto line1Length = GetLineLength(m_vertex1, m_vertex2);
	const auto line2Length = GetLineLength(m_vertex2, m_vertex3);
	const auto line3Length = GetLineLength(m_vertex1, m_vertex1);

	return line1Length + line2Length + line3Length;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

std::string CTriangle::GetShapeInfo() const
{
	return "Vertex 1: (" + std::to_string(CTriangle::GetVertex1().x) + ", " + std::to_string(CTriangle::GetVertex1().y) + ")\n"
		+ "Vertex 2: (" + std::to_string(CTriangle::GetVertex2().x) + ", " + std::to_string(CTriangle::GetVertex2().y) + ")\n"
		+ "Vertex 3: (" + std::to_string(CTriangle::GetVertex3().x) + ", " + std::to_string(CTriangle::GetVertex3().y) + ")\n";
}

void CTriangle::Draw(ICanvas& canvas)
{
	canvas.FillPolygon({ CTriangle::GetVertex1(), CTriangle::GetVertex2(), CTriangle::GetVertex3() },
		CSolidShape::GetFillColor(), CSolidShape::GetOutlineColor());
}
