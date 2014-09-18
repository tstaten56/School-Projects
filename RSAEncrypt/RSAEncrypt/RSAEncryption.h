#pragma once
#ifndef RSAENCRYPTION_H
#define RSAENCRYPTION_H

#include "BigInt.h"

class RSAEncryption
{
private:
	BigInt x, y, gcdNum, phiN, u, n;
public:
	RSAEncryption();
	~RSAEncryption();
	BigInt ModInverse(string, string, string);
	BigInt MessageToInt(BigInt e, string n, string message);   
	string IntToMessage(BigInt d, string n, BigInt num);
	void setPhiN(BigInt p, BigInt q);
	void ExtEuclid(BigInt a, BigInt m);
	void setN(string tempN);
	void setN(BigInt p, BigInt q);
	BigInt getN();
	void outputXY();
	void outputDN();
};

#endif