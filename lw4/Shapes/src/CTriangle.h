#pragma once

#include "CPoint.h"
#include "CSolidShape.h"
#include "ISolidShape.h"

class CTriangle final : public CSolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const final;
	[[nodiscard]] double GetPerimeter() const final;
	[[nodiscard]] CPoint GetVertex1() const;
	[[nodiscard]] CPoint GetVertex2() const;
	[[nodiscard]] CPoint GetVertex3() const;
	void Draw(ICanvas& canvas) override;

private:
	[[nodiscard]] std::string GetShapeInfo() const final;
	CPoint m_vertex1, m_vertex2, m_vertex3;
};
