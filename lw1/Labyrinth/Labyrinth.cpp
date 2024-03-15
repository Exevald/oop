#include "LabyrinthModule.h"

#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count" << std::endl
				  << "Usage: labyrinth.exe <input file> <output file>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
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
		Labyrinth labyrinth = ReadLabyrinth(args->inputFileName);
		FindShortestPath(labyrinth);
		WriteLabyrinth(args->outputFileName, labyrinth);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}