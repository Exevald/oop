#pragma once

#include "CStringBaseIterator.h"
#include "CStringConstIterator.h"

class CString;

class CStringIterator : public CStringBaseIterator<char, CString>
{
public:
	using base_type = CStringBaseIterator;

	CStringIterator(char* pChar, CString* stringData)
		: base_type(pChar, stringData)
	{
	}

	explicit CStringIterator(const CStringConstIterator& constIter)
		: base_type(const_cast<char*>(constIter.GetPtr()), constIter.GetStringData())
	{
	}
};
