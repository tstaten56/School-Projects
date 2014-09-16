#include "RandomPrime.h"

RandomPrime::RandomPrime()
{
}

RandomPrime::RandomPrime(int len) : length(len)
{
	Initialize();
}

RandomPrime::~RandomPrime()
{
}

void RandomPrime::Initialize()
{
	srand(time(NULL));

	//Use length to represent the number of digits of the random number which also must be prime.
	//  if digits is 1   has to be between 1 - 9
	// if digits is 2 has to be between 10 - 99
	// if digits is 3 has to be between 100 - 999
	// if digits is 4 has to be between 1000 - 9999

	//Determining the range that the random prime must be located
	//BigInt first = 1;
	//BigInt second = 9;
	//BigInt randNum = 0;
	//for (int i = 1; i < length; i++)
	//{
	//	first = first * 10;
	//	second = second + (first * 9);
	//}
	//second = second - first; //For our range
	//for (int i = 1; i <= 10; i++)
	//{
	//	//BigInt randNum(static_cast<BigInt>(rand()) % (second - first) + first);

	//}
	//Second way: Find one random number and add it to the rest of them for the number of length
	num.clear();
	//First digit is non-zero
	unsigned char randNonZero(static_cast<unsigned char>((rand()) % 9) + 1);
	num = num.push(randNonZero);
	if (length > 1)
	{
		for (int i = 2; i < this->length; i++)
		{
			unsigned char randDigit(static_cast<unsigned char>(rand()) % 9);
			num = num.push(randDigit);

		}
		//Last digit needs to be odd
		bool even = true;
		while (even)
		{
			int randInt(rand() % 9);
			if ((randInt % 2) != 0)
			{
				even = false;
				num = num.push(static_cast<unsigned char>(randInt));
			}
		}
	}
	//BigInt modExp(BigInt const& base, BigInt exponent, BigInt const& mod);
	//use fermat's little test

}

bool RandomPrime::FermatsLittleTest()
{ //If true then we have a prime!
	BigInt arr[5] { 2, 3, 5, 7, 11 }; //These are the A's I have chosen
	for (int i = 0; i < 5; i++)
	{
		if (num.modExp(arr[i], num - 1, num) != 1) {
			cout << "modExp answer: " << num.modExp(arr[i], num - 1, num) << endl;
			return false;
		}
	}
	return true;
}

BigInt RandomPrime::getNum()
{
	return this->num;
}

void GenerateNumTests()
{
	bool notPrime = true;
	RandomPrime ex(1); //Change number here for digits of prime
	while (notPrime)
	{
		ex.Initialize();
		cout << "Number: " << ex.getNum() << " ";
		if ((ex.getNum() % 2) == 0)
		{
			cout << "Number is not prime, it is even!" << endl;
		}
		if ((ex.getNum() < 0)) //Change these to be accurate!!
		{
			cout << "Number is too small, out of bounds!" << endl;
		}
		else if (ex.getNum() >9)
		{
			cout << "Number is too large, out of bounds!" << endl;
		}
		if (ex.FermatsLittleTest())
		{
			cout << "This number is prime!" << endl;
			break;
		}
	}

	int pause;
	cin >> pause;
}

void RandomPrimeTests()
{
	GenerateNumTests();
}
//
//int main(int argc, char *argv[]) {
//   RandomPrimeTests();    
//   //list<unsigned char> listed;
//   //listed.push_front(0);
//   //listed.pop_front();
//   return 0;
//}