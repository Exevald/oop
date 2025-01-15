#include "URLParser.h"
#include <iostream>
#include <regex>

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex url_regex(R"((http|https|ftp)://([^/:]+)(:(\d+))?(/.*)?)", std::regex_constants::icase);
	std::smatch url_match;

	if (std::regex_match(url, url_match, url_regex))
	{
		std::string proto = url_match[1];
		if (proto == "http")
		{
			protocol = Protocol::HTTP;
			port = 80;
		}
		else if (proto == "https")
		{
			protocol = Protocol::HTTPS;
			port = 443;
		}
		else if (proto == "ftp")
		{
			protocol = Protocol::FTP;
			port = 21;
		}
		host = url_match[2];

		if (url_match[4].length() > 0)
		{
			try
			{
				port = std::stoi(url_match[4]);
				if (port < 1 || port > 65535)
				{
					throw std::out_of_range("Invalid port. Port should be [1..65535]");
				}
			}
			catch (const std::exception& exception)
			{
				std::cout << exception.what() << std::endl;
				return false;
			}
		}
		document = url_match[5].length() > 0 ? url_match[5].str().substr(1) : "";
		return true;
	}

	return false;
}

void PrintParsedURLInfo(const std::string& url, const Protocol& protocol, int& port, const std::string& host,
	const std::string& document)
{
	std::cout << url << std::endl;
	std::cout << "HOST: " << host << std::endl;
	std::cout << "PORT: " << port << std::endl;
	std::cout << "DOC: " << document << std::endl;
}