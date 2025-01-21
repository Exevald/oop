#include <iostream>
#include "CCalculatorController.h"

int main() {
	CCalculator calculator;
	CCalculatorController calculatorController(calculator, std::cin, std::cout);

	std::cout << ">";
	while (true)
	{
		calculatorController.HandleCommand();
		std::cout << ">";
	}
}