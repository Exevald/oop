#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <stdexcept>

template <typename T>
class CArray
{
public:
	CArray();
	~CArray() noexcept;

	CArray(const CArray& other);
	CArray(CArray&& other) noexcept;

	void Push(const T& item);
	unsigned GetSize() const;

	void Resize(unsigned newSize);
	void Clear() noexcept;

	T& operator[](size_t index);
	T const& operator[](size_t index) const;

	CArray<T>& operator=(const CArray& other);
	CArray<T>& operator=(CArray&& other) noexcept;

	template <typename U>
	CArray<T>& operator=(const CArray<U>& other);

	T* begin() noexcept;
	const T* begin() const noexcept;
	T* end() noexcept;
	const T* end() const noexcept;

	std::reverse_iterator<T*> rbegin() noexcept;
	std::reverse_iterator<const T*> rbegin() const noexcept;
	std::reverse_iterator<T*> rend() noexcept;
	std::reverse_iterator<const T*> rend() const noexcept;

private:
	void AllocateMemory(size_t capacity);
	void Swap(CArray<T>& other) noexcept;

	T* m_data;
	size_t m_size;
	size_t m_capacity;
};

template <typename T>
CArray<T>::CArray()
	: m_capacity(0)
	, m_size(0)
	, m_data(nullptr)
{
}

template <typename T>
CArray<T>::~CArray() noexcept
{
	Clear();
}

template <typename T>
CArray<T>::CArray(const CArray& other)
	: m_size(other.m_size)
	, m_capacity(other.m_capacity)
	, m_data(nullptr)
{
	T* tempData = nullptr;
	if (other.m_data)
	{
		tempData = new T[other.m_size];
		try
		{
			std::copy(other.m_data, other.m_data + other.m_size, tempData);
		}
		catch (...)
		{
			delete[] tempData;
			throw;
		}
	}
	m_data = tempData;
}

template <typename T>
CArray<T>::CArray(CArray&& other) noexcept
	: m_data(other.m_data)
	, m_capacity(other.m_capacity)
	, m_size(other.m_size)
{
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_data = nullptr;
}

template <typename T>
void CArray<T>::Push(const T& item)
{
	if (m_size >= m_capacity)
	{
		AllocateMemory(m_capacity == 0 ? 1 : m_capacity * 2);
	}
	m_data[m_size++] = item;
}

template <typename T>
unsigned CArray<T>::GetSize() const
{
	return m_size;
}

template <typename T>
void CArray<T>::Resize(unsigned newSize)
{
	if (newSize > std::numeric_limits<size_t>::max())
	{
		throw std::overflow_error("Array size overflow");
	}
	if (newSize > m_size)
	{
		AllocateMemory(newSize);
		for (size_t i = m_size; i < newSize; ++i)
		{
			m_data[i] = T();
		}
	}
	m_size = newSize;
}

template <typename T>
void CArray<T>::Clear() noexcept
{
	if (m_data)
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i].~T();
		}
		::operator delete[](m_data);
	}
	m_data = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
T& CArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

template <typename T>
T const& CArray<T>::operator[](size_t index) const
{
	return m_data[index];
}

template <typename T>
CArray<T>& CArray<T>::operator=(const CArray& other)
{
	if (this != &other)
	{
		CArray<T> temp(other);
		Swap(temp);
	}
	return *this;
}

template <typename T>
CArray<T>& CArray<T>::operator=(CArray&& other) noexcept
{
	if (this != &other)
	{
		delete[] m_data;
		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}
	return *this;
}

template <typename T>
template <typename U>
CArray<T>& CArray<T>::operator=(const CArray<U>& other)
{
	CArray<T> temp;
	temp.AllocateMemory(other.GetSize());
	try
	{
		for (unsigned i = 0; i < other.GetSize(); ++i)
		{
			new (&temp.m_data[i]) T(static_cast<T>(other[i]));
		}
		temp.m_size = other.GetSize();
	}
	catch (...)
	{
		temp.Clear();
		throw;
	}
	Swap(temp);
	return *this;
}

template <typename T>
T* CArray<T>::begin() noexcept
{
	return m_data;
}

template <typename T>
const T* CArray<T>::begin() const noexcept
{
	return m_data;
}

template <typename T>
T* CArray<T>::end() noexcept
{
	return m_data + m_size;
}

template <typename T>
const T* CArray<T>::end() const noexcept
{
	return m_data + m_size;
}

template <typename T>
std::reverse_iterator<T*> CArray<T>::rbegin() noexcept
{
	return std::reverse_iterator<T*>(end());
}

template <typename T>
std::reverse_iterator<const T*> CArray<T>::rbegin() const noexcept
{
	return std::reverse_iterator<const T*>(end());
}

template <typename T>
std::reverse_iterator<T*> CArray<T>::rend() noexcept
{
	return std::reverse_iterator<T*>(begin());
}

template <typename T>
std::reverse_iterator<const T*> CArray<T>::rend() const noexcept
{
	return std::reverse_iterator<const T*>(begin());
}

template <typename T>
void CArray<T>::AllocateMemory(size_t capacity)
{
	if (capacity == 0)
	{
		delete[] m_data;
		m_data = nullptr;
		m_capacity = 0;
		return;
	}

	if (capacity > m_capacity)
	{
		T* newData = new T[capacity];
		if (m_data)
		{
			try
			{
				std::copy(m_data, m_data + m_size, newData);
				delete[] m_data;
			}
			catch (...)
			{
				delete[] newData;
				throw;
			}
		}
		m_data = newData;
		m_capacity = capacity;
	}
}

template <typename T>
void CArray<T>::Swap(CArray<T>& other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}