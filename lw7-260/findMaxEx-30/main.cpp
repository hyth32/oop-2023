#include "find_max_ex.h"
#include <iostream>
#include <vector>

struct SportsMan {
	std::string name;
	float height;
	float weight;
};

int main()
{
	const std::vector<SportsMan> sportsmen{
		{"Шубин Максимилиан Юрьевич", 167.87, 84.38},
		{"Власов Донат Геласьевич", 197.65, 90.38},
		{"Крюков Ибрагил Владиславович", 197.25, 86.35},
		{"Филиппов Иосиф Робертович", 181.34, 92.80},
		{"Ермаков Демьян Анатольевич", 160.07, 99.80},
		{"Лаврентьев Феликс Миронович", 195.95, 92.02},
	};

	SportsMan maxHeightSportsman;
	auto isMaxHeightSportsmanFound = FindMaxEx(
		sportsmen,
		maxHeightSportsman,
		[](const SportsMan& first, const SportsMan& second) -> bool {
			return first.height < second.height;
		}
 	);

	SportsMan maxWeightSportsman;
	auto isMaxWeightSportsmanFound =  FindMaxEx(
		sportsmen,
		maxWeightSportsman,
		[](const SportsMan& first, const SportsMan& second) -> bool {
			return first.weight < second.weight;
		}
	);

	if (isMaxHeightSportsmanFound)
	{
		std::cout
			<< "Самый высокий спортсмен " << maxHeightSportsman.name
			<< " с ростом " << maxHeightSportsman.height << std::endl;
	}
	else
	{
		std::cout << "Самый высокий спортсмен не найден" << std::endl;
	}

	if (isMaxWeightSportsmanFound)
	{
		std::cout
			<< "Самый тяжелый спортсмен " << maxWeightSportsman.name
			<< " с весом " << maxWeightSportsman.weight << std::endl;
	}
	else
	{
		std::cout << "Самый тяжелый спортсмен не найден" << std::endl;
	}

	return EXIT_SUCCESS;
}