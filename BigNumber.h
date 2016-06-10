#ifndef __BIGNUMBER_H__
#define __BIGNUMBER_H__
#include <stdio.h>
#include <stdlib.h>

class BigNumber{
	public:
		BigNumber();	//constructor
		~BigNumber();	//destructor

		void hexToInt(char* num_str);
		void printBigNumber();

		BigNumber Larger(BigNumber b);//compare self and b
		BigNumber Smaller(BigNumber b);//compare self and b
		
		bool Equal(BigNumber b);//self == b
		BigNumber Plus(BigNumber b);//self + b
		BigNumber Minus(BigNumber b);//self - b
		BigNumber Times(BigNumber b);// self * b
		BigNumber divisionQuot(BigNumber b);//self / b
		BigNumber divisionMod(BigNumber b);//self % b, get the smallest positive mod value
		
		BigNumber operator +(const BigNumber& b);
		BigNumber operator -(const BigNumber& b);
		BigNumber operator *(const BigNumber& b);
		BigNumber operator /(const BigNumber& b);
		BigNumber operator %(const BigNumber& b);
		bool operator ==(const BigNumber& b);

		BigNumber divideByTwo();//return self / 2
		bool isDivideInteger(int divisor);//whether self % divisor is zero or not
		BigNumber Pow(BigNumber e, BigNumber n);//self^e mod n
		BigNumber squareRoot(BigNumber p);//one of the self^(1/2) mod p
		BigNumber ExEuclid(BigNumber p);//cx+py = cx = 1, return x, which is the inverse of c. self & p are relative prime.


	private:
		int num_int[200];
		int length;
		int sign;
};

#endif	/*__BIGNUMBER_H__*/