//primenumbers -- 100
//Разработайте функцию std::set<int> GeneratePrimeNumbersSet(int upperBound), возвращающую множество всех простых чисел, не превышающих значения upperBound.
//С ее использованием разработайте программу, выводящую в стандартный поток вывода элементы множества простых чисел, не превышающие значения, переданного приложению через обязательный параметр командной строки.
//Максимальное значение верхней границы множества принять равным 100 миллионам.

#include "prime_numbers.h"
#include <iostream>

std::optional<int> GetArgs(int argc, char* argv[])
{
	if (argc == 2)
	{
		try
		{
			return { std::stoi(argv[1]) };
		}
		catch (const std::exception&)
		{
			return std::nullopt;
		}
	}
	return std::nullopt;
}

int main(int argc, char* argv[])
{
	auto upperBound = GetArgs(argc, argv);
	if (!upperBound.has_value())
	{
		std::cout << "Bad upper bound number." << std::endl
				  << "Usage: prime <upper_bound>" << std::endl;
		return 1;
	}

	auto primeSet = GeneratePrimeNumbers(upperBound.value());
	for (auto item : primeSet)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;

	return 0;
}
