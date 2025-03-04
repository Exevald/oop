#include "../src/URLParser.h"
#include <gtest/gtest.h>

struct TestArgs
{
	std::string url;
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
};

TestArgs PrepareTestArgs(const std::string& url)
{
	Protocol protocol = Protocol::HTTPS;
	int port = 0;
	std::string host;
	std::string document;
	return TestArgs{ url, protocol, port, host, document };
}

TEST(ParsingUrl, ParseDefaultUrl)
{
	TestArgs args = PrepareTestArgs("https://www.mysite.com/docs/document1.html?page=30&lang=en#title");

	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, true);
	ASSERT_EQ(args.protocol, Protocol::HTTPS);
	ASSERT_EQ(args.port, 443);
	ASSERT_EQ(args.host, "www.mysite.com");
	ASSERT_EQ(args.document, "docs/document1.html?page=30&lang=en#title");
}

TEST(ParsingUrl, ParseDefaultUrlWithPort)
{
	TestArgs args = PrepareTestArgs("https://www.google.com:123/docs/document1.html?page=30&lang=en#title");

	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, true);
	ASSERT_EQ(args.protocol, Protocol::HTTPS);
	ASSERT_EQ(args.port, 123);
	ASSERT_EQ(args.host, "www.google.com");
	ASSERT_EQ(args.document, "docs/document1.html?page=30&lang=en#title");
}

TEST(ParsingUrl, ParseDefaultUrlWithWrongPort)
{
	TestArgs args = PrepareTestArgs("https://www.google.com:9999999/docs/document1.html?page=30&lang=en#title");

	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, false);
}

TEST(ParsingUrl, ParseDefaultUrlWithWrongPortWithLetters)
{
	TestArgs args = PrepareTestArgs("https://www.google.com:aaa/docs/document1.html?page=30&lang=en#title");

	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, false);
}

TEST(ParsingUrl, ParseDefaultUrlWithEmptyHost)
{
	TestArgs args = PrepareTestArgs("https://:123/docs/document1.html?page=30&lang=en#title");

	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, false);
}

TEST(ParsingUrl, ParseUrlWithDifferentUpperCaseInProtocol)
{
	TestArgs args = PrepareTestArgs("htTp://example.com:8080/index.html");

	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, true);
	ASSERT_EQ(args.protocol, Protocol::HTTP);
	ASSERT_EQ(args.port, 8080);
	ASSERT_EQ(args.host, "example.com");
	ASSERT_EQ(args.document, "index.html");
}

TEST(ParsingUrl, ParseEmptyUrl)
{
	TestArgs args = PrepareTestArgs("");
	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, false);
}

TEST(ParsingUrl, ParseUrlWithEmptyDocument)
{
	TestArgs args = PrepareTestArgs("https://example.com:8080");

	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, true);
	ASSERT_EQ(args.protocol, Protocol::HTTPS);
	ASSERT_EQ(args.port, 8080);
	ASSERT_EQ(args.host, "example.com");
}

TEST(ParsingUrl, ParseUrlWithInvalidProtocol)
{
	TestArgs args = PrepareTestArgs("bimbimbambam://example.com:8080");
	auto isParsingComplete = ParseURL(args.url, args.protocol, args.port, args.host, args.document);
	ASSERT_EQ(isParsingComplete, false);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}