//#include <iostream>
//#include <string>
//#include "RandomPrime.h"
//#include "RSAEncryption.h"
//using namespace std;
//
//int main(int argc, char *argv[])
//{
//	if (argc == 1 || argc>5) {
//		cout << "Wrong input format!";
//		exit(1);
//	}
//	if (argc == 2) {   //s
//		BigInt size2 = atoi(argv[1]);
//		cout << flush;
//		cout << "size of the prime: " << size2 << endl;
//		//call your random prime generator ...
//		int size = atoi(argv[1]);
//
//		RandomPrime rand(size);
//		cout << "Your random prime: " << rand.getNum() << endl;
//		int pause;
//		cin >> pause;
//	}
//	if (argc == 3) {   //a b
//		string a = argv[1];
//		string b = argv[2];
//		cout << "a=" << a << ", b=" << b << endl;
//		//call your Extended Euclidean Algorithm ...
//		RSAEncryption ex;
//		//BigInt bigA(a);
//		//BigInt bigB(b);
//		ex.ExtEuclid(BigInt(a), BigInt(b));
//		ex.outputXY();
//		int pause;
//		cin >> pause;
//	}
//	if (argc == 4) {   //e p q
//		string e = argv[1];
//		string p = argv[2];
//		string q = argv[3];
//		cout << "e=" << e << ", p=" << p << ", q=" << q << endl;
//		//call your mod inverse func ...
//		RSAEncryption ex;
//		ex.ModInverse(e, p, q);
//		ex.outputDN();
//		int pause;
//		cin >> pause;
//	}
//	if (argc == 5) {    //'e' e n message
//		if (argv[1][0] == 'e') {
//			string e = argv[2];
//			string n = argv[3];
//			string m = argv[4];
//			cout << "e=" << e << ", n=" << n << ", message=" << m << endl;
//			//call your RSA encryption ...
//			RSAEncryption ex;
//			cout << ex.MessageToInt(BigInt(e), n, m) << endl;
//		}
//		else if (argv[1][0] == 'd'){    //'d' d n message
//			string d = argv[2];
//			string n = argv[3];
//			string m = argv[4];
//			cout << "d=" << d << ", n=" << n << ", message=" << m << endl;
//			//call your RSA decryption ...
//			RSAEncryption ex;
//			cout << ex.IntToMessage(BigInt(d), n, BigInt(m));
//		}
//		int pause;
//		cin >> pause;
//	}
//
//	return 0;
//}

/*
1.       Fermat’s test to generate large prime numbers with high confidence
@param: the size of the prime number (length of the prime number. Ex. the size of 113 is 3)
@return: a prime number of the size
2.       Extended Euclidean Algorithm
@param: two int (a,b)
@return: two int (x,y) such that gcd(a,b) = ax+by and y>0.
3.       RSA encryption
@param: int pair (e,n): public key
string : the message to be encrypted
@return: string : the encrypted message
4.       RSA decryption
@param: int pair (d,n): private key
string : message to be decrypted
@return: string : the decrypted message



Main function:
Please include only one main function in your program although each required function of your program will be tested. Use common-line arguments to separate the tasks to facilitate our grading of your program. Your program will be returned and resubmission will be requested if it does not follow the required format. Click here to see a c++ version of how to use common line arguments for this project (your program is required for follow the same format regardless the language you use). To grade each part, we’ll use
·       yourProgram.exe  s   //your program should output a prime with s digit to the console
·       yourProgram.exe  a b   //your program should output (x,y) s.t. gcd(a,b) = ax+by and y>0
·       yourProgram.exe  e p q //your program should output (d,n) s.t. ed=1%(p-1)(q-1), n=pq
·       yourProgram.exe  ‘e’ e n message   //your program should output the encrypted message
·       yourProgram.exe  ‘d’ d n message   // your program should output the decrypted message



*/

