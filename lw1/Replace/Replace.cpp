#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count" << std::endl
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}
	std::string result;
	size_t pos = 0;
	size_t lastPos = 0;
	while ((pos = subject.find(searchString, pos)) != std::string::npos)
	{
		// Не использовать итераторы. Использовать append
		std::string previousString(subject.begin() + lastPos, subject.begin() + pos);
		result += previousString;
		result += replacementString;
		pos += searchString.length();
		lastPos = pos;
	}
	std::string endOfString(subject.begin() + lastPos, subject.end());
	result += endOfString;

	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << std::endl;
	}
	if (!input.eof())
	{
		throw std::runtime_error("Failed to read text from file");
	}
}

void CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName, const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);

	std::ofstream outputFile;
	outputFile.open(outputFileName);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading");
	}

	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFileName + " for writing");
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}
	try
	{
		CopyFileWithReplacement(args->inputFileName, args->outputFileName, args->searchString, args->replaceString);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}