#pragma once

#include <iostream>
#include <map>
#include <string>

typedef std::multimap<std::string, std::string> Dictionary;

void LoadDict(const std::string& dictFileName, Dictionary& dict);
void SaveDict(const std::string& dictFileName, const Dictionary& dict);
void HandleSaving(const std::string& word, Dictionary& dict);
void WorkWithDictionary(Dictionary& dict);
bool IsWordRussian(const std::string& word);
std::string FindWord(const std::string& word, const Dictionary& dict);