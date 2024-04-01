#include "HTMLDecoder.h"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

const std::unordered_map<std::string, char> HtmlEntities = {
	{ "&quot;", '"' },
	{ "&apos;", '\'' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' }
};

std::string HtmlDecode(const std::string& htmlString)
{
	std::string decodedString;
	for (size_t i = 0; i < htmlString.length();)
	{
		if (htmlString[i] == '&')
		{
			std::string entity = htmlString.substr(i);
			entity = entity.substr(0, entity.find(';') + 1);
			auto it = HtmlEntities.find(entity);
			if (it != HtmlEntities.end())
			{
				decodedString += it->second;
				i += entity.size();
				continue;
			}
		}
		decodedString += htmlString[i++];
	}
	return decodedString;
}