#include <iostream>
#include "head.h"
#include <cmath>

using namespace std;

Numbers::Numbers(int num, int input_step) {
	number = num;
	step = input_step;
	clearArr();
	convertArr();
}

Numbers Numbers::operator +(Numbers &num) const{
	Numbers res(*this);

	if (num.mass.size() >= res.mass.size()) {
		res.result = res.plus(num.number, res.number);
	}
	else {
		res.result = res.plus(res.number, num.number);
	}

	return res;
}

//Вспомогательная функция для сложения
int Numbers::plus(int n1, int n2) {
	int res = 0;
	int i = 0;
	int num = n1;
	int num2 = n2;
	int next = 0;

	while (num > 0) {
		int power = pow(10, i);
		int ost1 = num % 10;
		int ost2 = num2 % 10;
		int pr = ost1 + ost2 + next;
		res += pr % step*power;
		if (pr / step > 0) {
			next = 1;
		}
		else next = 0;
		num /= 10;
		num2 /= 10;
		i++;
	}

	return res;
}

Numbers Numbers::operator -(Numbers &num) const {
	Numbers res(*this);

	if (num.mass.size() >= res.mass.size()) {
		res.result = res.minus(num.number, res.number);
	}
	else {
		res.result = res.minus(res.number, num.number);
	}

	return res;
}

//Вспомогательная функция для вычитания
int Numbers::minus(int n1, int n2) {
	int res = 0;
	int i = 0;
	int num = n1;
	int num2 = n2;
	int next = 0;

	while (num > 0) {
		int power = pow(10, i);
		int ost1 = num % 10;
		int ost2 = num2 % 10;
		int pr = ost1 - ost2;
		if (ost2 > ost1) {
			pr += step;
			if (next == 1) {
				next = 2;
			} else next = 1;
		} else next = 0;
		pr -= next;
		res += pr * power;
		num /= 10;
		num2 /= 10;
		i++;
	}

	return res;
}

Numbers Numbers::operator *(Numbers &num) const {
	Numbers res(*this);

	if (num.mass.size() >= res.mass.size()) {
		res.result = res.umn(num.number, res.number);
	}
	else {
		res.result = res.umn(res.number, num.number);
	}

	return res;
}

//Вспомогательная функция для умножения
int Numbers::umn(int n1, int n2) {
	int ost = n2;
	int res = 0;
	int count = 0;

	while (ost > 0) {
		int power = pow(10, count);
		int ost1 = help(ost % 10, n1);
		res += ost1 * power;
		ost /= 10;
		count++;
	}

    return res;
}

//2 Вспомогательная функция для умножения
int Numbers::help(int n, int num) {
	int ost = num;
	int res = 0;
	int count = 0;
	int next = 0;

	while (ost > 0) {
		int power = pow(10, count);
		int ost1 = (ost % 10) * n;
		res += (ost1 % step+next)* power;
		next = ost1 / step;
		ost /= 10;
		count++;
	}

	return res;
}	

//Функция возведения в степень
Numbers Numbers::degree(Numbers &num, int power) {
	Numbers res;

	while (power != 0) {
		res.result = num.umn(num.number, num.number);
		power--;
	}

	return res;
}

//Функция деления
Numbers Numbers::del(Numbers &n, Numbers &r) {
	Numbers res;
	res.number = n.number;
	res.step = n.step;

	int n1 = n.numToTen();
	int r1 = r.numToTen();

	if (n1 > r1) {
		res.result = n1 / r1;
	} else res.result = r1 / n1;

	return res;
}

// Функция для перевода числа в десятичную систему счисления
int Numbers::numToTen() {
	int r=0;
	vector <int> mass2;
    convertArr2(mass2);
	int count = 0;

	for (auto const &element : mass2) {
		r += pow(step, count)*element;
		count++;
	}

	step = 10;
	result = r;

	return r;
}

// Функция для перевода числа в р-ичную систему счисления
int Numbers::numToStep(int input_step) {
	int r = 0;
	int count = 0;
	int num = number;
	int s = input_step;

	while (num > 0) {
		int ost = num % s;
		r += ost*pow(10, count);
		count++;
		num /= s;
	}

	step = s;
	result = r;

	return r;
}

// Функция проверки числа
bool Numbers::check() {
	bool c = 1;
	int count = 0;

	for (auto const &element : mass) {
		if (element > step - 1) {
			c = 0;
		}
	}

	if (c != 1) {
		cout << " Wrong number! ";
		return -3;
	}

	return c;
}

// Функция для создания вектора с числом
void Numbers::convertArr() {
	int num = number;
	int count = 10;

	while (num / count > 9) {
		count*=10;
	}

	while (count / 10 > 0) {
		int ost = num / count;
		num %= count;
		count /= 10;
		mass.push_back(ost);
	}

	int ost = num / count;
	mass.push_back(ost);
}

// Функция для создания вектора с числом, с цифрами в обратном порядке
void Numbers::convertArr2(vector <int>& mass2) {
	int power = mass.size();
	power = pow(10, power-1);

	int num = number;

	while (power > 0) {
		int ost = num % 10;
		num /= 10;
		mass2.push_back(ost);
		power /= 10;
	}
}

//Очищение вектора
void Numbers::clearArr() {
	if (!mass.empty()) {
		mass.clear();
	}
}

//Вспомогательная функция
void Numbers::arrToNum() {
	vector <int> mass2;
	convertArr2(mass2);
	number = 0;
	int i = 1;

	for (auto const &element : mass2) {
		number += i * element;
		i *= 10;
	}
}

void Numbers::setNum(int num) {
	number = num;
	clearArr();
	convertArr();
}

void Numbers::setStep(int s) {
	step = s;
}

int Numbers::returnNum() {
	return number;
}

int Numbers::returnStep() {
	return step;
}

int Numbers::returnRes() {
	return result;
}

//Функция вывода
void Numbers::write() {
	cout << " Input Data : " << number << " ; " << endl;
	cout << " Step : " << step << " ; " << endl;
	cout << " Output Data : " << result << " ; " << endl;
}
