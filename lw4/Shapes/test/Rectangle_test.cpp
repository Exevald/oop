#include "CMockCanvas.h"
#include "CRectangle.h"
#include <gtest/gtest.h>

namespace
{
constexpr uint32_t rectangleFillColor = 0x00000;
constexpr uint32_t rectangleOutlineColor = 0xFFFFF;
constexpr double rectWidth = 30;
constexpr double rectHeight = 12.3;
constexpr CPoint leftTopPoint = { 0, 0.5 };
constexpr CPoint rightBottomPoint = { 0 + rectWidth, 0.5 + rectHeight };
constexpr double rectArea = rectWidth * rectHeight;
constexpr double rectPerimeter = (rectWidth + rectHeight) * 2;
} // namespace

struct MockCanvasDependencies
{
	std::stringstream output;
};

struct RectangleTestMiddleware : MockCanvasDependencies
{
	CMockCanvas mockCanvas;
	RectangleTestMiddleware()
		: mockCanvas(output)
	{
	}
};

TEST(Rectangle, TestRectangleCreating)
{
	RectangleTestMiddleware testMiddleware;
	auto rect = CRectangle(leftTopPoint, rectWidth, rectHeight, rectangleFillColor, rectangleOutlineColor);

	ASSERT_EQ(rect.GetLeftTop().x, leftTopPoint.x);
	ASSERT_EQ(rect.GetLeftTop().y, leftTopPoint.y);
	ASSERT_EQ(rect.GetRightBottom().x, rightBottomPoint.x);
	ASSERT_EQ(rect.GetRightBottom().y, rightBottomPoint.y);

	ASSERT_EQ(rect.GetWidth(), rectWidth);
	ASSERT_EQ(rect.GetHeight(), rectHeight);

	ASSERT_EQ(rect.GetArea(), rectArea);
	ASSERT_EQ(rect.GetPerimeter(), rectPerimeter);

	ASSERT_EQ(rect.GetFillColor(), rectangleFillColor);
	ASSERT_EQ(rect.GetOutlineColor(), rectangleOutlineColor);

	rect.Draw(testMiddleware.mockCanvas);
	auto expectedOutput = "Drawing rectangle 30*12.3 from (0, 0.5) with fill color 0 and outline color 1048575\n";
	ASSERT_EQ(testMiddleware.output.str(), expectedOutput);
}

TEST(Rectangle, TestInvalidRectnagleCreating)
{
	ASSERT_ANY_THROW(auto invalidRect = CRectangle({ 10, 10 }, -100, 200, rectangleFillColor, rectangleOutlineColor));
	ASSERT_ANY_THROW(auto invalidRect = CRectangle({ 10, 10 }, 100, -200, rectangleFillColor, rectangleOutlineColor));
}