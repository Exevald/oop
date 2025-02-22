#include "TemplateExpander.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
struct BohrVertex
{
	std::unordered_map<char, size_t> next;
	size_t parentVertexIndex = std::string::npos;
	size_t suffixLinkVertex = std::string::npos;
	size_t suffixGoodLinkVertex = std::string::npos;
	std::unordered_map<char, size_t> autoMove;
	char symbol{};
	bool isLeaf = false;
	std::string fullString;
};

typedef std::vector<BohrVertex> Bohr;

void AddStringToBohr(Bohr& bohr, const std::string& stringToAdd);
size_t GetSuffixLink(Bohr& bohr, size_t vertexPos);
size_t GetAutoMove(Bohr& bohr, size_t vertexPos, char symbol);
bool CheckIfFound(Bohr& bohr, size_t vertexPos);
void AddParamsInBohr(Bohr& bohr, const TemplateParams& params);
size_t ReadUntilIsParam(Bohr& bohr, size_t currentVertexPos, const std::string& tpl, std::string::const_iterator& it);
std::string GetStringToAdd(
	const TemplateParams& params,
	const std::string& foundString,
	std::string::const_iterator lastCopiedPos,
	std::string::const_iterator currentPosition);

void AddStringToBohr(Bohr& bohr, const std::string& stringToAdd)
{
	size_t currentVertexPos = 0;
	for (char symbol : stringToAdd)
	{
		if (!bohr[currentVertexPos].next.count(symbol))
		{
			BohrVertex newVertex;
			newVertex.parentVertexIndex = currentVertexPos;
			newVertex.symbol = symbol;
			bohr[currentVertexPos].next[symbol] = bohr.size();
			bohr.push_back(newVertex);
		}
		currentVertexPos = bohr[currentVertexPos].next[symbol];
	}
	bohr[currentVertexPos].fullString = stringToAdd;
	bohr[currentVertexPos].isLeaf = true;
}

size_t GetSuffixLink(Bohr& bohr, size_t vertexPos)
{
	if (bohr[vertexPos].suffixLinkVertex == std::string::npos)
	{
		if (vertexPos == 0 || bohr[vertexPos].parentVertexIndex == 0)
		{
			bohr[vertexPos].suffixLinkVertex = 0;
		}
		else
		{
			bohr[vertexPos].suffixLinkVertex = GetAutoMove(bohr, GetSuffixLink(bohr, bohr[vertexPos].parentVertexIndex), bohr[vertexPos].symbol);
		}
	}
	return bohr[vertexPos].suffixLinkVertex;
}

size_t GetSuffixGoodLink(Bohr& bohr, size_t vertexPos)
{
	if (bohr[vertexPos].suffixGoodLinkVertex == std::string::npos)
	{
		size_t vertexOnSuffixLink = GetSuffixLink(bohr, vertexPos);
		if (vertexOnSuffixLink == 0)
		{
			bohr[vertexPos].suffixGoodLinkVertex = 0;
		}
		else
		{
			bohr[vertexPos].suffixGoodLinkVertex = (bohr[vertexOnSuffixLink].isLeaf)
				? vertexOnSuffixLink
				: GetSuffixGoodLink(bohr, vertexOnSuffixLink);
		}
	}
	return bohr[vertexPos].suffixGoodLinkVertex;
}

size_t GetAutoMove(Bohr& bohr, size_t vertexPos, char symbol)
{
	if (!bohr[vertexPos].autoMove.count(symbol))
	{
		if (bohr[vertexPos].next.count(symbol))
		{
			bohr[vertexPos].autoMove[symbol] = bohr[vertexPos].next[symbol];
		}
		else
		{
			bohr[vertexPos].autoMove[symbol] = (vertexPos == 0)
				? 0
				: GetAutoMove(bohr, GetSuffixLink(bohr, vertexPos), symbol);
		}
	}
	return bohr[vertexPos].autoMove[symbol];
}

bool CheckIfFound(Bohr& bohr, size_t vertexPos)
{
	for (; vertexPos != 0; vertexPos = GetSuffixGoodLink(bohr, vertexPos))
	{
		if (bohr[vertexPos].isLeaf)
		{
			return true;
		}
	}
	return false;
}

void AddParamsInBohr(Bohr& bohr, const TemplateParams& params)
{
	for (const auto& param : params)
	{
		AddStringToBohr(bohr, param.first);
	}
}

size_t ReadUntilIsParam(Bohr& bohr, size_t currentVertexPos, const std::string& tpl, std::string::const_iterator& it)
{
	size_t newVertexPos = currentVertexPos;

	while (true)
	{
		currentVertexPos = newVertexPos;
		newVertexPos = GetAutoMove(bohr, newVertexPos, *(++it));

		if (it + 1 == tpl.end() || bohr[newVertexPos].parentVertexIndex != currentVertexPos || !CheckIfFound(bohr, currentVertexPos))
		{
			it--;
			break;
		}
	}

	return currentVertexPos;
}

std::string GetStringToAdd(const TemplateParams& params, const std::string& foundString, std::string::const_iterator lastCopiedPos, std::string::const_iterator currentPosition)
{
	size_t uncopiedStringLength = currentPosition - lastCopiedPos - foundString.length() + 1;
	std::string beforeFoundString(lastCopiedPos, lastCopiedPos + long(uncopiedStringLength));

	auto it = params.find(foundString);

	if (it != params.end())
	{
		return beforeFoundString + it->second;
	}

	return beforeFoundString + foundString;
}
} // namespace

std::string ExpandTemplate(const std::string& templateString, const TemplateParams& params)
{
	Bohr bohr{ BohrVertex() };
	std::string resultString;

	AddParamsInBohr(bohr, params);

	size_t vertexPos = 0;
	auto lastCopiedPos = templateString.begin();

	for (auto it = templateString.begin(); it != templateString.end(); ++it)
	{
		vertexPos = GetAutoMove(bohr, vertexPos, *it);

		if (CheckIfFound(bohr, vertexPos))
		{
			vertexPos = ReadUntilIsParam(bohr, vertexPos, templateString, it);
			resultString += GetStringToAdd(params, bohr[vertexPos].fullString, lastCopiedPos, it);
			vertexPos = 0;
			lastCopiedPos = it + 1;
		}
	}

	resultString += std::string(lastCopiedPos, templateString.end());

	return resultString;
}
