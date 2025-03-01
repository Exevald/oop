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

	testMiddleware.AssertCommandHandling("rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00");
	testMiddleware.AssertResult("Shape with max area:\n"
								"Area: 1240.280000\n"
								"Perimeter: 142.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 60.550000)\n"
								"Width: 30.700000\n"
								"Height: 40.400000\n\n"
								"Shape with min perimeter:\n"
								"Area: 1240.280000\n"
								"Perimeter: 142.200000\n"
								"LeftTop point: (10.300000, 20.150000)\n"
								"RightBottom point: (41.000000, 60.550000)\n"
								"Width: 30.700000\n"
								"Height: 40.400000\n");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}