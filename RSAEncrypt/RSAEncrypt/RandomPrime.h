#pragma once
#ifndef RANDOMPRIMEGEN_H
#define RANDOMPRIMEGEN_H

#include "BigInt.h"
#include <time.h>

class RandomPrime
{
private:
	int length;
	BigInt num;
public:
	RandomPrime();
	RandomPrime(int);
	~RandomPrime();
	void Initialize();
	bool FermatsLittleTest();
	BigInt getNum();
};

#endif