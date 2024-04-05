#include "DictionaryModule.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

std::string FindWord(const std::string& word, const Dictionary& dict)
{
	auto it = dict.find(word);
	if (it != dict.end())
	{
		return it->first;
	}
	else
	{
		return "";
	}
}

bool IsWordRussian(const std::string& word)
{
	for (const char ch : word)
	{
		bool isÑharsCorrect = (ch >= 'à') && (ch <= 'ÿ') || (ch == '¸');
		if (!isÑharsCorrect)
		{
			return false;
		}
	}
	return true;
}

void HandleSaving(const std::string& word, Dictionary& dict)
{
	std::cout << "Íåèçâåñòíîå ñëîâî '" << word << "'. Ââåäèòå ïåðåâîä èëè ïóñòóþ ñòðîêó äëÿ îòêàçà." << std::endl;

	std::string englishTranslation;
	std::getline(std::cin, englishTranslation);
	if (englishTranslation != "")
	{
		dict.insert({ word, englishTranslation });
	}
}

void TransformToLowerCase(std::string& word)
{
	std::transform(word.begin(), word.end(), word.begin(), [](unsigned char ch) {
		return std::tolower(ch);
	});
}

void HandleWord(const std::string& word, Dictionary& dict)
{
	std::string lowerWord = word;
	TransformToLowerCase(lowerWord);	

	if (FindWord(word, dict) == "")
	{
		HandleSaving(word, dict);
	}
	else
	{
		std::string russianTranslation = dict.find(lowerWord)->second;
		std::cout << russianTranslation << std::endl;
	}
}

void LoadDict(const std::string& dictFileName, Dictionary& dict)
{
	std::ifstream dictFile;
	dictFile.open(dictFileName);
	if (!dictFile.is_open())
	{
		throw std::runtime_error("Failed to open " + dictFileName + " for reading");
	}
	std::string word, translation;
	while (std::getline(dictFile, word) && std::getline(dictFile, translation))
	{
		dict.insert({ word, translation });
	}
	if (!dictFile.eof())
	{
		throw std::runtime_error("Failed to read line from " + dictFileName);
	}
}

void SaveDict(const std::string& dictFileName, const Dictionary& dict)
{
	std::ofstream dictFile;
	dictFile.open(dictFileName, std::ios_base::app);
	if (!dictFile.is_open())
	{
		throw std::runtime_error("Failed to open " + dictFileName + " for writing");
	}
	for (auto& item : dict)
	{
		dictFile << item.first << std::endl;
		dictFile << item.second << std::endl;
	}
	if (!dictFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}

void WorkWithDictionary(Dictionary& dict)
{
	std::string word;
	std::cout << ">";
	while (std::getline(std::cin, word))
	{
		if (word == "...")
		{
			break;
		}
		HandleWord(word, dict);
		std::cout << ">";
	}
}