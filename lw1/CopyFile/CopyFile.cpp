#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argumants count" << std::endl;
		std::cout << "Usage: CopyFile.exe <input file name> <output file name>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

void CopyStreams(std::ifstream& input, std::ofstream& output)
{
	// Копируем содержимое входного файла в выходной
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
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

	// Открываем входной файл
	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading" << std::endl;
		return 1;
	}

	// Открываем выходной файл
	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for writing" << std::endl;
		return 1;
	}

	CopyStreams(input, output);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file" << std::endl;
		return 1;
	}
	return 0;
}
