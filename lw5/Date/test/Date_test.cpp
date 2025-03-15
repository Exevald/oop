#include "CDate.h"
#include <gtest/gtest.h>

TEST(Date, TestDefaultConstructor)
{
	CDate date;
	ASSERT_EQ(date.GetDay(), 1);
	ASSERT_EQ(date.GetMonth(), Month::JANUARY);
	ASSERT_EQ(date.GetYear(), 1970);
	ASSERT_EQ(date.GetWeekDay(), WeekDay::THURSDAY);
	ASSERT_TRUE(date.IsValid());
}

TEST(Date, TestConstructorWithParameters)
{
	CDate date(12, Month::MARCH, 2025);
	ASSERT_EQ(date.GetDay(), 12);
	ASSERT_EQ(date.GetMonth(), Month::MARCH);
	ASSERT_EQ(date.GetYear(), 2025);
	ASSERT_TRUE(date.IsValid());

	CDate date2(28, Month::OCTOBER, 9999);
	ASSERT_TRUE(date2.IsValid());
}

TEST(Date, TestInvalidDate)
{
	CDate date1(31, Month::FEBRUARY, 2023);
	ASSERT_FALSE(date1.IsValid());

	CDate date2(10, Month::OCTOBER, 10000);
	ASSERT_FALSE(date2.IsValid());

	CDate date4(28, Month::OCTOBER, 1969);
	ASSERT_FALSE(date4.IsValid());
}

TEST(Date, TestIncrementOperator)
{
	CDate date(28, Month::FEBRUARY, 2020);
	++date;
	ASSERT_EQ(date.GetDay(), 29);
	ASSERT_EQ(date.GetMonth(), Month::FEBRUARY);
	ASSERT_EQ(date.GetYear(), 2020);
}

TEST(Date, TestDecrementOperator)
{
	CDate date(1, Month::MARCH, 2023);
	--date;
	ASSERT_EQ(date.GetDay(), 28);
	ASSERT_EQ(date.GetMonth(), Month::FEBRUARY);
	ASSERT_EQ(date.GetYear(), 2023);
}

TEST(Date, TestAdditionOperator)
{
	CDate date(28, Month::FEBRUARY, 2020);
	CDate newDate = date + 2;
	ASSERT_EQ(newDate.GetDay(), 1);
	ASSERT_EQ(newDate.GetMonth(), Month::MARCH);
	ASSERT_EQ(newDate.GetYear(), 2020);

	newDate += 2;
	ASSERT_EQ(newDate.GetDay(), 3);
	newDate -= 3;
	ASSERT_EQ(newDate.GetDay(), 29);
	ASSERT_EQ(newDate.GetMonth(), Month::FEBRUARY);
}

TEST(Date, TestSubtractionOperator)
{
	CDate date(1, Month::MARCH, 2023);
	CDate newDate = date - 2;
	ASSERT_EQ(newDate.GetDay(), 27);
	ASSERT_EQ(newDate.GetMonth(), Month::FEBRUARY);
	ASSERT_EQ(newDate.GetYear(), 2023);
}

TEST(Date, TestDifferenceBetweenDates)
{
	CDate date1(1, Month::MARCH, 2023);
	CDate date2(28, Month::FEBRUARY, 2023);
	ASSERT_EQ(date1 - date2, 1);
}

TEST(Date, TestInputOutputOperator)
{
	CDate date;
	std::istringstream input("15.03.2023");
	input >> date;
	ASSERT_EQ(date.GetDay(), 15);
	ASSERT_EQ(date.GetMonth(), Month::MARCH);
	ASSERT_EQ(date.GetYear(), 2023);

	std::ostringstream output;
	output << date;
	ASSERT_EQ(output.str(), "15.03.2023");
}

TEST(Date, TestDatesComparing)
{
	CDate date1(12, Month::MARCH, 2025);
	ASSERT_FALSE(date1 < date1);
	ASSERT_FALSE(date1 > date1);
	ASSERT_TRUE(date1 == date1);

	CDate date2(12, Month::APRIL, 2025);
	ASSERT_TRUE(date2 > date1);
	ASSERT_TRUE(date2 >= date1);

	CDate date3(11, Month::MARCH, 2025);
	ASSERT_TRUE(date3 < date1);
	ASSERT_TRUE(date3 <= date1);

	CDate date4(12, Month::MARCH, 2025);
	ASSERT_TRUE(date1 == date4);
	ASSERT_FALSE(date1 < date4);
	ASSERT_FALSE(date1 > date4);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}