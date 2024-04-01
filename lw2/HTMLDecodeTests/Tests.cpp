#include "../HTMLDecode/HTMLDecoder.h"

#include <../../catch2/catch.hpp>
#include <sstream>
#include <string>
#include <vector>

TEST_CASE("HtmlDecode: Decode empty string")
{
	REQUIRE(HtmlDecode("") == "");
}

TEST_CASE("HtmlDecode: Decode string")
{
	std::string resultString = "Cat <says> \"Meow\". M&M's";
	REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == resultString);
}

TEST_CASE("HtmlDecode: Decode inknows entities")
{
	std::string resultString = "Cat &let;says&get; \"Meow\". M&M's";
	REQUIRE(HtmlDecode("Cat &let;says&get; &quot;Meow&quot;. M&amp;M&apos;s") == resultString);
}