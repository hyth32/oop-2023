//copyfile -- 20
//Разработайте программу copyfile.exe, выполняющую копирование одного текстового файла в другой.Параметры командной строки :
//copyfile.exe <input file name> <output file name>
//Программа должна корректно обрабатывать ошибки, связанные с файловыми операциями, а также корректно закрываться открываемые программой файлы.
//В комплекте с программой должны обязательно поставляться файлы, позволяющие проверить ее работу в автоматическом режиме.


#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const unsigned int ARGUMENT_COUNT = 3;

int CopyFile(const string& inputFileName, const string& outputFileName)
{
	ifstream input(inputFileName);

	if (!input.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return 1;
	}

	ofstream output(outputFileName);

	if (!output.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing\n";
		return 1;
	}

	string str;

	while (getline(input, str))
	{
		output << str;
		if (!input.eof())
			output << endl;
	}

	if (!input.eof())
	{
		cout << "Failed to copy\n";
		return 1;
	}

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != ARGUMENT_COUNT)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}

	return CopyFile(argv[1], argv[2]);
}
