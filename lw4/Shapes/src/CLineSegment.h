#pragma once

#include "CPoint.h"
#include "CShape.h"
#include "IShape.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t lineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) override;

private:
	std::string GetShapeInfo() const override;

	CPoint m_startPoint, m_endPoint;
};
