#ifndef _RATION_H
#define _RATION_H

#include "head.h"

using namespace std;

class Rations : public Numbers {
private:
	int numer, denom, gen_ost;
public: 
	Rations() {}
	Rations(int num, int den, int input_step);

	Rations rationToStep(int input_step);
	int ostToTen(int ost);
	int ostToStep(int o);

	void write();
};

#endif
