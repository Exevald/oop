#include "Car.h"
#include "CarController.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>

int main()
{
	CCar car;
	CCarController carController(car);

	std::cout << ">";
	while (true)
	{
		carController.HandleCommand();
		std::cout << ">";
	}

	return EXIT_SUCCESS;
}