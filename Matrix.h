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
	void unitMatrix();
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
	Matrix operator~ ();   //транспонування матриці

	void MakeHilbertMatrix();
	double Norma();
	double scalMultiplication(Matrix&); //скалярний добуток
	void deleteColumn(int ind); // видалити стовпчик

	bool isSimmetrial();
	double findOversight(double&);
	void  findMax(int&, int&);
	void rotateMatrix(const int&, const int&, Matrix&);

	Matrix GaussMethod();
	Matrix KachmagMethod();
	Matrix YakobyMethod();

private:
	double** matr;
	int n;      //кількість рядків
	int m;      //кількість стовпчиків
};