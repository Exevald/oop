#include <iostream>
#include <fstream>
#include <string>
#include <optional>

struct Args
{
	std::string firstInputFileName;
	std::string secondInputFileName;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argumants count" << std::endl;
		std::cout << "Usage: Compare.exe <input file1 name> <input file2 name>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.firstInputFileName = argv[1];
	args.secondInputFileName = argv[2];
	return args;
}

void CompareFiles(std::ifstream& firstInput, std::ifstream& secondInput)
{
	//Сравнение двух файлов
	char ch1, ch2;
	int stringNumFirstFile = 1, stringNumSecondFile = 1;
	bool isDiff = false;
	while (firstInput.get(ch1) && secondInput.get(ch2))
	{
		if (ch1 != ch2)
		{
			isDiff = true;  
			break;
		}
		if (ch1 == '\n')
		{
			stringNumFirstFile++;
		}
		if (ch2 == '\n')
		{
			stringNumSecondFile++;
		}
	}
	if (isDiff)
	{
		std::cout << "Files are different." << " Line number is " << std::max(stringNumFirstFile, stringNumSecondFile) << std::endl;
	}
	else
	{
		std::cout << "Files are equal" << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);

	// Проверка правильности аргуметнов командной строки
	if (!args)
	{
		return 1;
	}

	// Открываем первый входной файл
	std::ifstream firstInput;
	firstInput.open(args->firstInputFileName);
	if (!firstInput.is_open())
	{
		std::cout << "Failed to open '" << args->firstInputFileName << "' for reading" << std::endl;
		return 1;
	}

	// Открываем второй входной файл
	std::ifstream secondInput;
	secondInput.open(args->secondInputFileName);
	if (!secondInput.is_open())
	{
		std::cout << "Failed to open '" << args->secondInputFileName << "' for reading" << std::endl;
		return 1;
	}

	CompareFiles(firstInput, secondInput);

	return 0;
}
