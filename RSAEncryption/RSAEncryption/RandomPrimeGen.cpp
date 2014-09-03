#include "RandomPrimeGen.h"

RandomPrimeGen::RandomPrimeGen()
{
}

RandomPrimeGen::RandomPrimeGen(int len) : length(len)
{
	Initialize();
}

RandomPrimeGen::~RandomPrimeGen()
{
}

void RandomPrimeGen::Initialize()
{
	//Use length to represent the number of digits of the random number which also must be prime.
	//  if digits is 1   has to be between 1 - 9
	// if digits is 2 has to be between 10 - 99
	// if digits is 3 has to be between 100 - 999
	// if digits is 4 has to be between 1000 - 9999
	//  5 is 10000 - 99999
	//  6 is 100000 - 999999   etc
	// pattern:  1 * 10  and (9 * 10) +9 for 2
	// 1 * 100 and (9 * 100) + 99    3
	// 1 * 1000 and (9 * 1000) + 999    4
}

void RandomPrimeGen::FermatsTests()
{
	
}
