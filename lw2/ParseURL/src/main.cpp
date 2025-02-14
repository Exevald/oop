#include "URLParser.h"
#include <iostream>

int main()
{
	std::string url;
	std::string host;
	std::string document;
	Protocol protocol;
	int port;

	while (std::getline(std::cin, url))
	{
		auto isParsingComplete = ParseURL(url, protocol, port, host, document);
		if (isParsingComplete)
		{
			PrintParsedURLInfo(url, port, host, document);
		}
		else
		{
			std::cout << "Failed to parse URL. Please, try again" << std::endl;
		}
	}
	if (!std::cin.eof())
	{
		std::cout << "Failed to read line from input stream" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}