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

bool isValueCorrect(const std::string& str)
{
	const char negativeSymbol = '-';
	const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	bool isValueInvalid = (str[0] == '0' || (str[0] == negativeSymbol && str[1] == '0')) && (str.size() >= 2);
	bool isFirstSymbolInvalid = (str[0] != negativeSymbol) && (alphabet.find(str[0]) == std::string::npos);

	if (str.empty() || isValueInvalid || isFirstSymbolInvalid)
	{
		return false;
	}
	for (size_t i = 1; i < str.size(); i++)
	{
		if ((alphabet.find(str[i]) == std::string::npos))
		{
			return false;
		}
	}

	return true;
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

int StringToInt(const std::string& str, const int& radix, bool& wasError)
{
	int digit;
	if (!isValueCorrect(str))
	{
		wasError = true;
		return 0;
	}
	int result = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]))
		{
			digit = str[i] - '0';
		}
		else
		{
			digit = tolower(str[i]) - 'a' + 10;
		}
		if (digit >= radix)
		{
			wasError = true;
			return 0;
		}
		if (result > (INT_MAX - digit) / radix)
		{
			wasError = true;
			return 0;
		}
		result = result * radix + digit;
	}

	return result;
}

std::string IntToString(int n, const int& radix)
{
	std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string result;
	while (n > 0)
	{
		result = alphabet[n % radix] + result;
		n /= radix;
	}

	return result;
}

int ConvertNotation(const std::string& notation, bool& wasError)
{
	const int minNotation = 2;
	const int maxNotation = 36;

	if (!isValueCorrect(notation))
	{
		wasError = true;
	}
	int convertedNotatiion = StringToInt(notation, 10, wasError);
	bool isNotationCorrect = (convertedNotatiion >= minNotation) || (convertedNotatiion <= maxNotation);
	if (!isNotationCorrect)
	{
		wasError = true;
	}

	return convertedNotatiion;
}

bool ConvertValueToNotation(const std::string& sourceNotation, const std::string& destinationNotation, std::string str)
{
	bool errInvalidArgument = false;
	bool errValueOverflow = false;

	int convertedSourceNotation = ConvertNotation(sourceNotation, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return false;
	}
	int convertedDestinationNotation = ConvertNotation(destinationNotation, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return false;
	}

	bool isNegative = false;
	const char negativeSymbol = '-';
	if (str[0] == negativeSymbol)
	{
		isNegative = true;
		str.erase(0, 1);
	}
	int valueInDecimalNotation = StringToInt(str, convertedSourceNotation, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return false;
	}
	std::string valueInDestinationNotation = IntToString(valueInDecimalNotation, convertedDestinationNotation);
	if (isNegative)
	{
		valueInDestinationNotation = negativeSymbol + valueInDestinationNotation;
	}
	std::cout << "Value in destination notation: " << valueInDestinationNotation << std::endl;

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