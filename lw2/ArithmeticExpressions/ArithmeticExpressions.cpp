#include "AriphmeticExpressionModule.h"

#include <iostream>
#include <string>
#include <sstream>

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			std::istringstream input(line);
			int result = CalculateExpression(input);
			std::cout << "Result: " << result << std::endl;
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return EXIT_FAILURE;
		}
	}
	if (!std::cin.eof())
	{
		std::cout << "Failed to read line from input stream" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}