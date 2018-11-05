#include <iostream>
#include <Windows.h>
#include "Matrix.h"

using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Matrix a, b;
	cin >> a; cout << endl;
	cin >> b; cout << endl;
	cout << a << endl << b << endl << a * b << endl;
	system("pause");
}