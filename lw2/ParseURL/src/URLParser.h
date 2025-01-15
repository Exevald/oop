#pragma once

#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);

void PrintParsedURLInfo(const std::string& url, const Protocol& protocol, int& port, const std::string& host,
		const std::string& document);