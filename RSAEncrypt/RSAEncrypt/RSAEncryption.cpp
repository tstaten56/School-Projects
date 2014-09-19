/*
Tera Staten   tns26   9/24/14
*/

#include "RSAEncryption.h"
#include <list>

RSAEncryption::RSAEncryption()
{
}

RSAEncryption::~RSAEncryption()
{
}

void RSAEncryption::setPhiN(BigInt p, BigInt q)
{
	phiN = (p - 1) * (q - 1);
}

void RSAEncryption::setN(BigInt p, BigInt q)
{
	n = (p * q);
}

void RSAEncryption::setN(string tempN)
{
	n = BigInt(tempN);
}

BigInt RSAEncryption::getN()
{
	return n;
}

BigInt RSAEncryption::ModInverse(string tempE, string tempP, string tempQ)
{
	setN(BigInt(tempP), BigInt(tempQ));
	setPhiN(BigInt(tempP), BigInt(tempQ));
	RSAEncryption::ExtEuclid(BigInt(tempE), phiN);
	if (!x.GetIsPositive())
	{
		x = phiN + x;
	}
	return (u + phiN) % phiN;
}

void RSAEncryption::ExtEuclid(BigInt a, BigInt m)
{
	BigInt tempX(0);
	BigInt tempY(1);
	BigInt u(1);
	BigInt v(0);
	BigInt b(m);
	while (a != 0)
	{
		BigInt q(b / a);
		BigInt temp1(b % a);
		BigInt temp2(tempX - (u * q));
		BigInt temp3(tempY - (v * q));
		b = a;
		a = temp1;
		tempX = u;
		tempY = v;
		u = temp2;
		v = temp3;
	}
	if (!tempX.GetIsPositive())
	{
		x = a + tempX;
	}
	else
	{
		x = tempX;
	}
	y = tempY; 
	gcdNum = b;
}

void RSAEncryption::outputXY()
{
	cout << "(x, y): (" << x << ", " << y << ")." << endl;
}

void RSAEncryption::outputDN()
{
	cout << "(d, n): (" << x << ", " << n << ")." << endl;
}

BigInt RSAEncryption::MessageToInt(BigInt e, string n, string message)
{
	setN(n);
	int m = int(message[0]);
	BigInt temp(m);
	//int count = 1;
	for (int count = 1; count < message.length(); count++) //when length() is 1 we don't want to get into the loop
	{
		temp = (temp * 128) + int(message[count]);
		//m = m * 128 + int(message[count]);
	}
	BigInt msg;
	msg = BigInt::modExp(temp, e, getN());
	if (msg > getN())
	{
		throw new invalid_argument("Message cannot be bigger than n, choose a smaller message please.");
	}
	return msg;
}

string RSAEncryption::IntToMessage(BigInt d, string n, BigInt num) //4 characters per message for now
{
	setN(n);
	num = BigInt::modExp(num, d, getN());
	bool large = true;
	BigInt letter(0);
	int msgASCII;
	string msg;
	while (large)
	{
		letter = (num % 128);
		msgASCII = letter.GetInt();
		
		msg += static_cast<char>(msgASCII); //save letter
		num = (num / 128); //getting rid of the letter
		if (num < 64)
		{
			large = false;
		}
	}
	//Reversing the string and returning message
	return string(msg.rbegin(), msg.rend());
}

void messageConvertTests()
{
	RSAEncryption ex;
	BigInt test(ex.MessageToInt(BigInt(79), "3337", "Z"));
	cout << test << " is the message as an integer" << endl;
	cout << ex.IntToMessage(BigInt(1019), "3337", test) << " should be Z" << endl;

	BigInt test2(ex.MessageToInt(BigInt(173), "40913", "CA"));
	cout << test2 << " is the message as an integer" << endl;
	cout << ex.IntToMessage(BigInt(11237), "40913", test2) << " should be CA" << endl;
}

void modInverseTests()
{
	RSAEncryption ex;
	ex.ModInverse("54", "23", "67");
}

void rsaEncryptionTests()
{
	messageConvertTests();
	modInverseTests();
}

//int main(int argc, char *argv[]) {
//   rsaEncryptionTests();    
//   return 0;
//}