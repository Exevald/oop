#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count" << std::endl
				  << "Usage: radix.exe <source notation> <destination notation> <value>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];

	return args;
}

bool HandleError(const bool& errInvalidArgument, const bool& errValueOverflow)
{
	if (errInvalidArgument)
	{
		std::cout << "Invalid argument!" << std::endl;
		return true;
	}
	if (errValueOverflow)
	{
		std::cout << "Value overflow!" << std::endl;
		return true;
	}

	return false;
}

int StringToInt(const std::string& str, const int& radix, bool& errInvalidArgument, bool& errValueOverflow)
{
	int value = 0;
	if (str == "0")
	{
		return 0;
	}
	try
	{
		value = std::stoi(str, 0, radix);
	}
	catch (std::invalid_argument&)
	{
		errInvalidArgument = true;
		return 0;
	}
	catch (std::out_of_range&)
	{
		errValueOverflow = true;
		return 0;
	}
	return value;
}

std::string IntToString(int n, const int& radix, bool& wasError)
{
	std::string vocabulary = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string result;
	if (n < 0 || n > INT_MAX)
	{
		wasError = true;
	}
	while (n > 0)
	{
		result = vocabulary[n % radix] + result;
		n /= radix;
	}

	return result;
}

int ConvertNotation(const std::string& notation, bool& errInvalidArgument, bool& errValueOverflow)
{
	const int minNotation = 2;
	const int maxNotation = 36;

	int convertedNotatiion = StringToInt(notation, 10, errInvalidArgument, errValueOverflow);
	bool isNotationCorrect = (convertedNotatiion >= minNotation) || (convertedNotatiion <= maxNotation);
	if (!isNotationCorrect)
	{
		errValueOverflow = true;
		return 0;
	}

	return convertedNotatiion;
}

bool ConvertValueToNotation(const std::string& sourceNotation, const std::string& destinationNotation, std::string str)
{
	bool errInvalidArgument = false;
	bool errValueOverflow = false;
	std::string resultInDestinationNotation;

	int convertedSourceNotation = ConvertNotation(sourceNotation, errInvalidArgument, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return false;
	}
	int convertedDestinationNotation = ConvertNotation(destinationNotation, errInvalidArgument, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return false;
	}

	bool isNegative = false;
	const char negativeSymbol = '-';
	if (str[0] == negativeSymbol && str.size() > 2 && str[1] != '0')
	{
		isNegative = true;
		str.erase(0, 1);
	}
	int valueInDecimalNotation = StringToInt(str, convertedSourceNotation, errInvalidArgument, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return false;
	}
	resultInDestinationNotation = IntToString(valueInDecimalNotation, convertedDestinationNotation, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return false;
	}
	if (valueInDecimalNotation == 0)
	{
		resultInDestinationNotation = "0";
	}
	if (isNegative)
	{
		resultInDestinationNotation = negativeSymbol + resultInDestinationNotation;
	}
	std::cout << "Value in destination notation: " << resultInDestinationNotation << std::endl;

	return true;
}

int main(int argc, char* argv[])
{
	std::string result;

	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	if (!ConvertValueToNotation(args->sourceNotation, args->destinationNotation, args->value))
	{
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}