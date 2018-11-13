#include <iostream>
#include <Windows.h>
#include "Matrix.h"

using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Matrix a;
	//a.MakeHilbertMatrix();
	cin >> a; cout << endl;
	cout << a << endl; 
	cout << a.GaussMethod() << endl;
	system("pause");
}