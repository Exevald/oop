#include "TemplateExpander.h"
#include <gtest/gtest.h>

using TemplateParams = std::unordered_map<std::string, std::string>;

TEST(ExpandTemplateTests, EmptyTemplateAndNoParams)
{
	std::string templateString;
	TemplateParams params;

	EXPECT_TRUE(ExpandTemplate(templateString, params).empty());
}

TEST(ExpandTemplateTests, NotEmptyTemplateWithoutParams)
{
	std::string templateString = "Hello %NAME%";
	TemplateParams params;

	EXPECT_EQ(ExpandTemplate(templateString, params), templateString);
}

TEST(ExpandTemplateTests, NotEmptyTemplateWithNonExistentParams)
{
	std::string templateString = "Hello %NAME%";
	TemplateParams params = {
		{ "%SURNAME%", "Ivanov" }
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), templateString);
}

TEST(ExpandTemplateTests, TemplateIsEqualToParam)
{
	std::string templateString = "%NAME%";
	TemplateParams params = {
		{ "%NAME%", "Konstantin" }
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "Konstantin");
}

TEST(ExpandTemplateTests, EmptyTemplateWithEmptyParamKeys)
{
	std::string templateString = "Hello, world!";
	TemplateParams params = {
		{ "", "Hello" },
		{ "", " " },
		{ "", "" }
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), templateString);
}

TEST(ExpandTemplateTests, EmptyTemplateParamValues)
{
	std::string templateString = "Hello, world!";
	TemplateParams params = {
		{ "world", "" },
		{ "!", "" },
		{ " ", "" },
		{ ",", "." }
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "Hello.");
}

TEST(ExpandTemplateTests, TemplateConsistsOnlyOfParameters)
{
	std::string templateString = "%NAME%%AGE%";
	TemplateParams params = {
		{ "%NAME%", "Konstantin" },
		{ "%AGE%", "20" }
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "Konstantin20");
}

TEST(ExpandTemplateTests, TemplateContainsSeveralDifferentParameters)
{
	std::string templateString = "Hello, %USER_NAME%! Let's {ACTION}.";
	TemplateParams params = {
		{ "%USER_NAME%", "Konstantin" },
		{ "{ACTION}", "code" }
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "Hello, Konstantin! Let's code.");
}

TEST(ExpandTemplateTests, ParameterValuesContainParameters)
{
	std::string templateString = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
	TemplateParams params = {
		{ "%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}" },
		{ "{WEEK_DAY}", "Saturday. {WEEK_DAY}" }
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Saturday. {WEEK_DAY}.");
}

TEST(ExpandTemplateTests, ParameterPrefixIsAlsoParameter)
{
	std::string templateString = "AAA";
	TemplateParams params = {
		{ "A", "[a]" },
		{ "AA", "[aa]" },
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "[aa][a]");
}

TEST(ExpandTemplateTests, ParameterPrefixIsAlsoParameterExtended)
{
	std::string templateString = "-AABBCCCCCABC+";
	TemplateParams params = {
		{ "A", "[a]" },
		{ "AA", "[aa]" },
		{ "B", "[b]" },
		{ "BB", "[bb]" },
		{ "C", "[c]" },
		{ "CC", "[cc]" },
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "-[aa][bb][cc][cc][c][a][b][c]+");
}

TEST(ExpandTemplateTests, PrefixOfOneParameterIsSuffixOfAnother)
{
	std::string templateString = "-ABCED+";
	TemplateParams params = {
		{ "ABCD", "[abcd]" },
		{ "BCE", "[bce]" },
	};

	EXPECT_EQ(ExpandTemplate(templateString, params), "-A[bce]D+");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}