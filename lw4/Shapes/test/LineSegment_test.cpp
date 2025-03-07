#include "CLineSegment.h"
#include "CMockCanvas.h"
#include <gtest/gtest.h>

namespace
{
constexpr CPoint startPoint = { 0, 0 };
constexpr CPoint endPoint = { 50, 0 };
constexpr double lineWidth = 50;
constexpr uint32_t lineColor = 0xFFFFF;

} // namespace

struct MockCanvasDependencies
{
	std::stringstream output;
};

struct LineSegmentTestMiddleware : MockCanvasDependencies
{
	CMockCanvas mockCanvas;
	LineSegmentTestMiddleware()
		: mockCanvas(output)
	{
	}
};

TEST(LineSegment, TestDefaultLineSegmentCreation)
{
	LineSegmentTestMiddleware testMiddleware;
	auto line = CLineSegment(startPoint, endPoint, lineColor);

	ASSERT_EQ(line.GetStartPoint().x, startPoint.x);
	ASSERT_EQ(line.GetStartPoint().y, startPoint.y);
	ASSERT_EQ(line.GetEndPoint().x, endPoint.x);
	ASSERT_EQ(line.GetEndPoint().y, endPoint.y);

	ASSERT_EQ(line.GetPerimeter(), lineWidth);
	ASSERT_EQ(line.GetArea(), 0);
}