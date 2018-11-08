#include <iostream>
#include "Matrix.h"
#include <cmath>

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


Matrix Matrix::operator~()
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

bool Matrix::isSimmetrial()
{

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if ((*(*(matr + i) + j)) != (*(*(matr + j) + i)))
				return false;
		}
	}
	return true;

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

Matrix Matrix::GaussMethod()
{
	for (int i = 0; i < n; i++)
	{
		double maxEl = abs(matr[i][i]);
		int maxRow = i;
		for (int k = i + 1; k < n; k++)
		{
			if (abs(matr[k][i]) > maxEl)
			{
				maxEl = abs(matr[k][i]);
				maxRow = k;
			}
		}

		for (int k = i; k < n + 1; k++)
		{
			double temp = matr[maxRow][k];
			matr[maxRow][k] = matr[i][k];
			matr[i][k] = temp;
		}

		for (int k = i + 1; k < n; k++)
		{
			double c = -matr[k][i] / matr[i][i];
			for (int j = i; j < n + 1; j++)
			{
				if (i == j)
				{
					matr[k][j] = 0;
				}
				else {
					matr[k][j] += c * matr[i][j];
				}
			}
		}
	}

	Matrix result(1, n, 0);
	for (int i = n - 1; i >= 0; i--)
	{
		result[0][i] = matr[i][n] / matr[i][i];
		for (int k = i - 1; k >= 0; k--)
		{
			matr[k][n] -= matr[k][i] * result[0][i];
		}
	}
	return result;
}

double Matrix::IsNorma()
{
	double temp = 0;
	for (int j = 0; j < m; j++)
	{
		temp += matr[0][j] * matr[0][j];
	}
	return sqrt(temp);
}

void Matrix::deleteColumn(int ind)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = ind - 1; j < m - 1; j++)
		{
			*(*(matr + i) + j) = *(*(matr + i) + j + 1);
		}
	}
	--m;
}

double Matrix::scalMultiplication(Matrix &other)
{
	double temp = 0;
	for (int j = 0; j < m; j++)
		temp += matr[0][j] * other.matr[0][j];
	return temp;
}

Matrix Matrix::KachmagMethod()
{
	const double E = 0.0000000001;

	double *tempRow = getColumn(m);
	this->deleteColumn(m);
	Matrix free(1, m, 0);
	free.matr[0] = tempRow;

	tempRow = getRow(1);
	Matrix x(1, m, 0);
	x.matr[0] = tempRow;
	Matrix x1(1, m, 0);

	Matrix sub(1, m, 1);
	Matrix ai(1, m, 0);
	int j = 0;
	double temp;
	while (sub.IsNorma() > E)
	{
		tempRow = getRow(j + 1);
		ai.matr[0] = tempRow;
		temp = ((free.matr[0][j] - ai.scalMultiplication(x)) / (ai.IsNorma()*ai.IsNorma()));

		ai = ai * temp;
		x1 = x + ai;
		sub = x1 - x;

		x = x1;
		if (j < m - 1)
			j++;
		else j = 0;
	}
	return x;
}

double Matrix::findOversight(double &oversight)
{
	oversight = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < m; j++)
		{

			oversight += matr[i][j] * matr[i][j];
		}
	}
	oversight = sqrt(2 * oversight);
	return oversight;
}

void  Matrix::findMax(int & maxI, int& maxJ)
{
	double max = 0.0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (matr[i][j] > 0 && matr[i][j] > max)
			{
				max = matr[i][j];
				maxI = i;
				maxJ = j;
			}
			else if (matr[i][j] < 0 && -matr[i][j] > max)
			{
				max = -matr[i][j];
				maxI = i;
				maxJ = j;
			}
		}
	}
}

void Matrix::unitMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < m; j++)
		{

			*(*(matr + i) + j) = 0;
			*(*(matr + j) + i) = 0;
		}
		*(*(matr + i) + i) = 1;
	}
}

void Matrix::turnMatrix(const int& maxI, const int& maxJ, Matrix &other)
{
	other.unitMatrix();
	if (matr[maxI][maxI] == matr[maxJ][maxJ])
	{
		other.matr[maxI][maxI] = other.matr[maxJ][maxJ] = other.matr[maxJ][maxI] = sqrt(2.0) / 2.0;
		other.matr[maxI][maxJ] = -sqrt(2.0) / 2.0;
	}
	else
	{
		double  alpha = 0.5 * atan((2.0 * matr[maxI][maxJ]) / (matr[maxI][maxI] - matr[maxJ][maxJ]));
		other.matr[maxI][maxI] = other.matr[maxJ][maxJ] = cos(alpha);
		other.matr[maxI][maxJ] = -sin(alpha);
		other.matr[maxJ][maxI] = sin(alpha);
	}
}

Matrix Matrix::YakobyMethod()
{
	int maxI = 0, maxJ = 0;
	double oversight = 0.0;
	Matrix turnedMatrix(n, m, 0);
	Matrix temp(n, m, 0);
	double E = 0.00001;

	if (!isSimmetrial())
	{
		cout << "Матриця не симетрична";

	}
	else
	{
		findOversight(oversight);
		while (oversight > E)
		{
			findMax(maxI, maxJ);
			this->turnMatrix(maxI, maxJ, turnedMatrix);
			temp = ~turnedMatrix * (*this);
			*this = temp * turnedMatrix;
			this->findOversight(oversight);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (abs(matr[i][j]) < E)
				matr[i][j] = 0;

		}
	}
	return *this;
}