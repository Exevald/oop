#pragma once

#include <string>

enum class Protocol

{
	HTTP,
	HTTPS
};

class CHttpURL
{
public:
	explicit CHttpURL(std::string const& url);
	CHttpURL(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);
	CHttpURL(
		const std::string& domain,
		const std::string& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	[[nodiscard]] std::string FormURL() const;

	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};