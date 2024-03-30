#include "PrimeNumbersGenerator.h"

#include <iostream>
#include <unordered_set>
#include <vector>

int main()
{
	int upperBound;
	std::cout << "Please, write upper bound for prime numbers set" << std::endl;
	std::cin >> upperBound;

	std::unordered_set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	for (const int& prime : primeNumbers)
	{
		std::cout << prime << std::endl;
	}
	return 0;
}