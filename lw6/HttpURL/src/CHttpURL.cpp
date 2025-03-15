#include "CHttpURL.h"

#include "CURLParsingError.h"
#include <regex>

namespace
{
constexpr int maxPortNumber = 65535;
constexpr int minPortNumber = 1;
constexpr int httpPort = 80;
constexpr int httpsPort = 443;

void ParseProtocol(const std::string& protocolString, Protocol& protocol, int& port)
{
	if (protocolString == "http")
	{
		protocol = Protocol::HTTP;
		port = httpPort;
	}
	else if (protocolString == "https")
	{
		protocol = Protocol::HTTPS;
		port = httpsPort;
	}
}

int ParsePort(const std::string& portString)
{
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
	throw std::invalid_argument("Empty port string");
}

void ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& domain, std::string& document)
{
	std::regex urlRegex(R"((http|https|ftp)://([^/:]+)(:(\d+))?(/.*)?)", std::regex_constants::icase);
	std::smatch urlMatch;

	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		throw CURLParsingError("URL doesn't match with pattern");
	}

	std::string protocolString = urlMatch[1];
	std::transform(protocolString.begin(), protocolString.end(), protocolString.begin(), ::tolower);

	ParseProtocol(protocolString, protocol, port);
	domain = urlMatch[2];

	std::string portString = urlMatch[4];
	if (!portString.empty())
	{
		try
		{
			port = ParsePort(portString);
		}
		catch (const std::exception& exception)
		{
			throw CURLParsingError(exception.what());
		}
	}

	document = urlMatch[5].length() > 0 ? urlMatch[5].str().substr(1) : "";
}

std::string FinalizeDocument(const std::string& document)
{
	std::string finalizedDocument = document;
	if (finalizedDocument.empty() || finalizedDocument[0] != '/')
	{
		finalizedDocument = "/" + finalizedDocument;
	}

	return finalizedDocument;
}
} // namespace

CHttpURL::CHttpURL(const std::string& url)
{
	Protocol protocol;
	int port;
	std::string domain;
	std::string document;

	ParseURL(url, protocol, port, domain, document);

	m_protocol = protocol;
	m_domain = domain;
	m_port = static_cast<unsigned short>(port);
	m_document = FinalizeDocument(document);
	m_url = FormURL();
}

CHttpURL::CHttpURL(const std::string& domain, const std::string& document, Protocol protocol)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}

	m_protocol = protocol;
	m_domain = domain;
	m_port = (protocol == Protocol::HTTP) ? httpPort : httpsPort;
	m_document = FinalizeDocument(document);
	m_url = FormURL();
}

CHttpURL::CHttpURL(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}

	if (port < minPortNumber || port > maxPortNumber)
	{
		throw std::out_of_range("Invalid port. Port should be from " + std::to_string(minPortNumber) + " to " + std::to_string(maxPortNumber));
	}

	m_protocol = protocol;
	m_domain = domain;
	m_port = port;
	m_document = FinalizeDocument(document);
	m_url = FormURL();
}

std::string CHttpURL::GetURL() const
{
	return m_url;
}

std::string CHttpURL::GetDomain() const
{
	return m_domain;
}

std::string CHttpURL::GetDocument() const
{
	return m_document;
}

Protocol CHttpURL::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpURL::GetPort() const
{
	return m_port;
}

std::string CHttpURL::FormURL() const
{
	std::string url;

	url += (m_protocol == Protocol::HTTP) ? "http://" : "https://";
	url += m_domain;

	if ((m_protocol == Protocol::HTTP && m_port != httpPort) || (m_protocol == Protocol::HTTPS && m_port != httpsPort))
	{
		url += ":" + std::to_string(m_port);
	}

	url += m_document;

	return url;
}
