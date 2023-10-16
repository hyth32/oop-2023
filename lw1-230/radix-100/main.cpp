//radix -- 100
//Разработайте программу radix.exe, выполняющую перевод чисел из одной произвольной системы счисления в другую произвольную и запись результата в стандартный поток вывода.Под произвольной системой счисления понимается система с основанием от 2 до 36. Системы счисления с 11 - ричной до 36 - ричной должны использовать заглавные буквы латинского алфавита от A до Z для представления разрядов с 1010 до 3510. Формат командной строки приложения :
//radix.exe <source notation> <destination notation> <value>

#include <algorithm>
#include <climits>
#include <iostream>
#include <optional>
#include <string>

#define MAX_RADIX 36
#define MIN_RADIX 2

/* Headers */
bool IsCapitalLetter(char ch);

bool IsDigit(char ch);

int CharToIntRadix(char ch, int radix);

char IntToCharRadix(int n, int radix);

long StringToInt(const std::string& str, int radix);

std::string IntToString(long n, int radix);

/* Main logic */
struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	// Validate input values
	if (argc != 4)
	{
		return std::nullopt;
	}

	long sourceNotation = StringToInt(argv[1], 10);
	if ((sourceNotation > MAX_RADIX) || (sourceNotation < MIN_RADIX))
	{
		throw std::runtime_error("bad range for source notation");
	}

	long destinationNotation = StringToInt(argv[2], 10);
	if ((destinationNotation > MAX_RADIX) || (destinationNotation < MIN_RADIX))
	{
		throw std::runtime_error("bad range for destination notation");
	}

	return {
		(Args){
			static_cast<int>(sourceNotation),
			static_cast<int>(destinationNotation),
			argv[3] }
	};
}

int main(int argc, char* argv[])
{
	try
	{
		std::optional<Args> result = ParseArgs(argc, argv);
		if (!result.has_value())
		{
			std::cout << "Wrong amount of parameters" << std::endl;
			std::cout << "Usage: radix <source notation> <destination notation> <value>" << std::endl;
			return 1;
		}
		long number = StringToInt(result->value, result->sourceNotation);
		std::cout << IntToString(number, result->destinationNotation) << std::endl;
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}
	return 0;
}

/* Functions */
bool IsCapitalLetter(char ch)
{
	return (ch <= 'Z') && (ch >= 'A');
}

bool IsDigit(char ch)
{
	return (ch >= '0') && (ch <= '9');
}

int CharToIntRadix(char ch, int radix)
{
	if (IsDigit(ch))
	{
		if (ch - '0' >= radix)
		{
			throw std::logic_error("char is bigger than radix");
		}
		return ch - '0';
	}

	if (IsCapitalLetter(ch))
	{
		if (ch - 'A' + 10 >= radix)
		{
			throw std::logic_error("char is bigger than radix");
		}
		return ch - 'A' + 10;
	}

	throw std::logic_error("can not covert char to int");
}

long StringToInt(const std::string& str, int radix)
{
	if ((radix > MAX_RADIX) || (radix < MIN_RADIX))
	{
		throw std::runtime_error("radix is not in correct range");
	}

	bool isNegative = false;
	if (str.length() > 0 && str[0] == '-')
	{
		isNegative = true;
	}

	long result = 0;
	for (int i = isNegative ? 1 : 0; i < static_cast<int>(str.length()); i++)
	{
		long lastCharIntValue = CharToIntRadix(str[i], radix);
		if (result > ((LONG_MAX - lastCharIntValue) / radix))
		{
			throw std::runtime_error("error: overflow while converting");
		}
		result = result * radix + lastCharIntValue;
	}

	if (isNegative)
	{
		if (result == LONG_MIN)
		{
			throw std::runtime_error("error: converting negative to positive overflow");
		}
		result = -result;
	}

	return result;
}

char IntToCharRadix(int n, int radix)
{
	if ((radix > MAX_RADIX) || (radix < MIN_RADIX))
	{
		throw std::runtime_error("radix is not in correct range");
	}

	if (n >= radix)
	{
		throw std::runtime_error("number is bigger than radix");
	}

	if ((n >= 0) && (n <= 9))
	{
		return static_cast<char>('0' + n);
	}

	if ((n >= 10) && (n <= 36))
	{
		return static_cast<char>('A' + (n - 10));
	}

	throw std::runtime_error("number is not in correct range");
}

std::string IntToString(long n, int radix)
{
	if (n == 0)
	{
		return "0";
	}

	bool isNegative = false;
	if (n < 0)
	{
		n = -n;
		isNegative = true;
	}

	std::string result = "";
	while (n > 0)
	{
		auto divResult = std::ldiv(n, radix);
		result += IntToCharRadix(static_cast<int>(divResult.rem), radix);
		n = divResult.quot;
	}

	if (isNegative)
	{
		result += '-';
	}

	std::reverse(result.begin(), result.end());
	return result;
}
