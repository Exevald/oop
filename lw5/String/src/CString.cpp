#include "CString.h"
#include <iostream>
#include <stdexcept>

namespace
{
char* AllocateMemory(size_t size)
{
	return new char[size]();
}

void ReleaseBufferMemory(const char* buffer)
{
	delete[] buffer;
}

} // namespace

CString::CString()
	: m_length(0)
	, m_capacity(1)
	, m_data(AllocateMemory(1))

{
	m_data[0] = '\0';
}

CString::CString(const char* pString)
	: CString(pString, std::strlen(pString))
{
}

CString::CString(const char* pString, size_t length)
	: m_length(length)
	, m_capacity(length + 1)
	, m_data(AllocateMemory(length + 1))
{
	std::memcpy(m_data, pString, m_length);
	m_data[m_length] = '\0';
}

CString::CString(const CString& other)
	: m_length(other.m_length)
	, m_capacity(other.m_capacity)
{
	if (other.m_data)
	{
		m_data = new char[m_capacity];
		std::memcpy(m_data, other.m_data, m_length);
		m_data[m_length] = '\0';
	}
	else
	{
		m_data = nullptr;
	}
}

CString::CString(CString&& other) noexcept
	: m_data(other.m_data)
	, m_length(other.m_length)
	, m_capacity(other.m_capacity)
{
	other.m_data = nullptr;
	other.m_length = 0;
	other.m_capacity = 0;
}

CString::CString(const std::string& stlString)
	: CString(stlString.c_str(), stlString.length())
{
}

CString::~CString()
{
	ReleaseBufferMemory(m_data);
}

size_t CString::GetLength() const
{
	return m_length;
}

const char* CString::GetStringData() const
{
	return m_data;
}

CString CString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("Start index of substring can't be greater than string length");
	}

	size_t actualLength = std::min(length, m_length - start);
	return { m_data + start, actualLength };
}

CString& CString::operator=(const CString& other)
{
	if (this != &other)
	{
		CString temp(other);
		std::swap(*this, temp);
	}
	return *this;
}

CString& CString::operator=(CString&& other) noexcept
{
	if (this != &other)
	{
		ReleaseBufferMemory(m_data);

		m_data = other.m_data;
		m_length = other.m_length;
		m_capacity = other.m_capacity;

		other.m_data = nullptr;
		other.m_length = 0;
		other.m_capacity = 0;
	}
	return *this;
}

CString CString::operator+(const CString& other) const
{
	CString result;
	result.m_length = m_length + other.m_length;
	result.m_capacity = result.m_length + 1;
	result.m_data = AllocateMemory(result.m_capacity);

	std::memcpy(result.m_data, m_data, m_length);
	std::memcpy(result.m_data + m_length, other.m_data, other.m_length);
	result.m_data[result.m_length] = '\0';
	return result;
}

CString CString::operator+(const std::string& other) const
{
	return *this + CString(other);
}

CString CString::operator+(const char* other) const
{
	return *this + CString(other);
}

CString CString::operator+=(const CString& other)
{
	size_t newLength = m_length + other.m_length;
	if (newLength + 1 > m_capacity)
	{
		m_capacity = std::max(m_capacity * 2, newLength + 1);
		auto newData = AllocateMemory(m_capacity);

		std::memcpy(newData, m_data, m_length);
		ReleaseBufferMemory(m_data);
		m_data = newData;
	}

	std::memcpy(m_data + m_length, other.m_data, other.m_length);
	m_length = newLength;
	m_data[m_length] = '\0';
	return *this;
}

bool CString::operator==(const CString& other) const
{
	return m_length == other.m_length && std::equal(m_data, m_data + m_length, other.m_data);
}

bool CString::operator!=(const CString& other) const
{
	return !(*this == other);
}

bool CString::operator<(const CString& other) const
{
	return std::lexicographical_compare(m_data, m_data + m_length, other.m_data, other.m_data + other.m_length);
}

bool CString::operator>(const CString& other) const
{
	return other < *this;
}

bool CString::operator<=(const CString& other) const
{
	return !(*this > other);
}

bool CString::operator>=(const CString& other) const
{
	return !(*this < other);
}

const char& CString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

char& CString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

std::ostream& operator<<(std::ostream& stream, const CString& string)
{
	stream << string.GetStringData();
	return stream;
}

std::istream& operator>>(std::istream& stream, CString& string)
{
	std::string temp;
	stream >> temp;
	string = CString(temp);
	return stream;
}

void CString::Clear()
{
	ReleaseBufferMemory(m_data);
	m_data = AllocateMemory(1);
	m_data[0] = '\0';
	m_length = 0;
	m_capacity = 1;
}

size_t CString::GetCapacity() const
{
	return m_capacity;
}