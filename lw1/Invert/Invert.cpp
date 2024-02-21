#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

typedef std::array<std::array<double, 3>, 3> TripleMatrix;
typedef std::array<std::array<double, 2>, 2> DoubleMatrix;

TripleMatrix ReadMatrix(const std::string& matrixFileName)
{
	std::ifstream matrixFile;
	matrixFile.open(matrixFileName);
	if (!matrixFile.is_open())
	{
		throw std::runtime_error("Failed to open " + matrixFileName + " for reading");
	}

	TripleMatrix matrix;
	double matrixElement;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (!(matrixFile >> matrixElement))
			{
				throw std::invalid_argument("Invalid matrix");
			}
			matrix[i][j] = matrixElement;
		}
	}

	return matrix;
}

double GetTripleMatrixDeterminant(const TripleMatrix& matrix)
{
	double positiveDiagonal = matrix[0][0] * matrix[1][1] * matrix[2][2];
	double positiveTriangle1 = matrix[0][1] * matrix[1][2] * matrix[2][0];
	double positiveTriangle2 = matrix[1][0] * matrix[2][1] * matrix[0][2];

	double negativeDiagonal = matrix[0][2] * matrix[1][1] * matrix[2][0];
	double negativeTriangle1 = matrix[0][1] * matrix[1][0] * matrix[2][2];
	double negativeTriangle2 = matrix[0][0] * matrix[1][2] * matrix[2][1];

	return positiveDiagonal + positiveTriangle1 + positiveTriangle2
		- negativeDiagonal - negativeTriangle1 - negativeTriangle2;
}

double GetDoubleMatrixDeterminant(const DoubleMatrix matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

double GetMatrixMinor(size_t i, size_t j, const TripleMatrix& matrix)
{
	DoubleMatrix minorMatrix;
	int minorRow = 0;
	for (size_t row = 0; row < 3; ++row)
	{
		if (row == i)
			continue;
		int minorColumn = 0;
		for (size_t col = 0; col < 3; ++col)
		{
			if (col == j)
				continue;
			minorMatrix[minorRow][minorColumn] = matrix[row][col];
			minorColumn++;
		}
		minorRow++;
	}

	return GetDoubleMatrixDeterminant(minorMatrix);
}

void WriteMatrix(const TripleMatrix& matrix)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

TripleMatrix InvertMatrix(const TripleMatrix& matrix)
{
	if (matrix.empty())
	{
		throw std::runtime_error("Matrix is empty");
	}
	if (GetTripleMatrixDeterminant(matrix) == 0)
	{
		throw std::runtime_error("Determinant is zero");
	}

	TripleMatrix invertedMatrix;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			invertedMatrix[j][i] = pow(-1, i + j) * GetMatrixMinor(i, j, matrix) / GetTripleMatrixDeterminant(matrix);
		}
	}

	return invertedMatrix;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count" << std::endl
				  << "Usage: invert.exe <matrix file>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string matrixFileName = argv[1];
	try
	{
		TripleMatrix matrix = ReadMatrix(matrixFileName);
		TripleMatrix invertedMatrix = InvertMatrix(matrix);
		WriteMatrix(invertedMatrix);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}