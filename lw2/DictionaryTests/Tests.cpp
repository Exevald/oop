#include "../Dictionary/DictionaryModule.h"

#include <../../catch2/catch.hpp>
#include <map>
#include <string>

TEST_CASE("LoadDictionary: Invalid dictionary filename")
{
	Dictionary dictionary;
	std::string invalidFilename = "invalidFileName.txt";
	REQUIRE_THROWS_AS(LoadDict(invalidFilename, dictionary), std::runtime_error);
}

TEST_CASE("IsWordRussian: Assert russian word")
{
	std::string word = "Dog";
	REQUIRE(IsWordRussian(word) == false);
}

TEST_CASE("FindWord: Find word")
{
	Dictionary dictionary = {
		{ "cat", "Кошка" }
	};
	REQUIRE(FindWord("cat", dictionary) == "cat");
}