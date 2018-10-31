#include <iostream>
#include "Matrix.h"

Matrix::Matrix() : matr(nullptr), n(0), m(0)
{
}

Matrix::Matrix(int row, int column, int numb = 0) :n(row), m(column)
{
    matr = new int*[n];
    for (int i = 0; i < n; i++)
    {
        *(matr + i) = new int[m];
        for (int j = 0; j < m; j++)
        {
            *(*(matr + i) + j) = numb;
        }
    }
}

Matrix::Matrix(const Matrix& other) : n(other.n), m(other.m)
{
    matr = new int*[n];
    for (int i = 0; i < n; i++)
    {
        *(matr + i) = new int[m];
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
    matr = new int*[n];
    for (int i = 0; i < n; i++)
    {
        *(matr + i) = new int[m];
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
        delete[] *(matr + i);
    }
    delete [] matr;
}

void Matrix::setMatrix()
{
    cout << "Введіть розмір матриці: рядків  "; 
	cin >> n; 
	cout << " стовпчиків "; 
	cin >> m;
    matr = new int*[n];
    for (int i = 0; i < n; i++)
    {
        *(matr + i) = new int[m];
        for (int j = 0; j < m; j++)
        {
            cout << "Елемент " << i + 1 << " рядка, " << j + 1 << "стовпчика ";
            cin >> *(*(matr + i) + j);
        }
    }

}

void Matrix::displayMatrix()const
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(4) << *(*(matr + i) + j);
        }
        cout << endl;
    }
}

int* Matrix::getRow(int ind)const
{
    int* row = new int[m];
    for (int i = 0; i < m; i++)
    {
        *(row + i) = *(*(matr + ind - 1) + i);
    }
    return row;
}

int* Matrix::getColumn(int ind)const
{
    int* column = new int[n];
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
        result.matr = new int*[n];
        for (int i = 0; i < n; i++)
        {
            *(result.matr + i) = new int[m];
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
		result.matr = new int*[n];
		for (int i = 0; i < n; i++)
		{
			*(result.matr + i) = new int[m];
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

Matrix Matrix::operator* (int numb) const
{
    Matrix result(n, m);
    result.matr = new int*[n];
    for (int i = 0; i < n; i++)
    {
        *(result.matr + i) = new int[m];
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
        int counter = m, ttl = 0;
        Matrix result(n, other.m);
        int *row;
        int *column;
        result.matr = new int*[n];
        for (int i = 0; i < n; i++)
        {
            *(result.matr + i) = new int[other.m];
            for (int j = 0; j < other.m; j++)
            {
                row = getRow(i + 1);
                column = other.getColumn(j + 1);
                for (int k = 0; k < counter; k++)
                {
                    ttl += (row[k] * column[k]);
                }
                *(*(result.matr + i) + j) = ttl;
                ttl = 0;
            }
        }
        return result;
    }
    else
    {
        cout << m << "   " << other.n;
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
        matr = new int*[n];
        for (int i = 0; i < n; i++)
        {
            *(matr + i) = new int[m];
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
int* Matrix::operator[](int i)const
{
    return getRow(i);
}

Matrix& Matrix::operator~()
{
    Matrix result(m, n);
    int *column;
    result.matr = new int*[m];
    for (int i = 0; i < m; i++)
    {
        column = this->getColumn(i + 1);
        *(result.matr + i) = new int[n];
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
			cout << setw(4) << *(*(matrix.matr + i) + j);
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
	matrix.matr = new int*[matrix.n];
	for (int i = 0; i < matrix.n; i++)
	{
		*(matrix.matr + i) = new int[matrix.m];
		for (int j = 0; j < matrix.m; j++)
		{
			cout << "Елемент " << i + 1 << " рядка, " << j + 1 << "стовпчика ";
			cin >> *(*(matrix.matr + i) + j);
		}
	}

	return input;
}