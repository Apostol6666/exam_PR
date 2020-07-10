#include <iostream>
#include "head.h"
#include "ration.h"
#include <cmath>

using namespace std;


Rations::Rations(int num, int den, int input_step) {
	numer = num;
	denom = den;
	setStep(input_step);
	setNum(numer/returnStep());
}

Rations Rations::rationToStep(int input_step) {
	Rations res(*this);
	res.setNum(res.numToTen());
	res.numToStep(input_step);
	int result = res.returnRes();

	int ost = numer % denom;
	gen_ost = ostToTen(ost);
	gen_ost = ostToStep(gen_ost);

	return res;
}

int Rations::ostToTen(int ost) {
	int o = ost;
	int count = 0;
	int r = 0;
	int i = -1;

	while (ost / 10 > 0) {
		count++;
		ost %= 10;
	}

	while (count > 0) {
		int power = pow(10, count);
		o %= power;
	    int num = pow(o/power, i);
		r += num;
		i--;
		count--;
	}

	return r;
}

int Rations::ostToStep(int o) {
	int ost = o;
	int res = 0;
	int s = returnStep();
	int count = 0;

	while (ost / 10 > 0) {
		ost %= 10;
		count++;
	}

	ost = o;
	while (count > 0) {
		int power = pow(10, count);
		ost *= s;
		res += (ost / s)*power;
		ost %= s;
		count--;
	}

	return res;
}

void Rations::write() {
	cout << endl;
	cout << "Начальная дробь :" << endl;
	cout << "Целая часть - " << (numer/denom) << endl; 
	cout << "Дробная часть - " << (numer % denom) << endl;
	cout << "Знаменатель - " <<  denom << endl;

	cout << endl;

	cout << "Конечная дробь :" << endl;
	cout << "Целая часть - " << returnRes() << endl;
	cout << "Дробная часть - " << gen_ost << endl;
	cout << "Знаменатель - " << denom << endl;
	cout << "Система счисления - " << returnStep() << endl;
	cout << endl;
}

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

Numbers Numbers::degree(Numbers &num, int power) {
	Numbers res;

	while (power != 0) {
		res.result = num.umn(num.number, num.number);
		power--;
	}

	return res;
}

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
		return 0;
	}

	return c;
}

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

void Numbers::clearArr() {
	if (!mass.empty()) {
		mass.clear();
	}
}

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

void Numbers::setResult(int r) {
	result = r;
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

void Numbers::write() {
	cout << " Input Data : " << number << " ; " << endl;
	cout << " Step : " << step << " ; " << endl;
	cout << " Output Data : " << result << " ; " << endl;
}
