#include "HTMLDecoder.h"

#include <iostream>
#include <string>

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::string decodedLine = HtmlDecode(line);
		std::cout << decodedLine << std::endl;
	}
	if (!std::cin.eof())
	{
		std::cout << "Failed to read line from input stream" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}