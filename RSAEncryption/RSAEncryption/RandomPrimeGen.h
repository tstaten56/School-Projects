
#ifndef RANDOMPRIMEGEN_H
#define RANDOMPRIMEGEN_H

#include "BigInt.h"
#include <time.h>

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
	void RandomPrimeGenTests();
	bool FermatsLittleTest(BigInt, BigInt);
	BigInt GenerateNum(BigInt, BigInt);
};

#endif