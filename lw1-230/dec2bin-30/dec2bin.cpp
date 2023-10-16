//dec2bin -- 30
//Разработайте программу dec2bin.exe, выполняющую перевод числа из десятичной системы в двоичную и вывод результата в стандартный поток вывода.Формат командной строки :
//bin2dec.exe <число в десятичной системе>

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const unsigned int ARGUMENT_COUNT = 2;

unsigned long long int ConvertDecToBin(const unsigned long int dec, unsigned long int bin)
{
	if (dec / 2 != 0)
	{
		ConvertDecToBin(dec / 2, bin);
	}
	bin << dec % 2;

	return bin;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	if (argc != ARGUMENT_COUNT)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: copyfile.exe <÷èñëî â äåñÿòè÷íîé ñèñòåìå>\n";
		return 1;
	}

	try
	{
		const unsigned long int dec = stoul(argv[1], nullptr, 10);
	}
	catch (const exception& e)
	{
		cout << e.what();
		return 1;
	}

	long long int bin;
	cout << ConvertDecToBin(dec, bin);

	return 0;
}
