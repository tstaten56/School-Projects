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
	//Find one random number and add it to the rest of them for the number of length
	bool notPrime = true;
	while (notPrime)
	{
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
		notPrime = !FermatsLittleTest();
	}	
}

bool RandomPrime::FermatsLittleTest()
{ //If true then we have a prime!
	BigInt arr[5] { 2, 3, 5, 7, 11 }; //These are the A's I have chosen
	if (num < 12) 
	{
		//Need this check to compare to our A's
		if ((num == 2) || (num == 3) || (num == 5) || (num == 7) || (num == 11))
		{
			return true;
		}
	}
	for (int i = 0; i < 5; i++) //Change this loop to test less A's if time is taking too long!
	{							//Works like a charm for i < 2
		BigInt ans(num.modExp(arr[i], num - 1, num));
		if (ans != 1) {
			//cout << "modExp answer != 1: " << ans << endl;
			return false;
		}
	}
	//cout << "modExp answer is == 1 " << ans << endl;
	return true;
}

BigInt RandomPrime::getNum()
{
	return this->num;
}

void GenerateNumTests()
{
	bool notPrime = true;
	RandomPrime ex(2); //Change number here for digits of prime
	while (notPrime)
	{
		ex.Initialize();
		cout << "Number: " << ex.getNum() << " ";
		//if ((ex.getNum() % 2) == 0)
		//{
		//	cout << " is not prime, it is even!" << endl;
		//}
		//if ((ex.getNum() < 10)) //Change these to be accurate!!
		//{
		//	cout << " is too small, out of bounds!" << endl;
		//}
		//else if (ex.getNum() > 99)
		//{
		//	cout << " is too large, out of bounds!" << endl;
		//}
		if (ex.FermatsLittleTest())
		{
			cout << " is prime!" << endl;
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

//int main(int argc, char *argv[]) {
//   RandomPrimeTests();    
//   //list<unsigned char> listed;
//   //listed.push_front(0);
//   //listed.pop_front();
//   return 0;
//}