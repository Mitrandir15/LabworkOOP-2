#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

class Matrix
{
public:
    Matrix();
    Matrix(int, int, double);              //������� �����, ������� ���������, �����-���������� �������
    Matrix(const Matrix&);              
    Matrix(Matrix&&);                   
    ~Matrix();                         
    double* getRow(int)const;              //������ �� ����� �� ��������
    double* getColumn(int)const;           //������ �� ��������� �� ��������
    Matrix operator+ (const Matrix&)const;  //��������� �������
	Matrix operator- (const Matrix&)const;  //�������� �������
    Matrix operator*(double)const;             //�������� ������� �� �����
    Matrix operator*(const Matrix&)const;   //�������� �������
    Matrix& operator = (const Matrix&);     
    Matrix& operator = (Matrix&&);  
	friend ostream& operator << (ostream&, const Matrix&); //���� ������� 
	friend istream& operator >> (istream&, Matrix&); //���������� ������� 
    bool operator== (const Matrix&)const;      //�������� ���������
	double* operator[](int);                 //������ �� �������� �� ��������
    Matrix& operator~ ();   //�������������� �������

	Matrix GaussMethod(Matrix);
	Matrix KachmagMethod(Matrix);

private:
    double** matr; 
    int n;      //������� �����
    int m;      //������� ���������
};