#include <iostream>
#include <optional>
#include <string>

const int MIN_NOTATION = 2;
const int MAX_NOTATION = 36;

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

bool HandleError(bool errInvalidArgument, bool errValueOverflow)
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

int StringToInt(const std::string& str, int radix, bool& errInvalidArgument, bool& errValueOverflow)
{
	int result = 0;
	errInvalidArgument = false;
	errValueOverflow = false;

	if (str.empty() || radix < MIN_NOTATION || radix > MAX_NOTATION)
	{
		errInvalidArgument = true;
		return 0;
	}

	int sign = 1;
	size_t i = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	for (; i < str.size(); i++)
	{
		int digit = isdigit(str[i]) ? str[i] - '0' : str[i] - 'A' + 10;
		if (digit >= radix)
		{
			errInvalidArgument = true;
			return 0;
		}
		if (result > (INT_MAX - digit) / radix)
		{
			errValueOverflow = true;
			return 0;
		}
		result = result * radix + digit;
	}

	if (sign == -1 && -result < INT_MIN + 1)
	{
		errValueOverflow = true;
		return 0;
	}

	return sign * result;
}

std::string IntToString(int n, const int radix, bool& errValueOverflow)
{
	errValueOverflow = false;

	if (radix < MIN_NOTATION || radix > MAX_NOTATION)
	{
		errValueOverflow = true;
		return "";
	}

	std::string vocabulary = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string result;

	if (n > INT_MAX - 1)
	{
		errValueOverflow = true;
		return "";
	}
	bool isNegative = false;
	if (n < 0)
	{
		isNegative = true;
		n *= -1;
	}
	if (n < 0 && -n < INT_MIN + 1)
	{
		errValueOverflow = true;
		return "";
	}

	while (n > 0)
	{
		result = vocabulary[n % radix] + result;
		n /= radix;
	}
	if (isNegative)
	{
		result = "-" + result;
	}

	return result;
}

int ConvertNotation(const std::string& notation, bool& errInvalidArgument, bool& errValueOverflow)
{
	errInvalidArgument = false;
	errValueOverflow = false;

	int convertedNotatiion = StringToInt(notation, 10, errInvalidArgument, errValueOverflow);
	bool isNotationCorrect = (convertedNotatiion >= MIN_NOTATION) || (convertedNotatiion <= MAX_NOTATION);
	if (!isNotationCorrect)
	{
		errValueOverflow = true;
		return 0;
	}

	return convertedNotatiion;
}

std::string ConvertValueToNotation(const std::string& sourceNotation, const std::string& destinationNotation, const std::string& str)
{
	bool errInvalidArgument = false;
	bool errValueOverflow = false;
	std::string resultInDestinationNotation;

	int convertedSourceNotation = ConvertNotation(sourceNotation, errInvalidArgument, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return "";
	}
	int convertedDestinationNotation = ConvertNotation(destinationNotation, errInvalidArgument, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return "";
	}

	int valueInDecimalNotation = StringToInt(str, convertedSourceNotation, errInvalidArgument, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return "";
	}
	resultInDestinationNotation = IntToString(valueInDecimalNotation, convertedDestinationNotation, errValueOverflow);
	if (HandleError(errInvalidArgument, errValueOverflow))
	{
		return "";
	}
	if (valueInDecimalNotation == 0)
	{
		resultInDestinationNotation = "0";
	}

	return resultInDestinationNotation;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}
	if (std::string resultValue = ConvertValueToNotation(args->sourceNotation, args->destinationNotation, args->value); resultValue == "")
	{
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "Value in destination notation: " << resultValue << std::endl;
	}

	return EXIT_SUCCESS;
}