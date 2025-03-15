#include "CDate.h"
#include <limits>

namespace
{
bool IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned GetDaysInMonth(Month month, unsigned year)
{
	switch (month)
	{
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	default:
		return 31;
	}
}

void ConvertTimestampToDate(unsigned& day, Month& month, unsigned& year, unsigned timestamp)
{
	unsigned remainingDays = timestamp;
	year = 1970;

	while (true)
	{
		unsigned daysInYear = IsLeapYear(year) ? 366 : 365;
		if (remainingDays < daysInYear)
		{
			break;
		}
		remainingDays -= daysInYear;
		++year;
	}

	month = Month::JANUARY;
	while (true)
	{
		unsigned daysInCurrentMonth = GetDaysInMonth(month, year);
		if (remainingDays < daysInCurrentMonth)
		{
			break;
		}
		remainingDays -= daysInCurrentMonth;
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
	}

	day = remainingDays + 1;
}

unsigned ConvertDateToTimestamp(unsigned day, Month month, unsigned year)
{
	if (year < 1970 || year > 9999 || month < Month::JANUARY || month > Month::DECEMBER || day < 1 || day > GetDaysInMonth(month, year))
	{
		return -1;
	}

	unsigned totalDays = 0;
	for (unsigned y = 1970; y < year; ++y)
	{
		totalDays += IsLeapYear(y) ? 366 : 365;
	}

	for (unsigned m = 1; m < static_cast<unsigned>(month); ++m)
	{
		totalDays += GetDaysInMonth(static_cast<Month>(m), year);
	}

	totalDays += day - 1;
	return totalDays;
}
} // namespace

CDate::CDate(unsigned day, Month month, unsigned year)
{
	unsigned timestamp = ConvertDateToTimestamp(day, month, year);
	if (timestamp == static_cast<unsigned>(-1))
	{
		m_timestamp = std::numeric_limits<unsigned>::max();
	}
	else
	{
		m_timestamp = timestamp;
	}
}

CDate::CDate(unsigned timestamp)
	: m_timestamp(timestamp)
{
	if (!IsValid())
	{
		m_timestamp = 0;
	}
}

CDate::CDate()
{
	m_timestamp = 0;
}

CDate& CDate::operator++()
{
	if (IsValid())
	{
		++m_timestamp;
	}
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	++(*this);
	return temp;
}

CDate& CDate::operator--()
{
	if (IsValid())
	{
		--m_timestamp;
	}
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp = *this;
	--(*this);
	return temp;
}

CDate CDate::operator+(int days) const
{
	return CDate(m_timestamp + days);
}

CDate CDate::operator-(int days) const
{
	return CDate(m_timestamp - days);
}

int CDate::operator-(const CDate& other) const
{
	return static_cast<int>(m_timestamp) - static_cast<int>(other.m_timestamp);
}

CDate& CDate::operator+=(int days)
{
	if (IsValid())
	{
		m_timestamp += days;
	}
	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (IsValid() && m_timestamp >= days)
	{
		m_timestamp -= days;
	}
	else
	{
		m_timestamp = 0;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const CDate& date)
{
	if (date.IsValid())
	{
		unsigned day = date.GetDay();
		Month month = date.GetMonth();
		unsigned year = date.GetYear();
		stream << (day < 10 ? "0" : "") << day << "."
			   << (static_cast<unsigned>(month) < 10 ? "0" : "") << static_cast<unsigned>(month) << "."
			   << year;
	}
	else
	{
		stream << "INVALID DATE";
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, CDate& date)
{
	unsigned day, year;
	unsigned month;
	char sep1, sep2;
	stream >> day >> sep1 >> month >> sep2 >> year;
	if (sep1 == '.' && sep2 == '.')
	{
		date.m_timestamp = ConvertDateToTimestamp(day, static_cast<Month>(month), year);
	}
	else
	{
		date.m_timestamp = 0;
	}
	return stream;
}

bool CDate::operator==(const CDate& date) const
{
	return m_timestamp == date.m_timestamp;
}

bool CDate::operator!=(const CDate& date) const
{
	return !(*this == date);
}

bool CDate::operator>(const CDate& date) const
{
	return m_timestamp > date.m_timestamp;
}

bool CDate::operator<(const CDate& date) const
{
	return m_timestamp < date.m_timestamp;
}

bool CDate::operator>=(const CDate& date) const
{
	return !(*this < date);
}

bool CDate::operator<=(const CDate& date) const
{
	return !(*this > date);
}

unsigned CDate::GetDay() const
{
	unsigned day, year;
	Month month;
	ConvertTimestampToDate(day, month, year, m_timestamp);
	return day;
}

Month CDate::GetMonth() const
{
	unsigned day, year;
	Month month;
	ConvertTimestampToDate(day, month, year, m_timestamp);
	return month;
}

unsigned CDate::GetYear() const
{
	unsigned day, year;
	Month month;
	ConvertTimestampToDate(day, month, year, m_timestamp);
	return year;
}

WeekDay CDate::GetWeekDay() const
{
	if (!IsValid())
	{
		return WeekDay::SUNDAY;
	}
	return static_cast<WeekDay>((m_timestamp + 4) % 7);
}

bool CDate::IsValid() const
{
	unsigned day, year;
	Month month;
	ConvertTimestampToDate(day, month, year, m_timestamp);

	return year >= 1970 && year <= 9999 && month >= Month::JANUARY && month <= Month::DECEMBER && day >= 1 && day <= GetDaysInMonth(month, year);
}