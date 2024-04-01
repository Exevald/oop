#include "AriphmeticExpressionModule.h"

#include <map>
#include <sstream>

bool IsSymbolValid(const char ch)
{
	return (ch > '0' && ch < '9' || ch == '(' || ch == '-') ? true : false;
}

int HandleOperator(std::istream& input, char operand)
{
	int result = (operand == '+') ? 0 : 1;
	char ch;
	while (input >> ch && ch != ')')
	{
		if (!IsSymbolValid(ch))
		{
			throw std::runtime_error("Invalid symbol");
		}
		if (ch == '(')
		{
			input.unget();
			result = (operand == '+') ? result += CalculateExpression(input) : result *= CalculateExpression(input);
		}
		else
		{
			input.unget();
			int num;
			input >> num;
			result = (operand == '+') ? result += num : result *= num;
		}
	}
	if (ch != ')')
	{
		throw std::runtime_error("Invalid expression");
	}
	return result;
}

int CalculateExpression(std::istream& input)
{
	char ch;
	int result = 0;
	input >> ch;
	if (ch != '(')
	{
		throw std::runtime_error("Invalid expression");
	}
	input >> ch;
	if (ch == '+')
	{
		result = HandleOperator(input, '+');
	}
	else if (ch == '*')
	{
		result = HandleOperator(input, '*');
	}
	return result;
}