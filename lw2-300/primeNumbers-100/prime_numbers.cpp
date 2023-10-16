#include "prime_numbers.h"
#include <cmath>
#include <vector>

std::set<int> GeneratePrimeNumbers(int upperBound)
{
	std::set<int> primeNumbers{};
	if (upperBound <= 2)
	{
		return primeNumbers;
	}
	std::vector<bool> sieve(upperBound, true);
	primeNumbers.insert(2);
	for (int i = 3; i < upperBound - 1; i += 2)
	{
		if (!sieve[i])
		{
			continue;
		}
		if (i < std::sqrt(upperBound - 1))
		{
			for (int j = i * i; j < upperBound - 1; j += i)
			{
				sieve[j] = false;
			}
		}
		primeNumbers.insert(i);
	}
	return primeNumbers;
}
