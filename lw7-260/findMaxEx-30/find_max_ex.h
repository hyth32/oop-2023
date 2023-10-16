#ifndef FIND_MAX_EX_H
#define FIND_MAX_EX_H

#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less) noexcept
{
	if (arr.empty())
	{
		return false;
	}

	auto max = arr.begin();

	for (auto i = arr.begin(); i != arr.end(); i++)
	{
		if (less(*max, *i))
		{
			max = i;
		}
	}

	maxValue = *max;

	return true;
}

#endif // FIND_MAX_EX_H
