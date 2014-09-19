/*
Tera Staten   tns26   9/24/14
*/

#include <iostream>
#include <string>
#include "RandomPrime.h"
#include "RSAEncryption.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc == 1 || argc>5) {
		cout << "Wrong input format!";
		exit(1);
	}
	if (argc == 2) {   //s
		BigInt size2 = atoi(argv[1]);
		cout << flush;
		cout << "size of the prime: " << size2 << endl;
		//call your random prime generator ...
		int size = atoi(argv[1]);

		RandomPrime rand(size);
		cout << "Your random prime: " << rand.getNum() << endl;
		int pause;
		cin >> pause;
	}
	if (argc == 3) {   //a b
		string a = argv[1];
		string b = argv[2];
		cout << "a=" << a << ", b=" << b << endl;
		//call your Extended Euclidean Algorithm ...
		RSAEncryption ex;
		//BigInt bigA(a);
		//BigInt bigB(b);
		ex.ExtEuclid(BigInt(a), BigInt(b));
		ex.outputXY();
		int pause;
		cin >> pause;
	}
	if (argc == 4) {   //e p q
		string e = argv[1];
		string p = argv[2];
		string q = argv[3];
		cout << "e=" << e << ", p=" << p << ", q=" << q << endl;
		//call your mod inverse func ...
		RSAEncryption ex;
		ex.ModInverse(e, p, q);
		ex.outputDN();
		int pause;
		cin >> pause;
	}
	if (argc == 5) {    //'e' e n message
		if (argv[1][0] == 'e') {
			string e = argv[2];
			string n = argv[3];
			string m = argv[4];
			cout << "e=" << e << ", n=" << n << ", message=" << m << endl;
			//call your RSA encryption ...
			RSAEncryption ex;
			cout << ex.MessageToInt(BigInt(e), n, m) << endl;
		}
		else if (argv[1][0] == 'd'){    //'d' d n message
			string d = argv[2];
			string n = argv[3];
			string m = argv[4];
			cout << "d=" << d << ", n=" << n << ", message=" << m << endl;
			//call your RSA decryption ...
			RSAEncryption ex;
			cout << ex.IntToMessage(BigInt(d), n, BigInt(m));
		}
		int pause;
		cin >> pause;
	}

	return 0;
}

