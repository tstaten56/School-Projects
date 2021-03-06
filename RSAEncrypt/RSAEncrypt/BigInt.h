/*##############################
# written by a UA student.   #
# all rights are reserved.   #
##############################*/

#ifndef BIGINT_H
#define	BIGINT_H

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <time.h>

using namespace std;

typedef unsigned char uchar;
typedef list<uchar> IntList;

class BigInt {
private:
	IntList intAsList;
	bool isPositive;
public:
	BigInt();
	BigInt(string const&);
	BigInt(IntList const&, bool isPositive);
	BigInt(int);

	int getLength() const;
	bool GetIsPositive() const;
	static BigInt modExp(BigInt base, BigInt exponent, BigInt const& mod);

	friend ostream& operator<<(ostream& stream, BigInt const& num);
	friend ostream& operator<<(ostream& stream, int const& num);

	bool operator<(BigInt const& thatNum) const;
	bool operator<(int const& thatNum) const;
	bool operator>(BigInt const& thatNum) const;
	bool operator>(int const& thatNum) const;
	bool operator<=(BigInt const& thatNum) const;
	bool operator<=(int const& thatNum) const;
	bool operator>=(BigInt const& thatNum) const;
	bool operator>=(int const& thatNum) const;
	bool operator==(BigInt const& thatNum) const;
	bool operator==(int const& thatNum) const;
	bool operator!=(BigInt const& thatNum) const;
	bool operator!=(int const& thatNum) const;
	BigInt operator+(BigInt const& thatNum) const;
	BigInt operator+(int const& thatNum) const;
	BigInt operator-(BigInt const& thatNum) const;
	BigInt operator-(int const& thatNum) const;
	BigInt operator-() const;
	BigInt operator%(BigInt const& mod) const;
	BigInt operator%(int const& mod) const;
	BigInt operator*(BigInt const& thatNum) const;
	BigInt operator*(int const& thatNum) const;
	BigInt operator/(BigInt const& thatNum) const;
	BigInt operator/(int const& thatNum) const;
	BigInt half();
	int GetInt();
	BigInt push(unsigned char digit);
	BigInt clear();
	BigInt bigExp(BigInt base, BigInt exp);

private:
	void borrow(IntList::reverse_iterator place) const;
};

#endif
