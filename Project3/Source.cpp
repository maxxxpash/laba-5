#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

double trapezoid_formula(double (*f)(double), double a, double b, double E);
double Simpson_method(double (*f)(double), double a, double b, double E);
double Simpsons_Cubature_Formula(double f(double, double), double a, double b, double c, double d, double E);

double integral(double x);
double integralXY(double x, double y);

int main()
{
	setlocale(LC_ALL, "Rus");
	double a = 0.6;
	double b = 1.724;
	cout << "Метод трапеции при E = 1e-6: " << endl;
	double integralfx = trapezoid_formula(integral, a, b, 1e-6);
	cout << "Метод Симпсона при E = 1e-6: " << endl;
	integralfx = Simpson_method(integral, a, b, 1e-6);
	cout << "Кубатурная формула Симпсона при E = 1e-6: " << endl;
	a = 0;
	b = 4.0;
	double c = 1.0;
	double d = 2.0;
	integralfx = Simpsons_Cubature_Formula(integralXY, a, b, c, d, 1e-6);
	system("pause");
	return 0;
}

double trapezoid_formula(double(*f)(double), double a, double b, double E)
{
	// вычисление интеграла при n = 2
	int n = 2;
	double x = a;
	double h = (b - a) / n;
	double I_h = (f(a) + f(b)) / 2;
	int k = 0;
	for (int i = 1; i < n; i++)
	{
		x += h;
		I_h += f(x);
	}
	I_h *= h;
	k++;
	cout << "k= " << k << setw(10) << "n= " << n << setw(10) << "I= " << setprecision(10) << I_h << endl;
	// вычисление интеграла при n = 4
	n = 4;
	x = a;
	h = (b - a) / n;
	double I_h2 = (f(a) + f(b)) / 2;
	for (int i = 1; i < n; i++)
	{
		x += h;
		I_h2 += f(x);
	}
	I_h2 *= h;
	k++;
	cout << "k= " << k << setw(10) << "n= " << n << setw(15) << "I= " << setprecision(10) << I_h2 << endl;
	while (abs(I_h2 - I_h) > 3 * E)
	{
		I_h = I_h2;
		x = a;
		n *= 2;
		h = (b - a) / n;
		I_h2 = (f(a) + f(b)) / 2;
		for (int i = 1; i < n; i++)
		{
			x += h;
			I_h2 += f(x);
		}
		I_h2 *= h;
		k++;
		cout << "k= " << k << setw(10) << "n= " << n << setw(15) << "I= " << setprecision(10) << I_h2 << endl;
	}
	return I_h2;
}
double Simpson_method(double(*f)(double), double a, double b, double E)
{
	// вычисление интеграла при n = 1
	int n = 1;
	double x = a;
	double h = (b - a) / (2 * n);
	double I_h = f(x);
	int k = 0;
	for (int i = 1; i < 2 * n; i++)
	{
		x += h;
		if (i % 2 == 0)
		{
			I_h += 2 * f(x);
		}
		else
		{
			I_h += 4 * f(x);
		}
	}
	x += h;
	I_h += f(x);
	I_h *= h / 3;
	k++;
	cout << "k= " << k << setw(10) << "n= " << n << setw(10) << "I= " << setprecision(10) << I_h << endl;
	// вычисление интеграла при n = 2
	n = 2;
	x = a;
	h = (b - a) / (2 * n);
	double I_h2 = f(x);
	for (int i = 1; i < 2 * n; i++)
	{
		x += h;
		if (i % 2 == 0)
		{
			I_h2 += 2 * f(x);
		}
		else
		{
			I_h2 += 4 * f(x);
		}
	}
	x += h;
	I_h2 += f(x);
	I_h2 *= h / 3;
	k++;
	cout << "k= " << k << setw(10) << "n= " << n << setw(10) << "I= " << setprecision(10) << I_h2 << endl;
	while (abs(I_h2 - I_h) > 15 * E)
	{
		I_h = I_h2;
		n *= 2;
		x = a;
		h = (b - a) / (2 * n);
		I_h2 = f(x);
		for (int i = 1; i < 2 * n; i++)
		{
			x += h;
			if (i % 2 == 0)
			{
				I_h2 += 2 * f(x);
			}
			else
			{
				I_h2 += 4 * f(x);
			}
		}
		x += h;
		I_h2 += f(x);
		I_h2 *= h / 3;
		k++;
		cout << "k= " << k << setw(10) << "n= " << n << setw(10) << "I= " << setprecision(10) << I_h2 << endl;
	}
	return I_h2;
}
double Simpsons_Cubature_Formula(double(*f)(double, double), double a, double b, double c, double d)
{
	double integral1 = 0;
	int n, m;
	cout << "Введите N: ";
	cin >> n;
	cout << "Введите M: ";
	cin >> m;
	double hx = (b - a) / (2 * n),
		hy = (d - c) / (2 * m);
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			double x2 = a + (2 * i) * hx,
				y2 = c + (2 * j) * hy,
				x2_1 = x2 + hx,
				x2_2 = x2_1 + hx,
				y2_1 = y2 + hy,
				y2_2 = y2_1 + hy;
			integral1 += f(x2, y2) + 4 * f(x2_1, y2) + f(x2_2, y2) + 4 * f(x2, y2_1) + 16 * f(x2_1, y2_1);
			integral1 += 4 * f(x2_2, y2_1) + f(x2, y2_2) + 4 * f(x2_1, y2_2) + f(x2_2, y2_2);
		}
	}
	integral1 *= hx * hy / 9;
	k++;
	cout << "k= " << k << setw(10) << "n =" << n << setw(10) << "I= " << integral1 << setprecision(10) << endl;

	return integral1;
}


double integral(double x)
{
	return pow((x + pow(x, 3)), 0.5);
}
double integralXY(double x, double y)
{
	int k = 0;
	double a = 0.5 + 0.1 * k, b = 0.5 + 0.1 * k;
	return (pow(x, 2) / (1 + pow(y, 2)));
}
//реферат-общая характеристика
//своими словами особенности метода, и о самом методе, стр на метод