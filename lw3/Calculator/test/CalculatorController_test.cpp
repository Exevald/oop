#include "../src/CCalculatorController.h"
#include <gtest/gtest.h>

struct CalculatorControllerDependencies
{
	CCalculator calc;
	std::stringstream input;
	std::stringstream output;
};

struct CalculatorControllerTestMiddleware : CalculatorControllerDependencies
{
	CCalculatorController calculatorController;

	CalculatorControllerTestMiddleware()
		: calculatorController(calc, input, output)
	{
	}

	void HandleCommand(const std::string& command)
	{
		input.str("");
		input.clear();
		output.str("");
		output.clear();

		input << command;
		calculatorController.HandleCommand();
	}

	void AssertCommandHandling(const std::string& command, const std::string& expectedOutput)
	{
		HandleCommand(command);

		ASSERT_EQ(input.eof(), true);
		ASSERT_EQ(output.str(), expectedOutput);
	}
};

TEST(CalculatorController, TestDefaultCommandsHandling)
{
	CalculatorControllerTestMiddleware testMiddleware;

	testMiddleware.AssertCommandHandling("", "Unknown command!\n");
	testMiddleware.AssertCommandHandling("aaa", "Unknown command!\n");
	testMiddleware.AssertCommandHandling("printvars", "");
	testMiddleware.AssertCommandHandling("printfns", "");
}

TEST(CalculatorController, TestVariableDefinition)
{
	CalculatorControllerTestMiddleware testMiddleware;

	testMiddleware.AssertCommandHandling("var i", "");
	testMiddleware.AssertCommandHandling("printvars", "i:nan\n");
	testMiddleware.AssertCommandHandling("var a", "");
	testMiddleware.AssertCommandHandling("var aa", "");
	testMiddleware.AssertCommandHandling("printvars", "a:nan\n"
													  "aa:nan\n"
													  "i:nan\n");
	testMiddleware.AssertCommandHandling("print a", "nan\n");

	testMiddleware.AssertCommandHandling("let b=10", "");
	testMiddleware.AssertCommandHandling("print b", "10.000000\n");
	testMiddleware.AssertCommandHandling("let a=20", "");
	testMiddleware.AssertCommandHandling("print a", "20.000000\n");
	testMiddleware.AssertCommandHandling("let c=a", "");
	testMiddleware.AssertCommandHandling("print c", "20.000000\n");
}

TEST(CalculatorController, TestUpdateVariableValue)
{
	CalculatorControllerTestMiddleware testMiddleware;

	testMiddleware.AssertCommandHandling("var i", "");
	testMiddleware.AssertCommandHandling("printvars", "i:nan\n");
	testMiddleware.AssertCommandHandling("let i=2", "");
	testMiddleware.AssertCommandHandling("printvars", "i:2.000000\n");
	testMiddleware.AssertCommandHandling("let b=1", "");
	testMiddleware.AssertCommandHandling("printvars", "b:1.000000\n"
													  "i:2.000000\n");
	testMiddleware.AssertCommandHandling("let b=i", "");
	testMiddleware.AssertCommandHandling("printvars", "b:2.000000\n"
													  "i:2.000000\n");
}

TEST(CalculatorController, TestFunctionDefinition)
{
	CalculatorControllerTestMiddleware testMiddleware;

	testMiddleware.AssertCommandHandling("let radius=2", "");
	testMiddleware.AssertCommandHandling("fn radiusSquared=radius*radius", "");
	testMiddleware.AssertCommandHandling("printfns", "radiusSquared:4.000000\n");
	testMiddleware.AssertCommandHandling("let radius=5", "");
	testMiddleware.AssertCommandHandling("printfns", "radiusSquared:25.000000\n");

	testMiddleware.AssertCommandHandling("fn radiusKube=radiusSquared*radius", "");
	testMiddleware.AssertCommandHandling("printfns", "radiusKube:125.000000\n"
													 "radiusSquared:25.000000\n");
	testMiddleware.AssertCommandHandling("let radius=4", "");
	testMiddleware.AssertCommandHandling("printfns", "radiusKube:100.000000\n"
													 "radiusSquared:16.000000\n");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
