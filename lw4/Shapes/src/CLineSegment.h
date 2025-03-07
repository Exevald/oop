#pragma once

#include "CPoint.h"
#include "CShape.h"
#include "IShape.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t lineColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) override;

private:
	[[nodiscard]] std::string GetShapeInfo() const override;

	CPoint m_startPoint, m_endPoint;
};
