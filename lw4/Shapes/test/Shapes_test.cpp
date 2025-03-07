#include "CShapesController.h"
#include <gtest/gtest.h>

struct ShapesControllerDependencies
{
	std::stringstream input;
	std::stringstream output;
};

struct ShapesControllerTestMiddleware : ShapesControllerDependencies
{
	CShapesController shapesController;
	ShapesControllerTestMiddleware()
		: shapesController(input, output)
	{
	}

	void HandleCommand(const std::string& command)
	{
		input.str("");
		input.clear();
		output.str("");
		output.clear();

		input << command;
		shapesController.HandleCommand();
	}

	void AssertCommandHandling(const std::string& command)
	{
		HandleCommand(command);
		ASSERT_EQ(input.eof(), true);
	}

	void AssertResult(const std::string& expectedOutput = "")
	{
		shapesController.PrintResult();
		ASSERT_EQ(output.str(), expectedOutput);
	}
};

TEST(ShapesController, TestCommandsHandling)
{
	ShapesControllerTestMiddleware testMiddleware;

	testMiddleware.AssertResult("Shapes are not exist\n");

	testMiddleware.AssertCommandHandling("aaa");
	testMiddleware.AssertResult("Unknown command!\nShapes are not exist\n");

	testMiddleware.AssertCommandHandling("rectangle 10.3 20.15 30.7 40.4 D9D9D9 D9D9D9");
	testMiddleware.AssertResult("Shape with max circleArea:\n"
								"Area: 1240.280000\n"
								"Perimeter: 142.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 60.550000)\n"
								"Width: 30.700000\n"
								"Height: 40.400000\n\n"
								"Shape with min circlePerimeter:\n"
								"Area: 1240.280000\n"
								"Perimeter: 142.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 60.550000)\n"
								"Width: 30.700000\n"
								"Height: 40.400000\n");
}

TEST(ShapesController, TestCalculateShapesInfo)
{
	ShapesControllerTestMiddleware testMiddleware;

	testMiddleware.AssertCommandHandling("rectangle 10.3 20.15 30.7 40.4 D9D9D9 D9D9D9");
	testMiddleware.AssertCommandHandling("rectangle 10.3 20.15 30.7 500.4 D9D9D9 D9D9D9");
	testMiddleware.AssertResult("Shape with max circleArea:\n"
								"Area: 15362.280000\n"
								"Perimeter: 1062.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 520.550000)\n"
								"Width: 30.700000\n"
								"Height: 500.400000\n\n"
								"Shape with min circlePerimeter:\n"
								"Area: 1240.280000\n"
								"Perimeter: 142.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 60.550000)\n"
								"Width: 30.700000\n"
								"Height: 40.400000\n");

	testMiddleware.AssertCommandHandling("circle 340 360 12 000000 000000");
	testMiddleware.AssertResult("Shape with max circleArea:\n"
								"Area: 15362.280000\n"
								"Perimeter: 1062.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 520.550000)\n"
								"Width: 30.700000\n"
								"Height: 500.400000\n\n"
								"Shape with min circlePerimeter:\n"
								"Area: 452.389342\n"
								"Perimeter: 75.398224\n"
								"Center point: (340.000000, 360.000000)\n"
								"Radius: 12.000000)\n");

	testMiddleware.AssertCommandHandling("line 10 396 15 406 8E8E8E");
	testMiddleware.AssertResult("Shape with max circleArea:\n"
								"Area: 15362.280000\n"
								"Perimeter: 1062.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 520.550000)\n"
								"Width: 30.700000\n"
								"Height: 500.400000\n\n"
								"Shape with min circlePerimeter:\n"
								"Area: 0.000000\n"
								"Perimeter: 11.180340\n"
								"Start point: (10.000000, 396.000000)\n"
								"End point: (15.000000, 406.000000)\n");

	testMiddleware.AssertCommandHandling("triangle 0 0 500 500 500 0 000000 000000");
	testMiddleware.AssertResult("Shape with max circleArea:\n"
								"Area: 125000.000000\n"
								"Perimeter: 1707.106781\n"
								"Vertex 1: (0.000000, 0.000000)\n"
								"Vertex 2: (500.000000, 500.000000)\n"
								"Vertex 3: (500.000000, 0.000000)\n\n"
								"Shape with min circlePerimeter:\n"
								"Area: 0.000000\n"
								"Perimeter: 11.180340\n"
								"Start point: (10.000000, 396.000000)\n"
								"End point: (15.000000, 406.000000)\n");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}