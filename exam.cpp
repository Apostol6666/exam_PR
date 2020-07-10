#include <iostream>
#include "head.h"
#include <math.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Numbers num;
	num.setNum(1050);
	num.setStep(7);

	Numbers num2;
	num2.setNum(20);
	num2.setStep(7);

	Numbers result;

	cout << " Сложение : " << endl;
	result = num + num2;
	result.write();
	cout << endl;

	cout << " Вычитание: " << endl;
	result = num - num2;
	result.write();
	cout << endl;

	cout << " Умножение : " << endl;
	result = num * num2;
	result.write();
	cout << endl;

	cout << " Степень : " << endl;
	result = num.degree(num, 3);
	result.write();
	cout << endl;

	cout << " Деление : " << endl;
	Numbers fordel1(1800, 7);
	Numbers fordel2(30, 7);
	result = fordel1.del(fordel1, fordel2);
	result.write();
	cout << endl;

	num.convertArr();

	cout << " Перевод в 10-чную систему счисления : " << endl;
	num.numToTen();
	cout << endl;

	cout << " Перевод в 5-чную систему счисления : " << endl;
	num.numToStep(5);
	cout << endl;

	cout << " Проверка : " << endl;
	num.check();

	cout << endl;
	num.write();

	return 0;
}
