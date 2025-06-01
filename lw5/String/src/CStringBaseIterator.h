#pragma once

#include <cassert>
#include <compare>
#include <cstddef>
#include <iterator>

class CString;

template <typename ElementType, typename ContainerType>
class CStringBaseIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = ElementType;
	using difference_type = std::ptrdiff_t;
	using pointer = ElementType*;
	using reference = ElementType&;

	CStringBaseIterator(ElementType* pChar, ContainerType* stringData)
		: m_ptr(pChar)
		, m_stringData(stringData)
	{
	}

	reference operator*() const
	{
		assert(m_ptr);
		return *m_ptr;
	}

	CStringBaseIterator& operator++()
	{
		assert(m_stringData != nullptr);
		assert(m_ptr != m_stringData->GetStringData() + m_stringData->GetLength());
		++m_ptr;
		return *this;
	}

	CStringBaseIterator operator++(int)
	{
		CStringBaseIterator retval = *this;
		++(*this);
		return retval;
	}

	CStringBaseIterator& operator--()
	{
		assert(m_stringData != nullptr);
		assert(m_ptr != m_stringData->GetStringData());
		--m_ptr;
		return *this;
	}

	CStringBaseIterator operator--(int)
	{
		CStringBaseIterator retval = *this;
		--(*this);
		return retval;
	}

	CStringBaseIterator& operator+=(difference_type offset)
	{
		VerifyOffset(offset);
		m_ptr += offset;
		return *this;
	}

	[[nodiscard]] CStringBaseIterator operator+(difference_type offset) const noexcept
	{
		CStringBaseIterator tmp = *this;
		tmp += offset;
		return tmp;
	}

	CStringBaseIterator& operator-=(difference_type offset) noexcept
	{
		return *this += -offset;
	}

	[[nodiscard]] CStringBaseIterator operator-(difference_type offset) const noexcept
	{
		CStringBaseIterator tmp = *this;
		tmp -= offset;
		return tmp;
	}

	[[nodiscard]] difference_type operator-(const CStringBaseIterator& right) const noexcept
	{
		return m_ptr - right.m_ptr;
	}

	[[nodiscard]] reference operator[](difference_type offset) const
	{
		assert(m_stringData != nullptr);
		assert(m_ptr + offset >= m_stringData->GetStringData());
		assert(m_ptr + offset <= m_stringData->GetStringData() + m_stringData->GetLength());
		return *(*this + offset);
	}

	std::strong_ordering operator<=>(const CStringBaseIterator& rhs) const noexcept
	{
		return m_ptr <=> rhs.m_ptr;
	}

	bool operator==(const CStringBaseIterator& rhs) const noexcept
	{
		return m_ptr == rhs.m_ptr;
	}

protected:
	void VerifyOffset(difference_type offset) const
	{
		assert(m_stringData != nullptr);

		const ElementType* begin = m_stringData->GetStringData();
		const ElementType* end = begin + m_stringData->GetLength();

		assert((offset == 0) || ((offset < 0 && m_ptr + offset >= begin) || (offset > 0 && m_ptr + offset <= end)));
	}

	ElementType* GetPtr() const { return m_ptr; }
	ContainerType* GetStringData() const { return m_stringData; }

	ElementType* m_ptr = nullptr;
	ContainerType* m_stringData = nullptr;
};
