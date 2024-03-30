#include "PrimeNumbersGenerator.h"

#include <unordered_set>
#include <vector>

std::unordered_set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
	{
		return {};
	}
	std::vector<int> primes(upperBound + 1, true);
	primes[0] = primes[1] = false;
	for (int i = 3; i * i <= upperBound; i += 2)
	{
		if (primes[i])
		{
			for (int j = i * i; j <= upperBound; j += i * 2)
			{
				primes[j] = false;
			}
		}
	}
	std::unordered_set<int> primeNumbers;
	primeNumbers.insert(2);
	for (int i = 3; i <= upperBound; i += 2)
	{
		if (primes[i])
		{
			primeNumbers.insert(i);
		}
	}
	return primeNumbers;
}
