#include "CCircle.h"
#include "CMockCanvas.h"
#include <gtest/gtest.h>

namespace
{
constexpr CPoint center = { 50, 50 };
constexpr double radius = 30;
constexpr double circlePerimeter = 188.496;
constexpr double circleArea = 2827.43;
constexpr uint32_t circleFillColor = 0x00000;
constexpr uint32_t circleOutlineColor = 0xFFFFF;

} // namespace

struct MockCanvasDependencies
{
	std::stringstream output;
};

struct CircleTestMiddleware : MockCanvasDependencies
{
	CMockCanvas mockCanvas;
	CircleTestMiddleware()
		: mockCanvas(output)
	{
	}
};

TEST(Circle, TestDefaultCircleCreation)
{
	CircleTestMiddleware testMiddleware;
	auto circle = CCircle(center, radius, circleFillColor, circleOutlineColor);

	ASSERT_EQ(circle.GetCenter().x, center.x);
	ASSERT_EQ(circle.GetCenter().y, center.y);

	ASSERT_EQ(circle.GetRadius(), radius);

	ASSERT_EQ(circle.GetFillColor(), circleFillColor);
	ASSERT_EQ(circle.GetOutlineColor(), circleOutlineColor);

	circle.Draw(testMiddleware.mockCanvas);
	auto expectedOutput = "Drawing circle with fill color 0 and outline color 1048575 in (50, 50) with radius 30\n";
	ASSERT_EQ(testMiddleware.output.str(), expectedOutput);
}