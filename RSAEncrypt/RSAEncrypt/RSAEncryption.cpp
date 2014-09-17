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

BigInt RSAEncryption::ModInverse(string tempE, string tempP, string tempQ)
{
	//BigInt p(tempP);
	//BigInt q(tempQ);
	//setPhiN(p, q);
	//BigInt a(phiN);
	//BigInt m(tempE);
	//BigInt tempX(0);
	//BigInt tempY(1);
	//BigInt u(1);
	//BigInt v(0);
	//BigInt b(m);
	//while (a != 0)
	//{
	//	BigInt q(b / a);
	//	BigInt temp1(b % a);
	//	BigInt temp2(tempX - (u * q));
	//	BigInt temp3(tempY - (v * q));
	//	b = a;
	//	a = temp1;
	//	tempX = u;
	//	tempY = v;
	//	u = temp2;
	//	v = temp3;
	//}
	setN(BigInt(tempP), BigInt(tempQ));
	setPhiN(BigInt(tempP), BigInt(tempQ));
	RSAEncryption::ExtEuclid(BigInt(tempE), phiN);
	if (!x.GetIsPositive())
	{
		x = phiN + x;
	}
	//else
	//{
	//	x = tempX;
	//}
	////y = tempY; Shouldn't need this
	//gcdNum = b;
	return (u + phiN) % phiN;
}

void RSAEncryption::ExtEuclid(BigInt a, BigInt m)
{
	//BigInt p(tempP);
	//BigInt q(tempQ);
	//setPhiN(a);
	//BigInt a(phiN);
	//BigInt m(tempE);
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

BigInt RSAEncryption::MessageToInt(string message)
{
	int m = int(message[0]);
	BigInt msg(m);
	//int count = 1;
	for (int count = 1; count < message.length(); count++) //when length() is 1 we don't want to get into the loop
	{
		msg = (msg * 128) + int(message[count]);
		//m = m * 128 + int(message[count]);
	}
	return msg;
}

string RSAEncryption::IntToMessage(BigInt num) //4 characters per message for now
{
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
	cout << ex.MessageToInt("LAST") << "= 160459220" << endl;
	BigInt test(160459220);
	cout << ex.IntToMessage(test) << "= LAST" << endl;
	cout << ex.MessageToInt("HELLOIAMTERA") << endl;
	BigInt test2(ex.MessageToInt("HELLOIAMTERA"));
	//Takes a while since this is not split up
	cout << ex.IntToMessage(test2) << "=HELLOIAMTERA" << endl;
	int pause;
	cin >> pause;
}

void modInverseTests()
{
	RSAEncryption ex;
	ex.ModInverse("54", "23", "67");
}

void rsaEncryptionTests()
{
	//messageConvertTests();
	modInverseTests();
}

//int main(int argc, char *argv[]) {
//   rsaEncryptionTests();    
//   return 0;
//}