#include "CHttpURL.h"
#include "CURLParsingError.h"
#include <gtest/gtest.h>

TEST(HttpURL, TestValidUrl)
{
	CHttpURL url("https://example.com:8080/path/to/resource");
	ASSERT_EQ(url.GetURL(), "https://example.com:8080/path/to/resource");
	ASSERT_EQ(url.GetDomain(), "example.com");
	ASSERT_EQ(url.GetDocument(), "/path/to/resource");
	ASSERT_EQ(url.GetProtocol(), Protocol::HTTPS);
	ASSERT_EQ(url.GetPort(), 8080);

	CHttpURL url2("hTTps://example.com:8080/path/to/resource");
	ASSERT_EQ(url.GetProtocol(), Protocol::HTTPS);
}

TEST(HttpURL, TestCreateUrlWithPort)
{
	CHttpURL url("example.com", "/index.html", Protocol::HTTP, 1);
	ASSERT_EQ(url.GetURL(), "http://example.com:1/index.html");
	ASSERT_EQ(url.GetDomain(), "example.com");
	ASSERT_EQ(url.GetDocument(), "/index.html");
	ASSERT_EQ(url.GetProtocol(), Protocol::HTTP);
	ASSERT_EQ(url.GetPort(), 1);

	CHttpURL url2("example.com", "/index.html", Protocol::HTTP, 65535);
	ASSERT_EQ(url2.GetPort(), 65535);
}

TEST(HttpURL, TestDocumentStartsWithSlash)
{
	CHttpURL url("example.com", "path/to/resource", Protocol::HTTP);
	ASSERT_EQ(url.GetDocument(), "/path/to/resource");

	CHttpURL url2("example.com", "/path/to/resource", Protocol::HTTP);
	ASSERT_EQ(url2.GetDocument(), "/path/to/resource");

	CHttpURL url3("example.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP);
	ASSERT_EQ(url3.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
}

TEST(HttpURL, TestEmptyDocument)
{
	CHttpURL url("example.com", "", Protocol::HTTP);
	ASSERT_EQ(url.GetDocument(), "/");
}

TEST(HttpURL, TestInvalidUrlParams)
{
	ASSERT_THROW(CHttpURL("bimbimbambam://example.com"), CURLParsingError);
	ASSERT_THROW(CHttpURL("http://example.com:100000000"), CURLParsingError);
	ASSERT_THROW(CHttpURL("http://example.com:0"), CURLParsingError);
	ASSERT_THROW(CHttpURL("", "", Protocol::HTTP), std::invalid_argument);
}
