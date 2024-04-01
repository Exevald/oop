#include "../Vector/VectorProcessor.h"

#include <../../catch2/catch.hpp>
#include <sstream>
#include <vector>

TEST_CASE("InitializeVectorFromStream: Empty input")
{
	std::istringstream input("");
	std::vector<float> vector;
	REQUIRE_THROWS(vector = InitializeVectorFromStream(input));
}