#pragma once

#include <stdexcept>

class CURLParsingError : public std::invalid_argument
{
public:
	explicit CURLParsingError(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};
