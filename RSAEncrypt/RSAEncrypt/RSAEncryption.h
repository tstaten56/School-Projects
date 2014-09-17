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
	BigInt MessageToInt(string message);   
	string IntToMessage(BigInt num);
	void setPhiN(BigInt p, BigInt q);
	void ExtEuclid(BigInt a, BigInt m);
	void setN(BigInt p, BigInt q);
	void outputXY();
	void outputDN();
};

#endif