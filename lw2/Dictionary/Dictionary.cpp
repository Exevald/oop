#include "DictionaryModule.h"

#include <iostream>
#include <string>
#include <windows.h>

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	if (argc != 2)
	{
		std::cout << "Не задано имя файла словаря" << std::endl
				  << "Пожалуйста, задайте имя файла, как аргумент командной строки" << std::endl;
		return EXIT_FAILURE;
	}
	const std::string dictFileName = argv[1];
	Dictionary dictionary;

	try
	{
		LoadDict(dictFileName, dictionary);
		size_t dictStartSize = dictionary.size();

		WorkWithDictionary(dictionary);

		if (dictionary.size() != dictStartSize)
		{
			std::cout << "В словарь были внесены изменения. Введите 'Y' или 'y' для сохранения перед выходом" << std::endl;
			std::string answer;
			std::getline(std::cin, answer);
			if (answer == "Y" || answer == "y")
			{
				SaveDict(dictFileName, dictionary);
			}
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
