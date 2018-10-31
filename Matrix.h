#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

class Matrix
{
public:
    Matrix();
    Matrix(int, int, int);              //������� �����, ������� ���������, �����-���������� �������
    Matrix(const Matrix&);              
    Matrix(Matrix&&);                   
    ~Matrix();                         
    void setMatrix();                   //���������� ������� � ���������
    void displayMatrix() const;         //���� ������� �� �������
    int* getRow(int)const;              //������ �� ����� �� ��������
    int* getColumn(int)const;           //������ �� ��������� �� ��������
    Matrix operator+ (const Matrix&)const;  //��������� �������
	Matrix operator- (const Matrix&)const;  //�������� �������
    Matrix operator*(int)const;             //�������� ������� �� �����
    Matrix operator*(const Matrix&)const;   //�������� �������
    Matrix& operator = (const Matrix&);     
    Matrix& operator = (Matrix&&);  
	friend ostream& operator << (ostream&, const Matrix&);
	friend istream& operator >> (istream&, Matrix&);
    bool operator== (const Matrix&)const;      //�������� ���������
    int* operator[](int)const;                 //������ �� �������� �� ��������
    Matrix& operator~ ();   //�������������� �������

private:
    int** matr; 
    int n;      //������� �����
    int m;      //������� ���������
};