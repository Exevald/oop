#include "TemplateExpander.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	bool isHelpModeEnabled = false;
	bool isConsoleModeEnabled = false;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	Args args;

	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		args.isHelpModeEnabled = true;
		return args;
	}

	if (argc == 1)
	{
		args.isConsoleModeEnabled = true;
		return args;
	}

	if (argc < 3)
	{
		std::cout << "Invalid argument count" << std::endl
				  << "Usage: expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]"
				  << std::endl;
		return std::nullopt;
	}

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	TemplateParams params;
	for (size_t i = 3; i <= argc - 2; i += 2)
	{
		params.emplace(argv[i], argv[i + 1]);
	}

	return args;
}

std::string TrimBlanks(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos)
	{
		return "";
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, last - first + 1);
}

void PrepareStreams(const std::string& inputFileName, const std::string& outputFileName, std::ifstream& input, std::ofstream& output)
{
	input.open(inputFileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading");
	}

	output.open(outputFileName);
	if (!output.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFileName + " for writing");
	}
}

void FindKeyAndValue(const std::string& line, std::string& key, std::string& value)
{
	size_t delimiterPos = line.find(":=");
	if (delimiterPos == std::string::npos)
	{
		throw std::runtime_error("Invalid input format: " + line);
	}

	key = TrimBlanks(line.substr(0, delimiterPos));
	value = TrimBlanks(line.substr(delimiterPos + 2));
}

void ExpandFileStreamTemplate(const std::string& inputFileName, const std::string& outputFileName)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	TemplateParams params;

	PrepareStreams(inputFileName, outputFileName, inputFile, outputFile);
	std::string line;

	while (std::getline(inputFile, line))
	{
		if (line.empty())
		{
			break;
		}
		std::string key, value;
		FindKeyAndValue(line, key, value);

		params.emplace(key, value);
	}

	std::stringstream templateStream;
	while (std::getline(inputFile, line))
	{
		templateStream << line << std::endl;
	}

	outputFile << ExpandTemplate(templateStream.str(), params);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}

void ExpandStreamTemplate(std::istream& input, std::ostream& output)
{
	std::string line;
	TemplateParams params;

	while (std::getline(input, line))
	{
		if (line.empty())
		{
			break;
		}
		std::string key, value;
		FindKeyAndValue(line, key, value);

		params.emplace(key, value);
	}

	std::stringstream templateStream;
	while (std::getline(input, line))
	{
		templateStream << line << std::endl;
	}

	output << ExpandTemplate(templateStream.str(), params);
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}
	if (args->isHelpModeEnabled)
	{
		std::cout << "Usage: expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]" << std::endl
				  << "If no arguments are provided, the program reads from stdin and writes to stdout." << std::endl
				  << "Use -h to display this help message." << std::endl;
		return EXIT_SUCCESS;
	}

	try
	{
		if (args->isConsoleModeEnabled)
		{
			ExpandStreamTemplate(std::cin, std::cout);
		}
		else
		{
			ExpandFileStreamTemplate(args->inputFileName, args->outputFileName);
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}