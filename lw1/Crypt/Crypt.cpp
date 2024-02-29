#include <fstream>
#include <iostream>
#include <optional>
#include <string>

enum class AppMode
{
	Encrypt,
	Decrypt
};

struct Args
{
	AppMode mode;
	std::string inputFileName;
	std::string outputFileName;
	uint8_t key;
};

int ConvertAndCheckKey(const std::string& key)
{
	int resultKey;
	const int MIN_KEY_VALUE = 0;
	const int MAX_KEY_VALUE = 255;
	try
	{
		resultKey = std::stoi(key, 0, 10);
	}
	catch (const std::invalid_argument&)
	{
		return -1;
	}
	catch (const std::overflow_error&)
	{
		return -1;
	}
	if (resultKey < MIN_KEY_VALUE || resultKey > MAX_KEY_VALUE)
	{
		return -1;
	}
	return resultKey;
}

std::optional<AppMode> ConvertAndCheckMode(const char* mode)
{
	if (strcmp(mode, "encrypt") == 0)
	{
		return AppMode::Encrypt;
	}
	else if (strcmp(mode, "decrypt") == 0)
	{
		return AppMode::Decrypt;
	}
	else
	{
		return std::nullopt;
	}
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count" << std::endl
				  << "Usage: crypt.exe crypt/decrypt <inputFile> <outputFile> <key>" << std::endl;
		return std::nullopt;
	}

	auto mode = ConvertAndCheckMode(argv[1]);
	if (!mode)
	{
		std::cout << "Wrong app mode: " << argv[1] << std::endl
				  << "Use crypt or decrypt mode" << std::endl;
		return std::nullopt;
	}

	int key = ConvertAndCheckKey(argv[4]);
	if (key == -1)
	{
		std::cout << "Invalid key argument. Key must be a number from 0 to 255" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.mode = mode.value();
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = key;

	return args;
}

char CryptSymbol(const char ch, const uint8_t key)
{
	uint8_t byte = ch ^ key;
	uint8_t result = 0b00000000;
	result |= (byte & 0b10000000) >> 2;
	result |= (byte & 0b01100000) >> 5;
	result |= (byte & 0b00011000) << 3;
	result |= (byte & 0b00000111) << 2;

	return result;
}

char DecryptSymbol(const char ch, const uint8_t key)
{
	uint8_t result = 0b00000000;
	result |= (ch & 0b00100000) << 2;
	result |= (ch & 0b00000011) << 5;
	result |= (ch & 0b11000000) >> 3;
	result |= (ch & 0b00011100) >> 2;

	return result ^= key;
}

void CryptStream(std::ifstream& inputFile, std::ofstream& outputFile, const uint8_t key)
{
	char ch;
	while (inputFile.get(ch))
	{
		if (!outputFile.put(CryptSymbol(ch, key)))
		{
			throw std::runtime_error("Failed to save data on disk");
		}
	}
}

void DecryptStream(std::ifstream& inputFile, std::ofstream& outputFile, const uint8_t key)
{
	char ch;
	while (inputFile.get(ch))
	{
		if (!outputFile.put(DecryptSymbol(ch, key)))
		{
			throw std::runtime_error("Failed to save data on disk");
		}
	}
}

void CryptOrDecryptBinaryFile(
	const AppMode& mode,
	const std::string& inputFileName,
	const std::string& outputFileName,
	const uint8_t key)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName, std::ios::binary | std::ios::in);
	std::ofstream outputFile;
	outputFile.open(outputFileName, std::ios::binary | std::ios::out);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading");
	}
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFileName + " for writing");
	}

	switch (mode)
	{
	case AppMode::Encrypt:
		CryptStream(inputFile, outputFile, key);
		break;
	case AppMode::Decrypt:
		DecryptStream(inputFile, outputFile, key);
		break;
	}

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
		CryptOrDecryptBinaryFile(args->mode, args->inputFileName, args->outputFileName, args->key);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}