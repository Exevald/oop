#include "URLParser.h"
#include <iostream>
#include <regex>

void ParseProtocol(const std::string& protocolString, Protocol& protocol, int& port)
{
	if (protocolString == "http")
	{
		protocol = Protocol::HTTP;
		port = 80;
	}
	else if (protocolString == "https")
	{
		protocol = Protocol::HTTPS;
		port = 443;
	}
	else if (protocolString == "ftp")
	{
		protocol = Protocol::FTP;
		port = 21;
	}
}

int ParsePort(const std::string& portString)
{
	constexpr int maxPortNumber = 65535;
	constexpr int minPortNumber = 1;
	int port;

	if (!portString.empty())
	{
		port = std::stoi(portString);
		if (port < minPortNumber || port > maxPortNumber)
		{
			throw std::out_of_range("Invalid port. Port should be from " + std::to_string(minPortNumber) + " to " + std::to_string(maxPortNumber));
		}
		return port;
	}
	throw std::runtime_error("Empty port string");
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlRegex(R"((http|https|ftp)://([^/:]+)(:(\d+))?(/.*)?)", std::regex_constants::icase);
	std::smatch urlMatch;

	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		return false;
	}

	std::string protocolString = urlMatch[1];
	std::transform(protocolString.begin(), protocolString.end(), protocolString.begin(), ::tolower);

	ParseProtocol(protocolString, protocol, port);
	host = urlMatch[2];

	std::string portString = urlMatch[4];
	if (!portString.empty())
	{
		try
		{
			port = ParsePort(portString);
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return false;
		}
	}

	document = urlMatch[5].length() > 0 ? urlMatch[5].str().substr(1) : "";
	return true;
}

void PrintParsedURLInfo(const std::string& url, int port, const std::string& host,
	const std::string& document)
{
	std::cout << url << std::endl;
	std::cout << "HOST: " << host << std::endl;
	std::cout << "PORT: " << port << std::endl;
	std::cout << "DOC: " << document << std::endl;
}