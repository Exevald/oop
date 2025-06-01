#pragma once

#include "CStringBaseIterator.h"

class CString;

class CStringConstIterator : public CStringBaseIterator<const char, CString>
{
public:
	using base_type = CStringBaseIterator;

	CStringConstIterator(const char* pChar, const CString* stringData)
		: base_type(const_cast<char*>(pChar), const_cast<CString*>(stringData))
	{
	}

	friend class CStringIterator;
};
