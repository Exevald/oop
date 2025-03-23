#include "../src/CArray.h"
#include <gtest/gtest.h>

TEST(Array, TestPushAndAccess)
{
	CArray<int> arr;
	arr.Push(1);
	arr.Push(2);
	ASSERT_EQ(arr[0], 1);
	ASSERT_EQ(arr[1], 2);
}

TEST(Array, TestResize)
{
	CArray<int> arr;
	arr.Resize(5);
	ASSERT_EQ(arr.GetSize(), 5);
	ASSERT_EQ(arr[4], 0);
}

TEST(Array, TestCopyConstructor)
{
	CArray<int> arr;
	arr.Push(1);
	arr.Push(2);
	arr = CArray<int>(arr);

	CArray<int> arr2(arr);
	ASSERT_EQ(arr2[0], 1);
	ASSERT_EQ(arr2[1], 2);
}

TEST(Array, TestMoveConstructor)
{
	CArray<int> arr;
	arr.Push(1);
	arr.Push(2);
	CArray<int> arr2(std::move(arr));
	ASSERT_EQ(arr2[0], 1);
	ASSERT_EQ(arr2[1], 2);
	ASSERT_EQ(arr.GetSize(), 0);
}

TEST(Array, TestAssignmentOperator)
{
	CArray<int> arr;
	arr.Push(1);
	arr.Push(2);
	arr = arr;

	CArray<int> arr2;
	arr2 = arr;
	ASSERT_EQ(arr2[0], 1);
	ASSERT_EQ(arr2[1], 2);
}

TEST(Array, TestMoveAssignmentOperator)
{
	CArray<int> arr;
	arr.Push(1);
	arr.Push(2);
	arr = std::move(arr);
	ASSERT_EQ(arr.GetSize(), 2);

	CArray<int> arr2;
	arr2 = std::move(arr);
	ASSERT_EQ(arr2[0], 1);
	ASSERT_EQ(arr2[1], 2);
	ASSERT_EQ(arr.GetSize(), 0);
}

TEST(Array, TestCrossTypeAssignment)
{
	CArray<int> intArray;
	intArray.Push(1);
	intArray.Push(2);
	CArray<double> doubleArray;
	doubleArray = intArray;
	ASSERT_EQ(doubleArray[0], 1.0);
	ASSERT_EQ(doubleArray[1], 2.0);
}

TEST(Array, TestOutOfRangeAccess)
{
	CArray<int> arr;
	arr.Push(1);
	ASSERT_THROW(arr[1], std::out_of_range);
}

TEST(Array, TestRangeBasedFor)
{
	CArray<int> arr;
	arr.Push(1);
	arr.Push(2);

	for (auto& item : arr)
	{
		item++;
	}
	ASSERT_EQ(arr[0], 2);
	ASSERT_EQ(arr[1], 3);
}