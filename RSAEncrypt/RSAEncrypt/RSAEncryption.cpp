#include "RSAEncryption.h"
#include <list>

RSAEncryption::RSAEncryption()
{
}


RSAEncryption::~RSAEncryption()
{
}

BigInt RSAEncryption::ModInverse(string tempE, string tempP, string tempQ)
{
	BigInt e(tempE);
	BigInt p(tempP);
	BigInt q(tempQ);
	BigInt n(p * q);
	BigInt circleN((p - 1)*(q - 1));
	return n;
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

void rsaEncryptionTests()
{
	messageConvertTests();
}

//int main(int argc, char *argv[]) {
//   rsaEncryptionTests();    
//   return 0;
//}