#include "../PrimeNumbers/PrimeNumbersGenerator.h"

#include <../../catch2/catch.hpp>
#include <unordered_set>

TEST_CASE("GeneratePrimeNumbersSet: Generate prime numbers set with upper bound 1")
{
	const int upperBound = 1;
	std::unordered_set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primeNumbersSet == std::unordered_set<int>{});
}

TEST_CASE("GeneratePrimeNumbersSet: Generate prime numbers set with upper bound 5")
{
	const int upperBound = 5;
	std::unordered_set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primeNumbersSet == std::unordered_set<int>{ 2, 3, 5 });
}

#ifndef DEBUG

TEST_CASE("GeneratePrimeNumbersSet: Generate prime numbers set with upper bound 100000000")
{
	const int upperBound = 100000000;
	const int expectedPrimeNumbersCount = 5761455;
	std::unordered_set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primeNumbersSet.size() == expectedPrimeNumbersCount);
}

#endif