#include "HTMLDecoder.h"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::string HtmlDecode(const std::string& htmlString)
{
	std::unordered_map<std::string, char> htmlEntities = {
		{ "&quot;", '"' },
		{ "&apos;", '\'' },
		{ "&lt;", '<' },
		{ "&gt;", '>' },
		{ "&amp;", '&' }
	};
	std::string decodedString = "";
	for (size_t i = 0; i < htmlString.length(); i++)
	{
		if (htmlString[i] == '&')
		{
			size_t semicolonPos = htmlString.find(';', i);
			if (semicolonPos != std::string::npos)
			{
				std::string entity = htmlString.substr(i, semicolonPos - i + 1);
				if (htmlEntities[entity])
				{
					decodedString += htmlEntities[entity];
					i = semicolonPos;
					continue;
				}
			}
		}
		decodedString += htmlString[i];
	}

	return decodedString;
}