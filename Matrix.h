#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

class Matrix
{
public:
    Matrix();
    Matrix(int, int, int);              //кількість рядків, кількість стовпчиків, число-наповнювач матриці
    Matrix(const Matrix&);              
    Matrix(Matrix&&);                   
    ~Matrix();                         
    void setMatrix();                   //заповнення матриці з клавіатури
    void displayMatrix() const;         //вивід матриці на консоль
    int* getRow(int)const;              //доступ до рядка за індексом
    int* getColumn(int)const;           //доступ до стовпчика за індексом
    Matrix operator+ (const Matrix&)const;  //додавання матриць
	Matrix operator- (const Matrix&)const;  //віднімання матриць
    Matrix operator*(int)const;             //множення матриці на число
    Matrix operator*(const Matrix&)const;   //множення матриць
    Matrix& operator = (const Matrix&);     
    Matrix& operator = (Matrix&&);  
	friend ostream& operator << (ostream&, const Matrix&);
	friend istream& operator >> (istream&, Matrix&);
    bool operator== (const Matrix&)const;      //оператор порівняння
    int* operator[](int)const;                 //доступ до елемента за індексом
    Matrix& operator~ ();   //транспонування матриці

private:
    int** matr; 
    int n;      //кількість рядків
    int m;      //кількість стовпчиків
};