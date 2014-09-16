#pragma once
#ifndef RSAENCRYPTION_H
#define RSAENCRYPTION_H

#include "BigInt.h"

class RSAEncryption
{
private:

public:
	RSAEncryption();
	~RSAEncryption();
	BigInt ModInverse(string tempE, string tempP, string tempQ);
	BigInt MessageToInt(string message);   
	string IntToMessage(BigInt num);
};

#endif