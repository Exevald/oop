#include "TemplateExpander.h"
#include <fstream>
#include <iostream>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	TemplateParams params;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid argument count" << std::endl
				  << "Usage: expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]"
				  << std::endl;
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	TemplateParams params;
	for (size_t i = 3; i <= argc - 2; i += 2)
	{
		params.emplace(argv[i], argv[i + 1]);
	}
	args.params = params;

	return args;
}

void ExpandStreamTemplateWithParams(std::ifstream& input, std::ofstream& output, const TemplateParams& params)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ExpandTemplate(line, params);
	}
	if (!input.eof())
	{
		throw std::runtime_error("Failed to read text from file");
	}
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

void ExpandTemplateWithParams(const std::string& inputFileName, const std::string& outputFileName, const TemplateParams& params)
{
	std::ifstream inputFile;
	std::ofstream outputFile;

	PrepareStreams(inputFileName, outputFileName, inputFile, outputFile);
	ExpandStreamTemplateWithParams(inputFile, outputFile, params);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	try
	{
		ExpandTemplateWithParams(args->inputFileName, args->outputFileName, args->params);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}