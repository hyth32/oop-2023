//invert -- 80
//Разработайте приложение invert.exe, выполняющее инвертирование матрицы 3 * 3, т.е.нахождение обратной матрицы  и выводящее коэффициенты результирующей матрицы в стандартный поток вывода.Формат командной строки приложения :
//invert.exe <matrix file1>
//Коэффициенты входной матрицы заданы во входном текстовом файле(смотрите файл matrix.txt в качестве иллюстрации)  в трех строках по 3 элемента.
//Коэффициенты результирующей матрицы выводятся с точностью до 3 знаков после запятой.
//Используйте двухмерные массивы для хранения коэффициентов матриц.

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

constexpr int MATRIX_ROW = 3;
constexpr int MATRIX_COLUMN = 3;

typedef std::array<std::array<double, MATRIX_ROW>, MATRIX_COLUMN> Matrix;

std::optional<Matrix> GetMatrix(const std::string& inputPath);
std::optional<Matrix> ReadMatrix(std::istream& inputFile);
void OutputMatrix(const Matrix& matrix);
std::optional<Matrix> InvertMatrix(const Matrix& matrix);
double GetDeterminant(const Matrix& matrix);
std::optional<Matrix> TransposeMatrix(const Matrix& matrix);
std::optional<Matrix> GetComplementMatrix(const Matrix& matrix);
std::optional<Matrix> MultiplyMatrixAndNumber(const Matrix& matrix, double number);

struct Args
{
	std::string inputPath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return { { argv[1] } };
}

std::optional<Matrix> GetMatrix(const std::string& inputPath)
{
	std::ifstream inputFile;
	inputFile.open(inputPath);

	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Input file does not open");
	}

	auto matrix = ReadMatrix(inputFile);

	if (!matrix.has_value())
	{
		throw std::invalid_argument("There is no matrix");
	}

	return { matrix };
}
 
std::optional<Matrix> ReadMatrix(std::istream& inputFile)
{
	Matrix matrix;

	double number;
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			if (!(inputFile >> number))
			{
				throw std::invalid_argument("Wrong matrix");
			}

			matrix[matrixRow][matrixColumn] = number;
		}
	}

	return { matrix };
}

void OutputMatrix(const Matrix& matrix)
{
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			std::cout << "    " << std::fixed << std::setprecision(3) << matrix[matrixRow][matrixColumn];
		}

		std::cout << std::endl;
	}
}

std::optional<Matrix> InvertMatrix(const Matrix& matrix)
{
	double determinant = GetDeterminant(matrix);
	if (determinant == 0)
	{
		throw std::runtime_error("There is no inverse matrix. Determinant is 0");
	}

	auto complementMatrix = GetComplementMatrix(matrix);

	if (!complementMatrix.has_value())
	{
		throw std::runtime_error("There is no complement matrix.");
	}

	auto transposedMatrix = TransposeMatrix(complementMatrix.value());

	if (!transposedMatrix.has_value())
	{
		throw std::runtime_error("There is no transposed matrix.");
	}

	auto invertedMatrix = MultiplyMatrixAndNumber(transposedMatrix.value(), 1 / (determinant));

	if (!invertedMatrix.has_value())
	{
		throw std::runtime_error("There is no inverted matrix.");
	}

	return { invertedMatrix };
}

double GetDeterminant(const Matrix& matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1];
}

std::optional<Matrix> TransposeMatrix(const Matrix& matrix)
{
	Matrix transposedMatrix;
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			transposedMatrix[matrixRow][matrixColumn] = matrix[matrixColumn][matrixRow];
		}
	}

	return { transposedMatrix };
}

std::optional<Matrix> GetComplementMatrix(const Matrix& matrix)
{
	Matrix complementMatrix;
	double minor;
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			minor = matrix[matrixRow][matrixColumn] * matrix[(matrixRow + 1) % 3][(matrixColumn + 1) % 3] - matrix[matrixRow][(matrixColumn + 1) % 3] * matrix[(matrixRow + 1) % 3][matrixColumn];
			complementMatrix[(matrixRow + 2) % 3][(matrixColumn + 2) % 3] = minor;
		}
	}

	return { complementMatrix };
}

std::optional<Matrix> MultiplyMatrixAndNumber(const Matrix& matrix, double number)
{
	Matrix resultMatrix;
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			resultMatrix[matrixRow][matrixColumn] = matrix[matrixRow][matrixColumn] * number;
		}
	}

	return { resultMatrix };
}

int main(int argc, char* argv[])
{
	std::optional<Args> args;

	args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		std::cout << "Wrong input. Params should be: invert.exe <matrix file>" << std::endl;
		return 1;
	}

	try
	{
		auto matrix = GetMatrix(args->inputPath);
		auto invertedMatrix = InvertMatrix(matrix.value());
		OutputMatrix(invertedMatrix.value());
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}
