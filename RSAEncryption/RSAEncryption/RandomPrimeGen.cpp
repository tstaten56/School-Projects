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
	srand(time(NULL));

	//Use length to represent the number of digits of the random number which also must be prime.
	//  if digits is 1   has to be between 1 - 9
	// if digits is 2 has to be between 10 - 99
	// if digits is 3 has to be between 100 - 999
	// if digits is 4 has to be between 1000 - 9999

	//Determining the range that the random prime must be located
	BigInt first = 1;
	BigInt second = 9;
	for (int i = 1; i < length; i++)
	{
		first = first * 10;
		second = second + (first * 9);
	}
	second = second - first; //For our range
	for (int i = 1; i <= 10; i++)
	{
		BigInt randNum(static_cast<BigInt>(rand()) %(second - first) + first);
		
	}
	//BigInt modExp(BigInt const& base, BigInt exponent, BigInt const& mod);
	//use fermat's little test

}

bool RandomPrimeGen::FermatsLittleTest(BigInt a, BigInt p)
{
	//  a^p - a must be divisible by p
	//if (a.modExp(a, p, p) != 0))
	//{

	//}
	return true;
}

BigInt RandomPrimeGen::GenerateNum(BigInt first, BigInt second)
{
	BigInt randNum;
	//for (int i = 1; i <= 10; i++)
	//{
		randNum = static_cast<BigInt>(rand()) % (second - first) + first;

	//}
	return randNum;
}

void GenerateNumTests()
{
	//Tested 1-10, 100-999, 1000-9999
	BigInt firstDig(1000);
	BigInt secondDig(9999);
	BigInt testNum;
	RandomPrimeGen ex; 
	for (int i = 0; i < 20; i++)
	{
		testNum = ex.GenerateNum(firstDig, secondDig);
		if ((firstDig <= testNum) && (testNum <= secondDig)) //Correct just output the random number
		{
			cout << testNum << endl;
		}
		else
		{
			cout << firstDig << "<=" << testNum << "<=" << secondDig << "Incorrect!" << endl; //Wrong
		}
	}
	int dumb;
	cin >> dumb;
}

void RandomPrimeGen::RandomPrimeGenTests()
{
	GenerateNumTests();
}
