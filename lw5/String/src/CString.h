#pragma once

#include "CStringConstIterator.h"
#include "CStringIterator.h"
#include <cstring>
#include <string>

class CString
{
public:
	using iterator = CStringIterator;
	using const_iterator = CStringConstIterator;

	CString();
	explicit CString(const char* pString);
	CString(const char* pString, size_t length);
	CString(CString const& other);
	CString(CString&& other) noexcept;
	explicit CString(std::string const& stlString);

	~CString();

	[[nodiscard]] size_t GetLength() const;
	[[nodiscard]] size_t GetCapacity() const;
	[[nodiscard]] const char* GetStringData() const;
	[[nodiscard]] CString SubString(size_t start, size_t length = SIZE_MAX) const;

	CString& operator=(const CString& other);
	CString& operator=(CString&& other) noexcept;

	CString operator+(const CString& other) const;
	CString operator+(const std::string& other) const;
	CString operator+(const char* other) const;

	CString operator+=(const CString& other);

	bool operator==(const CString& other) const;
	bool operator!=(const CString& other) const;
	bool operator<(const CString& other) const;
	bool operator>(const CString& other) const;
	bool operator<=(const CString& other) const;
	bool operator>=(const CString& other) const;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	friend std::ostream& operator<<(std::ostream& stream, const CString& str);
	friend std::istream& operator>>(std::istream& stream, CString& string);

	void Clear();

	iterator begin() { return { m_data, this }; }
	iterator end() { return { m_data + m_length, this }; }

	[[nodiscard]] const_iterator begin() const { return { m_data, this }; }
	[[nodiscard]] const_iterator end() const { return { m_data + m_length, this }; }

	[[nodiscard]] const_iterator cbegin() const { return { m_data, this }; }
	[[nodiscard]] const_iterator cend() const { return { m_data + m_length, this }; }

private:
	CString(size_t length, size_t capacity, const char* data);

	char* m_data;
	size_t m_length;
	size_t m_capacity;
};
