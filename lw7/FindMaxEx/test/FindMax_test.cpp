#include "../src/FindMaxProcessor.h"
#include <gtest/gtest.h>

namespace
{
struct Athlete
{
	std::string name;
	double height = 0;
	double weight = 0;
};

bool CompareByHeight(const Athlete& a, const Athlete& b)
{
	return a.height < b.height;
}

bool CompareByWeight(const Athlete& a, const Athlete& b)
{
	return a.weight < b.weight;
}
} // namespace

TEST(FindMaxTest, TestEmptyArray)
{
	std::vector<int> arr;
	int maxValue;
	ASSERT_FALSE(FindMax(arr, maxValue, std::less<int>()));
}

TEST(FindMaxTest, TestSingleElementArray)
{
	std::vector<int> arr = { 42 };
	int maxValue;
	ASSERT_TRUE(FindMax(arr, maxValue, std::less<int>()));
	ASSERT_EQ(maxValue, 42);
}

TEST(FindMaxTest, TestMultipleElementsArray)
{
	std::vector<int> arr = { 3, 1, 4, 1, 5, 9, 2, 6 };
	int maxValue;
	ASSERT_TRUE(FindMax(arr, maxValue, std::less<int>()));
	ASSERT_EQ(maxValue, 9);
}

TEST(FindMaxTest, TestAthleteMaxHeight)
{
	std::vector<Athlete> athletes = {
		{ "Alice", 170.0, 60.0 },
		{ "Bob", 180.0, 80.0 },
		{ "Charlie", 160.0, 70.0 }
	};
	Athlete maxAthlete;
	ASSERT_TRUE(FindMax(athletes, maxAthlete, CompareByHeight));
	ASSERT_EQ(maxAthlete.name, "Bob");
	ASSERT_EQ(maxAthlete.height, 180.0);
}

TEST(FindMaxTest, TestAthleteMaxWeight)
{
	std::vector<Athlete> athletes = {
		{ "Alice", 170.0, 60.0 },
		{ "Bob", 180.0, 80.0 },
		{ "Charlie", 160.0, 70.0 }
	};
	Athlete maxAthlete;
	ASSERT_TRUE(FindMax(athletes, maxAthlete, CompareByWeight));
	ASSERT_EQ(maxAthlete.name, "Bob");
	ASSERT_EQ(maxAthlete.weight, 80.0);
}

TEST(FindMaxTest, TestCustomComparator)
{
	std::vector<std::string> arr = { "apple", "banana", "cherry" };
	std::string maxValue;
	ASSERT_TRUE(FindMax(arr, maxValue, [](const std::string& a, const std::string& b) {
		return a.length() < b.length();
	}));
	ASSERT_EQ(maxValue, "banana");
}
