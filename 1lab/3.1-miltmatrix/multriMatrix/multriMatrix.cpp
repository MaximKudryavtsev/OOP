// multriMatrix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

static const int COUNT_OF_ARGUMENTS = 3;
static const int MATRIX_SIZE = 3;

void ReadMatrix(ifstream &input, float matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			input >> matrix[i][j];
		}
	}
}

void MultiplicationMatrix(float firstMatrix[MATRIX_SIZE][MATRIX_SIZE], float secondMAtrix[MATRIX_SIZE][MATRIX_SIZE], float resultMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			float result = 0;
			for (int t = 0; t < MATRIX_SIZE; t++)
			{
				result += firstMatrix[i][t] * secondMAtrix[t][j];
			}
			resultMatrix[i][j] = result;
		}
	}
}

void PrintMatrix(float resultMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			cout << resultMatrix[i][j] << " ";
		}
		cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	float firstMatrix[MATRIX_SIZE][MATRIX_SIZE];
	float secondMatrix[MATRIX_SIZE][MATRIX_SIZE];
	float resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

	if (argc != COUNT_OF_ARGUMENTS) {
		cout << "Invalid arguments count: \n"
			<< "Usage: multmatrix.exe <matrix file 1> <matrix file 2>\n";
		return 1;
	}

	ifstream input1(argv[1]);
	if (!input1.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ifstream input2(argv[2]);
	if (!input2.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading\n";
		return 1;
	}
	ReadMatrix(input1, firstMatrix);
	ReadMatrix(input2, secondMatrix);
	MultiplicationMatrix(firstMatrix, secondMatrix, resultMatrix);
	PrintMatrix(resultMatrix);
}

