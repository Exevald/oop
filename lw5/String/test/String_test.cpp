#include "CString.h"
#include <gtest/gtest.h>

TEST(String, TestDefaultConstructor)
{
	CString str;
	str = std::move(str);
	ASSERT_EQ(str.GetLength(), 0);
	ASSERT_EQ(str.GetCapacity(), 1);
	ASSERT_STREQ(str.GetStringData(), "");
}

TEST(String, TestConstructorWithString)
{
	CString str("Hello");
	ASSERT_EQ(str.GetLength(), 5);
	ASSERT_EQ(str.GetCapacity(), 6);
	ASSERT_STREQ(str.GetStringData(), "Hello");
}

TEST(String, TestConstructorWithStringAndLength)
{
	CString str("Hello World", 5);
	ASSERT_EQ(str.GetLength(), 5);
	ASSERT_EQ(str.GetCapacity(), 6);
	ASSERT_STREQ(str.GetStringData(), "Hello");
}

TEST(String, TestCopyConstructor)
{
	CString str1("Hello");
	const CString& str2(str1);
	ASSERT_EQ(str2.GetLength(), 5);
	ASSERT_EQ(str2.GetCapacity(), 6);
	ASSERT_STREQ(str2.GetStringData(), "Hello");
}

TEST(String, TestMoveConstructor)
{
	CString str1("Hello");
	CString str2(std::move(str1));
	ASSERT_EQ(str2.GetLength(), 5);
	ASSERT_EQ(str2.GetCapacity(), 6);
	ASSERT_STREQ(str2.GetStringData(), "Hello");
	ASSERT_EQ(str1.GetLength(), 0);
	ASSERT_EQ(str1.GetCapacity(), 0);
	ASSERT_EQ(str1.GetStringData(), nullptr);
}

TEST(String, TestAssignmentOperator)
{
	const CString str1("Hello");
	const CString& str2 = str1;
	ASSERT_EQ(str2.GetLength(), 5);
	ASSERT_EQ(str2.GetCapacity(), 6);
	ASSERT_STREQ(str2.GetStringData(), "Hello");
}

TEST(String, TestMoveAssignmentOperator)
{
	CString str1("Hello");
	const CString str2 = std::move(str1);
	ASSERT_EQ(str2.GetLength(), 5);
	ASSERT_EQ(str2.GetCapacity(), 6);
	ASSERT_STREQ(str2.GetStringData(), "Hello");
	ASSERT_EQ(str1.GetLength(), 0);
	ASSERT_EQ(str1.GetCapacity(), 0);
	ASSERT_EQ(str1.GetStringData(), nullptr);
}

TEST(String, TestOperatorPlus)
{
	const CString str1("Hello");
	const CString str2(" World");
	const CString result = str1 + str2;
	ASSERT_EQ(result.GetLength(), 11);
	ASSERT_EQ(result.GetCapacity(), 12);
	ASSERT_STREQ(result.GetStringData(), "Hello World");
}

TEST(String, TestOperatorPlusEquals)
{
	CString str1("Hello");
	const CString str2(" World");
	str1 += str2;
	ASSERT_EQ(str1.GetLength(), 11);
	ASSERT_EQ(str1.GetCapacity(), 12);
	ASSERT_STREQ(str1.GetStringData(), "Hello World");
}

TEST(String, TestOperatorEquals)
{
	const CString str1("Hello");
	const CString str2("Hello");
	ASSERT_TRUE(str1 == str2);
}

TEST(String, TestOperatorNotEquals)
{
	const CString str1("Hello");
	const CString str2("World");
	ASSERT_TRUE(str1 != str2);
}

TEST(String, TestOperatorLessThan)
{
	const CString str1("Apple");
	const CString str2("Banana");
	ASSERT_TRUE(str1 < str2);
}

TEST(String, TestOperatorGreaterThan)
{
	const CString str1("Banana");
	const CString str2("Apple");
	ASSERT_TRUE(str1 > str2);
}

TEST(String, TestOperatorLessThanOrEqual)
{
	const CString str1("Apple");
	const CString str2("Banana");
	ASSERT_TRUE(str1 <= str2);
}

TEST(String, TestOperatorGreaterThanOrEqual)
{
	const CString str1("Banana");
	const CString str2("Apple");
	ASSERT_TRUE(str1 >= str2);
}

TEST(String, TestSubString)
{
	const CString str("Hello World");
	const CString subStr = str.SubString(6, 5);
	ASSERT_EQ(subStr.GetLength(), 5);
	ASSERT_EQ(subStr.GetCapacity(), 6);
	ASSERT_STREQ(subStr.GetStringData(), "World");
}

TEST(String, TestTestSubStringOutOfRange)
{
	const CString str("Hello World");
	ASSERT_THROW(auto subString = str.SubString(12, 5), std::out_of_range);
}

TEST(String, TestClear)
{
	CString str("Hello");
	str.Clear();
	ASSERT_EQ(str.GetLength(), 0);
	ASSERT_EQ(str.GetCapacity(), 1);
	ASSERT_STREQ(str.GetStringData(), "");
}

TEST(String, TestIndexOperator)
{
	CString str("Hello");
	ASSERT_EQ(str[0], 'H');
	ASSERT_EQ(str[4], 'o');
	ASSERT_THROW(str[5], std::out_of_range);
}

TEST(String, TestIndexOperatorConst)
{
	const CString str("Hello");
	ASSERT_EQ(str[0], 'H');
	ASSERT_EQ(str[4], 'o');
	ASSERT_THROW(str[5], std::out_of_range);
}

TEST(String, TestStreamOutput)
{
	CString str("Hello");
	std::ostringstream oss;
	oss << str;
	ASSERT_EQ(oss.str(), "Hello");
}

TEST(String, TestStreamInput)
{
	CString str;
	std::istringstream iss("Hello");
	iss >> str;
	ASSERT_EQ(str.GetLength(), 5);
	ASSERT_EQ(str.GetCapacity(), 6);
	ASSERT_STREQ(str.GetStringData(), "Hello");
}

TEST(StringIterator, IterateOverStringUsingIterator)
{
	CString str("Hello");
	std::string result;

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		result.push_back(*it);
	}

	ASSERT_EQ(result, "Hello");
}

TEST(StringIterator, IterateOverStringUsingConstIterator)
{
	const CString str("World");
	std::string result;

	for (auto it = str.cbegin(); it != str.cend(); ++it)
	{
		result.push_back(*it);
	}

	ASSERT_EQ(result, "World");
}

TEST(StringIterator, RangeBasedForLoop)
{
	CString str("Range");
	std::string result;

	for (const char c : str)
	{
		result.push_back(c);
	}

	ASSERT_EQ(result, "Range");
}

TEST(StringIterator, TestModifyStringUsingIterator)
{
	CString str("Hello");
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (*it == 'H')
		{
			*it = 'J';
		}
	}
	ASSERT_STREQ(str.GetStringData(), "Jello");
}

TEST(StringIterator, TestConstIteratorDoesNotAllowModification)
{
	const CString str("Hello");
	const auto it = str.cbegin();
	ASSERT_EQ(*it, 'H');
}

TEST(StringIterator, TestIteratorArithmetic)
{
	CString str("Hello");
	auto it = str.begin();
	it += 2;
	ASSERT_EQ(*it, 'l');

	auto it2 = it + 2;
	ASSERT_EQ(*it2, 'o');

	const auto diff = it2 - it;
	ASSERT_EQ(diff, 2);

	it2 -= 1;
	ASSERT_EQ(*it2, 'l');
}

TEST(StringIterator, TestIteratorComparison)
{
	CString str("Hello");
	const auto it1 = str.begin();
	const auto it2 = str.begin() + 2;

	ASSERT_TRUE(it1 < it2);
	ASSERT_TRUE(it2 > it1);
	ASSERT_TRUE(it1 <= it2);
	ASSERT_TRUE(it2 >= it1);
	ASSERT_FALSE(it1 == it2);

	const auto it3 = str.begin();
	ASSERT_TRUE(it1 == it3);
}

TEST(StringIterator, TestIndexedAccessOperator)
{
	CString str("Hello");
	const auto it = str.begin();

	ASSERT_EQ(it[0], 'H');
	ASSERT_EQ(it[1], 'e');
	ASSERT_EQ(it[4], 'o');
}