#include "TemplateExpander.h"
#include <gtest/gtest.h>

using TemplateParams = std::unordered_map<std::string, std::string>;

TEST(ExpandTemplateTests, EmptyTemplateAndNoParams)
{
	std::string tpl;
	TemplateParams params;

	EXPECT_TRUE(ExpandTemplate(tpl, params).empty());
}

TEST(ExpandTemplateTests, NotEmptyTemplateWithoutParams)
{
	std::string tpl = "Hello %NAME%";
	TemplateParams params;

	EXPECT_EQ(ExpandTemplate(tpl, params), tpl);
}

TEST(ExpandTemplateTests, NotEmptyTemplateWithNonExistentParams)
{
	std::string tpl = "Hello %NAME%";
	TemplateParams params = {
		{ "%SURNAME%", "Ivanov" }
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), tpl);
}

TEST(ExpandTemplateTests, TemplateIsEqualToParam)
{
	std::string tpl = "%NAME%";
	TemplateParams params = {
		{ "%NAME%", "Konstantin" }
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "Konstantin");
}

TEST(ExpandTemplateTests, EmptyTemplateWithEmptyParamKeys)
{
	std::string tpl = "Hello, world!";
	TemplateParams params = {
		{ "", "Hello" },
		{ "", " " },
		{ "", "" }
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), tpl);
}

TEST(ExpandTemplateTests, EmptyTemplateParamValues)
{
	std::string tpl = "Hello, world!";
	TemplateParams params = {
		{ "world", "" },
		{ "!", "" },
		{ " ", "" },
		{ ",", "." }
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "Hello.");
}

TEST(ExpandTemplateTests, TemplateConsistsOnlyOfParameters)
{
	std::string tpl = "%NAME%%AGE%";
	TemplateParams params = {
		{ "%NAME%", "Konstantin" },
		{ "%AGE%", "20" }
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "Konstantin20");
}

TEST(ExpandTemplateTests, TemplateContainsSeveralDifferentParameters)
{
	std::string tpl = "Hello, %USER_NAME%! Let's {ACTION}.";
	TemplateParams params = {
		{ "%USER_NAME%", "Konstantin" },
		{ "{ACTION}", "code" }
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "Hello, Konstantin! Let's code.");
}

TEST(ExpandTemplateTests, ParameterValuesContainParameters)
{
	std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
	TemplateParams params = {
		{ "%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}" },
		{ "{WEEK_DAY}", "Saturday. {WEEK_DAY}" }
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Saturday. {WEEK_DAY}.");
}

TEST(ExpandTemplateTests, ParameterPrefixIsAlsoParameter)
{
	std::string tpl = "AAA";
	TemplateParams params = {
		{ "A", "[a]" },
		{ "AA", "[aa]" },
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "[aa][a]");
}

TEST(ExpandTemplateTests, ParameterPrefixIsAlsoParameterExtended)
{
	std::string tpl = "-AABBCCCCCABC+";
	TemplateParams params = {
		{ "A", "[a]" },
		{ "AA", "[aa]" },
		{ "B", "[b]" },
		{ "BB", "[bb]" },
		{ "C", "[c]" },
		{ "CC", "[cc]" },
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "-[aa][bb][cc][cc][c][a][b][c]+");
}

TEST(ExpandTemplateTests, PrefixOfOneParameterIsSuffixOfAnother)
{
	std::string tpl = "-ABCED+";
	TemplateParams params = {
		{ "ABCD", "[abcd]" },
		{ "BCE", "[bce]" },
	};

	EXPECT_EQ(ExpandTemplate(tpl, params), "-A[bce]D+");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}