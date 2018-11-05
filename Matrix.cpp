#include <iostream>
#include "Matrix.h"

Matrix::Matrix() : matr(nullptr), n(0), m(0)
{
}

Matrix::Matrix(int row, int column, double numb = 0) : n(row), m(column)
{
	matr = new double*[n];
	for (int i = 0; i < n; i++)
	{
		*(matr + i) = new double[m];
		for (int j = 0; j < m; j++)
		{
			*(*(matr + i) + j) = numb;
		}
	}
}

Matrix::Matrix(const Matrix& other) : n(other.n), m(other.m)
{
	matr = new double*[n];
	for (int i = 0; i < n; i++)
	{
		*(matr + i) = new double[m];
		for (int j = 0; j < m; j++)
		{
			*(*(matr + i) + j) = *(*(other.matr + i) + j);
		}
	}
}

Matrix::Matrix(Matrix&& other)
{
	n = other.n;
	m = other.m;
	matr = new double*[n];
	for (int i = 0; i < n; i++)
	{
		*(matr + i) = new double[m];
		for (int j = 0; j < m; j++)
		{
			*(*(matr + i) + j) = *(*(other.matr + i) + j);
		}
	}
	other.n = 0;
	other.m = 0;
	other.matr = nullptr;
}

Matrix::~Matrix()
{
	for (int i = 0; i < n; i++)
	{
		delete[] * (matr + i);
	}
	delete[] matr;
}

double* Matrix::getRow(int ind)const
{
	double* row = new double[m];
	for (int i = 0; i < m; i++)
	{
		*(row + i) = *(*(matr + ind - 1) + i);
	}
	return row;
}

double* Matrix::getColumn(int ind)const
{
	double* column = new double[n];
	for (int i = 0; i < n; i++)
	{
		*(column + i) = *(*(matr + i) + ind - 1);
	}
	return column;
}

Matrix Matrix::operator+(const Matrix& other) const
{
	if ((n == other.n) && (m == other.m))
	{
		Matrix result(n, m);
		result.matr = new double*[n];
		for (int i = 0; i < n; i++)
		{
			*(result.matr + i) = new double[m];
			for (int j = 0; j < m; j++)
			{
				*(*(result.matr + i) + j) = *(*(matr + i) + j) + *(*(other.matr + i) + j);
			}
		}
		return result;
	}
	else
	{
		cout << "Додавання нерівнорозмірних матриць неможливе" << endl;
		system("pause");
		exit(1);
	}
}

Matrix Matrix::operator-(const Matrix& other) const
{
	if ((n == other.n) && (m == other.m))
	{
		Matrix result(n, m);
		result.matr = new double*[n];
		for (int i = 0; i < n; i++)
		{
			*(result.matr + i) = new double[m];
			for (int j = 0; j < m; j++)
			{
				*(*(result.matr + i) + j) = *(*(matr + i) + j) - *(*(other.matr + i) + j);
			}
		}
		return result;
	}
	else
	{
		cout << "Віднімання нерівнорозмірних матриць неможливе" << endl;
		system("pause");
		exit(1);
	}
}

Matrix Matrix::operator* (double numb) const
{
	Matrix result(n, m);
	result.matr = new double*[n];
	for (int i = 0; i < n; i++)
	{
		*(result.matr + i) = new double[m];
		for (int j = 0; j < m; j++)
		{
			*(*(result.matr + i) + j) = (*(*(matr + i) + j)) * numb;
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& other)const
{
	if (m == other.n)
	{
		int counter = m;
		double temp = 0;
		Matrix result(n, other.m);
		double *row;
		double *column;
		result.matr = new double*[n];
		for (int i = 0; i < n; i++)
		{
			*(result.matr + i) = new double[other.m];
			for (int j = 0; j < other.m; j++)
			{
				row = getRow(i + 1);
				column = other.getColumn(j + 1);
				for (int k = 0; k < counter; k++)
				{
					temp += (row[k] * column[k]);
				}
				*(*(result.matr + i) + j) = temp;
				temp = 0;
			}
		}
		return result;
	}
	else
	{
		cout << "Множення нерівнорозмірних матриць неможливе" << endl;
		system("pause");
		exit(1);
	}

}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		for (int i = 0; i < n; i++)
		{
			delete[] * (matr + i);
		}
		delete matr;
		n = other.n;
		m = other.m;
		matr = new double*[n];
		for (int i = 0; i < n; i++)
		{
			*(matr + i) = new double[m];
			for (int j = 0; j < m; j++)
			{
				*(*(matr + i) + j) = *(*(other.matr + i) + j);
			}
		}
	}

	return *this;
}

Matrix& Matrix::operator=(Matrix&& other)
{
	if (this != &other)
	{
		for (int i = 0; i < n; i++)
		{
			delete[] * (matr + i);
		}
		delete matr;
		n = other.n;
		m = other.m;
		matr = other.matr;
		other.n = 0;
		other.m = 0;
		other.matr = nullptr;
	}

	return *this;
}

bool Matrix::operator==(const Matrix& other)const
{
	if (n != other.n || m != other.m)
		return false;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (*(*(matr + i) + j) != *(*(other.matr + i) + j))
				return false;
		}
	}
	return true;
}
double* Matrix::operator[](int i)
{
	return matr[i];
};


Matrix& Matrix::operator~()
{
	Matrix result(m, n);
	double *column;
	result.matr = new double*[m];
	for (int i = 0; i < m; i++)
	{
		column = this->getColumn(i + 1);
		*(result.matr + i) = new double[n];
		for (int j = 0; j < n; j++)
		{
			*(*(result.matr + i) + j) = column[j];
		}
	}
	return result;
}

ostream& operator << (ostream& output, const Matrix& matrix)
{
	for (int i = 0; i < matrix.n; i++)
	{
		for (int j = 0; j < matrix.m; j++)
		{
			cout << setw(16) << *(*(matrix.matr + i) + j);
		}
		cout << endl;
	}
	return output;
}

istream& operator >> (istream& input, Matrix& matrix)
{
	cout << "Введіть розмір матриці: рядків  ";
	cin >> matrix.n;
	cout << " стовпчиків ";
	cin >> matrix.m;
	matrix.matr = new double*[matrix.n];
	for (int i = 0; i < matrix.n; i++)
	{
		*(matrix.matr + i) = new double[matrix.m];
		for (int j = 0; j < matrix.m; j++)
		{
			cout << "Елемент " << i + 1 << " рядка, " << j + 1 << " стовпчика ";
			cin >> *(*(matrix.matr + i) + j);
		}
	}

	return input;
}

Matrix Matrix::GaussMethod(Matrix A)
{
	int n = A.n;

	for (int i = 0; i < n; i++) 
	{
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k < n; k++) 
		{
			if (abs(A[k][i]) > maxEl) 
			{
				maxEl = abs(A[k][i]);
				maxRow = k;
			}
		}

		for (int k = i; k < n + 1; k++) 
		{
			double temp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = temp;
		}

		for (int k = i + 1; k < n; k++) 
		{
			double c = -A[k][i] / A[i][i];
			for (int j = i; j < n + 1; j++)
			{
				if (i == j)
				{
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}

	Matrix result(1, n, 0);
	for (int i = n - 1; i >= 0; i--)
	{
		result[0][i] = A[i][n] / A[i][i];
		for (int k = i - 1; k >= 0; k--)
		{
			A[k][n] -= A[k][i] * result[0][i];
		}
	}
	return result;
}

Matrix Matrix::KachmagMethod(Matrix b)
{
}