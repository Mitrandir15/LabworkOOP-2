#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

class Matrix
{
public:
    Matrix();
    Matrix(int, int, double);              //кількість рядків, кількість стовпчиків, число-наповнювач матриці
    Matrix(const Matrix&);              
    Matrix(Matrix&&);                   
    ~Matrix();                         
    double* getRow(int)const;              //доступ до рядка за індексом
    double* getColumn(int)const;           //доступ до стовпчика за індексом
    Matrix operator+ (const Matrix&)const;  //додавання матриць
	Matrix operator- (const Matrix&)const;  //віднімання матриць
    Matrix operator*(double)const;             //множення матриці на число
    Matrix operator*(const Matrix&)const;   //множення матриць
    Matrix& operator = (const Matrix&);     
    Matrix& operator = (Matrix&&);  
	friend ostream& operator << (ostream&, const Matrix&); //вивід матриці 
	friend istream& operator >> (istream&, Matrix&); //заповнення матриці 
    bool operator== (const Matrix&)const;      //оператор порівняння
	double* operator[](int);                 //доступ до елемента за індексом
    Matrix& operator~ ();   //транспонування матриці

	Matrix GaussMethod(Matrix);
	Matrix KachmagMethod(Matrix);

private:
    double** matr; 
    int n;      //кількість рядків
    int m;      //кількість стовпчиків
};