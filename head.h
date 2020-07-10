#ifndef _NUMBER_H
#define _NUMBER_H

#include <vector>

using namespace std;

class Numbers {
private:
	int number, step, result;
	vector<int> mass;

public:
	Numbers() {}
	Numbers(int num, int input_step);
	void setNum(int num);
	void setStep(int s);
	
	bool check();
	void convertArr();
	void convertArr2(vector <int>& mass2);
	void clearArr();

	Numbers operator +(Numbers &num) const;
	int plus(int n1, int n2);

	Numbers operator -(Numbers &num) const;
	int minus(int n1, int n2);

	Numbers operator *(Numbers &num) const;
	int umn(int n1, int n2);
	int help(int n , int num);

	Numbers degree(Numbers &num, int power);
	Numbers del(Numbers &n, Numbers &r);

	int numToTen();
	int numToStep(int input_step);
	void arrToNum();

	int returnNum();
	int returnStep();
	int returnRes();
	void write();
};

#endif
