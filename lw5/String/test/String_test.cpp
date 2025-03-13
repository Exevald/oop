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
	CString str1("Hello");
	CString str2;
	str2 = str1;
	ASSERT_EQ(str2.GetLength(), 5);
	ASSERT_EQ(str2.GetCapacity(), 6);
	ASSERT_STREQ(str2.GetStringData(), "Hello");
}

TEST(String, TestMoveAssignmentOperator)
{
	CString str1("Hello");
	CString str2;
	str2 = std::move(str1);
	ASSERT_EQ(str2.GetLength(), 5);
	ASSERT_EQ(str2.GetCapacity(), 6);
	ASSERT_STREQ(str2.GetStringData(), "Hello");
	ASSERT_EQ(str1.GetLength(), 0);
	ASSERT_EQ(str1.GetCapacity(), 0);
	ASSERT_EQ(str1.GetStringData(), nullptr);
}

TEST(String, TestOperatorPlus)
{
	CString str1("Hello");
	CString str2(" World");
	CString result = str1 + str2;
	ASSERT_EQ(result.GetLength(), 11);
	ASSERT_EQ(result.GetCapacity(), 12);
	ASSERT_STREQ(result.GetStringData(), "Hello World");
}

TEST(String, TestOperatorPlusEquals)
{
	CString str1("Hello");
	CString str2(" World");
	str1 += str2;
	ASSERT_EQ(str1.GetLength(), 11);
	ASSERT_EQ(str1.GetCapacity(), 12);
	ASSERT_STREQ(str1.GetStringData(), "Hello World");
}

TEST(String, TestOperatorEquals)
{
	CString str1("Hello");
	CString str2("Hello");
	ASSERT_TRUE(str1 == str2);
}

TEST(String, TestOperatorNotEquals)
{
	CString str1("Hello");
	CString str2("World");
	ASSERT_TRUE(str1 != str2);
}

TEST(String, TestOperatorLessThan)
{
	CString str1("Apple");
	CString str2("Banana");
	ASSERT_TRUE(str1 < str2);
}

TEST(String, TestOperatorGreaterThan)
{
	CString str1("Banana");
	CString str2("Apple");
	ASSERT_TRUE(str1 > str2);
}

TEST(String, TestOperatorLessThanOrEqual)
{
	CString str1("Apple");
	CString str2("Banana");
	ASSERT_TRUE(str1 <= str2);
}

TEST(String, TestOperatorGreaterThanOrEqual)
{
	CString str1("Banana");
	CString str2("Apple");
	ASSERT_TRUE(str1 >= str2);
}

TEST(String, TestSubString)
{
	CString str("Hello World");
	CString subStr = str.SubString(6, 5);
	ASSERT_EQ(subStr.GetLength(), 5);
	ASSERT_EQ(subStr.GetCapacity(), 6);
	ASSERT_STREQ(subStr.GetStringData(), "World");
}

TEST(String, TestTestSubStringOutOfRange)
{
	CString str("Hello World");
	ASSERT_THROW(str.SubString(12, 5), std::out_of_range);
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