#include "CMockCanvas.h"
#include "CTriangle.h"
#include <gtest/gtest.h>

namespace
{
constexpr CPoint vertex1 = { -3, 0 };
constexpr CPoint vertex2 = { 3, 0 };
constexpr CPoint vertex3 = { 0, 4 };
constexpr double trianglePerimeter = 16;
constexpr double triangleArea = 12;
constexpr uint32_t triangleFillColor = 0x00000;
constexpr uint32_t triangleOutlineColor = 0xFFFFF;

} // namespace

struct MockCanvasDependencies
{
	std::stringstream output;
};

struct TriangleTestMiddleware : MockCanvasDependencies
{
	CMockCanvas mockCanvas;
	TriangleTestMiddleware()
		: mockCanvas(output)
	{
	}
};

TEST(Triangle, TestDefaultTriangleCreaion)
{
	TriangleTestMiddleware testMiddleware;
	auto triangle = CTriangle(vertex1, vertex2, vertex3, triangleFillColor, triangleOutlineColor);

	ASSERT_EQ(triangle.GetVertex1().x, vertex1.x);
	ASSERT_EQ(triangle.GetVertex1().y, vertex1.y);
	ASSERT_EQ(triangle.GetVertex2().x, vertex2.x);
	ASSERT_EQ(triangle.GetVertex2().y, vertex2.y);
	ASSERT_EQ(triangle.GetVertex3().x, vertex3.x);
	ASSERT_EQ(triangle.GetVertex3().x, vertex3.x);

	ASSERT_EQ(triangle.GetPerimeter(), trianglePerimeter);
	ASSERT_EQ(triangle.GetArea(), triangleArea);

	triangle.Draw(testMiddleware.mockCanvas);
	auto expectedOutput = "Drawing polygon with fill color 0 and outline color 1048575 in vertexes: (-3, 0) (3, 0) (0, 4)\n";
	ASSERT_EQ(testMiddleware.output.str(), expectedOutput);
}

TEST(Triangle, TestInvalidTriangleCreation)
{
	ASSERT_ANY_THROW(auto triangle = CTriangle({ 0, 0 }, { 1, 1 }, { 2, 2 }, triangleFillColor, triangleOutlineColor));
}