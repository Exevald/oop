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

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	const int minNotation = 2;
	const int maxNotation = 36;
	wasError = false;
	if (str.empty() || radix < minNotation || radix > maxNotation)
	{
		wasError = true;
		return 0;
	}

	int result = 0;
	int sign = 1;
	size_t i = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	for (; i < str.size(); i++)
	{
		int digit = isdigit(str[i]) ? str[i] - '0' : str[i] - 'A' + 10;
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

	if (sign == -1 && -result < INT_MIN)
	{
		wasError = true;
		return 0;
	}

	return sign * result;
}

int StringToInt(const std::string& str, const int radix, bool& errInvalidArgument, bool& errValueOverflow)
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
	catch (const std::invalid_argument&)
	{
		errInvalidArgument = true;
		return 0;
	}
	catch (const std::out_of_range&)
	{
		errValueOverflow = true;
		return 0;
	}
	return value;
}

// Можно просто вернуть пустую строку и обрабатывать уже её
// Не надо передавать примитивные типы данных по константной ссылке
// Добавить обработку знака
std::string IntToString(int n, const int radix, bool& wasError)
{
	// Сделать проверку на radix > 36
	wasError = false;
	if (radix < 2 || radix > 36)
	{
		wasError = true;
		return "";
	}

	std::string vocabulary = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string result;
	if (n < 0 || n > INT_MAX) // Условие всегда false. Вторая часть условия не имеет смысла
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
	// Вынести в отдельную фукнцию
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

	// Переименовать без decimal
	// Сделать имена переменных покороче
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

	std::cout << "Value in destination notation: " << resultInDestinationNotation << std::endl;

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}
	// Поменять возвращаемое значение на string
	if (!ConvertValueToNotation(args->sourceNotation, args->destinationNotation, args->value))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}