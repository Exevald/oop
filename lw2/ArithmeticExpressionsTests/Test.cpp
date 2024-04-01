#include "../ArithmeticExpressions/AriphmeticExpressionModule.h"

#include <../../catch2/catch.hpp>
#include <sstream>
#include <string>

TEST_CASE("CalculateExpression: Empty input")
{
	std::istringstream input("");
	const std::string expectedExceptionMessage = "Invalid expression";
	REQUIRE_THROWS_WITH(CalculateExpression(input), expectedExceptionMessage);
}

TEST_CASE("CalculateExpression: Expression with single argument")
{
	std::istringstream input("(+ 7)");
	const int expectedResult = 7;
	const int result = CalculateExpression(input);
	REQUIRE(result == expectedResult);
}

TEST_CASE("CalculateExpression: Expression with many arguments")
{
	std::istringstream input("(* 2 3 4)");
	const int expectedResult = 24;
	const int result = CalculateExpression(input);
	REQUIRE(result == expectedResult);
}

TEST_CASE("CalculateExpression: Expression with priority")
{
	std::istringstream input("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2) ))");
	const int expectedResult = 33;
	const int result = CalculateExpression(input);
	REQUIRE(result == expectedResult);
}

TEST_CASE("CalculateExpression: Expression with negative argument")
{
	std::istringstream input("(+ -2 3)");
	const int expectedResult = 1;
	const int result = CalculateExpression(input);
	REQUIRE(result == expectedResult);
}

TEST_CASE("CalculateExpression: Exception with no first bracer")
{
	std::istringstream input("* 2 3 4");
	const std::string expectedExceptionMessage = "Invalid expression";
	REQUIRE_THROWS_WITH(CalculateExpression(input), expectedExceptionMessage);
}

TEST_CASE("CalculateExpression: Exception with no last bracer")
{
	std::istringstream input("(* 2 3 4");
	const std::string expectedExceptionMessage = "Invalid expression";
	REQUIRE_THROWS_WITH(CalculateExpression(input), expectedExceptionMessage);
}

TEST_CASE("CalculateExpression: Invalid symbol exception")
{
	std::istringstream input("(+ abc2 3 4)");
	const std::string expectedExceptionMessage = "Invalid symbol";
	REQUIRE_THROWS_WITH(CalculateExpression(input), expectedExceptionMessage);
}