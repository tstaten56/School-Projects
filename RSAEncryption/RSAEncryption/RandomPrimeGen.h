#pragma once
#ifndef RANDOMPRIMEGEN_H
#define RANDOMPRIMEGEN_H

#include "BigInt.h"

class RandomPrimeGen
{
private:
	int length;
	BigInt num;
public:
	RandomPrimeGen();
	RandomPrimeGen(int);
	~RandomPrimeGen();
	void Initialize();
	void FermatsTests();
};

#endif