#include "BigNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#define self (*this)
using namespace std;
//Constructor of BigNumber class
BigNumber::BigNumber(){
	memset(num_int, 0, sizeof(num_int));
	length = 0;
	sign = 0;
}

//Denstructor of BigNumber class
BigNumber::~BigNumber(){
}

/***********************************
	void hexToInt(char* num_str)

	->num_str is the input that user typed it.
	  this function can let this instance have num_str's bignumber value in its num_int array
	
	return when finish
***********************************/
void
BigNumber::hexToInt(char* num_str){
    int l = strlen(num_str);
    for(int x=0; x<l; x++){
        switch(num_str[l-x-1]){
            case '-':
            	sign = 1;	l--;	break;
            case '0':
                num_int[x] = 0;break;
            case '1':
                num_int[x] = 1;break;
            case '2':
                num_int[x] = 2;break;
            case '3':
                num_int[x] = 3;break;
            case '4':
                num_int[x] = 4;break;
            case '5':
                num_int[x] = 5;break;
            case '6':
                num_int[x] = 6;break;
            case '7':
                num_int[x] = 7;break;
            case '8':
                num_int[x] = 8;break;
            case '9':
                num_int[x] = 9;break;
            case 'A':
                num_int[x] = 10;break;
            case 'B':
                num_int[x] = 11;break;
            case 'C':
                num_int[x] = 12;break;
            case 'D':
                num_int[x] = 13;break;
            case 'E':
                num_int[x] = 14;break;
            case 'F':
                num_int[x] = 15;break;
            default:
                num_int[x] = 0;break;
        }
    }
    for(length = l; length>0; length--){
        if(num_int[length-1] != 0)
            break;
    }
    return;
}

/***********************************
	void printBigNumber()

	->use all private data in this instance to print out bignumber
	
	return when finish
***********************************/
void 
BigNumber::printBigNumber(){
    if(sign)	putchar('-');
    
    if(length <= 0){
    	putchar('0');
    }
    else{
        for(int x=0; x<length; x++){
	        switch(num_int[length-x-1]){
	            case 0:
	                putchar('0');break;
	            case 1:
	                putchar('1');break;
	            case 2:
	                putchar('2');break;
	            case 3:
	                putchar('3');break;
	            case 4:
	                putchar('4');break;
	            case 5:
	                putchar('5');break;
	            case 6:
	                putchar('6');break;
	            case 7:
	                putchar('7');break;
	            case 8:
	                putchar('8');break;
	            case 9:
	                putchar('9');break;
	            case 10:
	                putchar('A');break;
	            case 11:
	                putchar('B');break;
	            case 12:
	                putchar('C');break;
	            case 13:
	                putchar('D');break;
	            case 14:
	                putchar('E');break;
	            case 15:
	                putchar('F');break;
	        }
	    }
    }
    putchar('\n');
}

/***********************************
	BigNumber Larger(BigNumber b)

	->compare self and b and return the larger one
	  this function just consider the magnitude!!!
	
	return self when self > b
	return b when self == b
	return b when self < b
***********************************/
BigNumber
BigNumber::Larger(BigNumber b){
	int larger_length = max(self.length, b.length);
	for(int x=larger_length; x>=0; x--){
		if(self.num_int[x] > b.num_int[x])	return self;
		else if(self.num_int[x] < b.num_int[x])	return b;
	}
	return b;
}

/***********************************
	BigNumber Smaller(BigNumber b)

	->compare self and b and return the smaller one
	  self function just consider the magnitude!!!
	
	return b when self > b
	return b when self == b
	return self when self < b
***********************************/
BigNumber
BigNumber::Smaller(BigNumber b){
	int larger_length = max(self.length, b.length);
	for(int x=larger_length; x>=0; x--){
		if(self.num_int[x] > b.num_int[x])	return b;
		else if(self.num_int[x] < b.num_int[x])	return self;
	}
	return b;
}

/***********************************
	bool Equal(BigNumber b)

	->compare self and b and consider whether self == b or not
	  this function just consider the magnitude!!!

	return true when self == b
	return false when self != b
***********************************/
bool
BigNumber::Equal(BigNumber b){
	int larger_length = max(self.length, b.length);
	for(int x=larger_length; x>=0; x--)
		if(self.num_int[x] != b.num_int[x])	return false;
	return true;
}

/***********************************
	BigNumber Plus(BigNumber b)

	->Plus self and b, return the result
	  this function can handle negative bignumber calculation

	return self + b, a BigNumber instance
***********************************/
BigNumber
BigNumber::Plus(BigNumber b){
	BigNumber res_plus;
    res_plus.length = self.Larger(b).length;
    
    if(self.sign != b.sign){
    	if(self.sign == 1){	//self.sign == 1, b.sign == 0
    		BigNumber temp = self;
    		temp.sign = 0;
    		return b.Minus(temp);
    	}
    	else{	//self.sign == 0, b.sign == 1
    		BigNumber temp = b;
    		temp.sign = 0;
    		return self.Minus(temp);
    	}
    }
    
    else if(self.sign == 1)// self, b are both negative
    	res_plus.sign = 1;

    //plus two BigNumber and adjust carry
    for(int x=0; x<res_plus.length; x++)
        res_plus.num_int[x] = self.num_int[x] + b.num_int[x];
    for(int x=0; x<res_plus.length; x++){
        if(res_plus.num_int[x]>15){
            res_plus.num_int[x] -= 16;
            res_plus.num_int[x+1] += 1;
        }
    }

    //edit res_plus.length
    if(res_plus.num_int[res_plus.length] > 0)
        res_plus.length += 1;
    return res_plus;
}

/***********************************
	BigNumber Minus(BigNumber b)

	->self minus b, return the result
	  this function can handle negative bignumber calculation

	return self - b, a BigNumber instance
***********************************/
BigNumber
BigNumber::Minus(BigNumber b){
	BigNumber res_minus;

    //need to be larger - smaller
    BigNumber larger = self.Larger(b);
    BigNumber smaller = self.Smaller(b);

    if(self.sign != b.sign){
    	if(self.sign == 1){	//self.sign == 1, b.sign == 0
    		BigNumber temp = self;
    		temp.sign = 0;
    		res_minus = temp.Plus(b);
    		res_minus.sign = 1;
    		return res_minus;
    	}
    	else{	//self.sign == 0, b.sign == 1
    		BigNumber temp = b;
    		temp.sign = 0;
    		res_minus = self.Plus(temp);
    		res_minus.sign = 0;
    		return res_minus;
    	}
    }
    if(self.Equal(b))	//self == b, the result will be zero
    	return res_minus;


    if(self.sign == 1){	//self.sign == 1, b.sign == 1
    	if(larger.Equal(self))
    		res_minus.sign = 1;
    }
    else{
    	if(larger.Equal(b))
    		res_minus.sign = 1;
    }

    //minus two BigNumber and adjust carry
    for(int x=0; x<larger.length; x++)
        res_minus.num_int[x] = larger.num_int[x] - smaller.num_int[x];
    for(int x=0; x<larger.length; x++){
        if(res_minus.num_int[x]<0){
            res_minus.num_int[x] += 16;
            res_minus.num_int[x+1] -= 1;
        }
    }

    //edit res_minus->length
    int x;
    for(x=larger.length-1; x>=0; x--){
        if(res_minus.num_int[x]!=0)
            break;
    }
    res_minus.length = x+1;

    return res_minus;
}

/***********************************
	BigNumber Times(BigNumber b)

	->self times b, return the result
	  this function can handle negative bignumber calculation

	return self * b, a BigNumber instance
***********************************/
BigNumber
BigNumber::Times(BigNumber b){
	BigNumber res_times;
    
    BigNumber larger = self.Larger(b);//for x
    BigNumber smaller = self.Smaller(b);//for y

    //times two numbers, adjust carry
    int x, y;
    for(x=0; x<larger.length; x++){
        for(y=0; y<smaller.length; y++)
            res_times.num_int[x+y] += larger.num_int[x] * smaller.num_int[y];
    }
    for(x=0; x<(self.length+b.length); x++){//max length of m*n is len(m)+len(n)
        while(res_times.num_int[x]>15){//adjust carry
            res_times.num_int[x] -= 16;
            res_times.num_int[x+1] += 1;
        }
    }
    //edit res_times length
    int real_length=0;
    for(x=0; x<(self.length+b.length); x++){//max length of m*n is len(m)+len(n)
        if(res_times.num_int[x] > 0)
            res_times.length = x+1;//last position plus 1
    }
    if(self.sign != b.sign)	res_times.sign = 1;
    return res_times;
}

/***********************************
	BigNumber divisionQuot(BigNumber b)

	->self / b, return the result
	  we get quot's value by the concept of long-division method
	  this function can handle negative dividend and negative divisor

	return self / b, a BigNumber instance
***********************************/
BigNumber
BigNumber::divisionQuot(BigNumber b){
	bool flag = false;	//flag: record whether self is + or -	(+ => false, - => true)
	bool flag2 = false;	//flag2: record whether b is + or -		(+ => false, - => true)
    BigNumber zero;
    
    //handle negative bignumber and |self|<|b| situation
    BigNumber p_self = self;
    if(self.sign == 1){
    	p_self.sign = 0;
    	flag = true;
    }
    if(b.sign == 1){
    	b.sign = 0;
    	flag2 = true;
    }
    if(b.Equal(p_self.Larger(b))) return zero;

    //initialize some variables
    BigNumber dividend = p_self;
    BigNumber quot;
    BigNumber temp;
    int l_m_s = p_self.length - b.length;
    int k;
    
    //get quot's value by the concept of long-division method
    for(int i=l_m_s; i>=0; i--){
        k=0;
        temp = b;
        for(int j=temp.length-1; j>=0; j--)
            temp.num_int[j+i] = temp.num_int[j];
        for(int j=i-1; j>=0; j--)
        	temp.num_int[j] = 0;
        temp.length += i;
        
        while(dividend.Equal(dividend.Larger(temp))){
            dividend = dividend.Minus(temp);
            k++;
        }
        quot.num_int[i] = k;
    }

    //get quot's length
    for(int i=l_m_s; i>=0; i--){
        if(quot.num_int[i]!=0){
            quot.length = i+1;
            break;
        }
    }
    
    //get quot's sign, and return quot
    if(!(flag^flag2))	return quot;
    else{
    	quot.sign = 1;
    	return quot;
    }
}

/***********************************
	BigNumber divisionMod(BigNumber b)

	->self % b, return the result
	  this function's purpose is to get the smallest positive mod value
	  this function's implementation is same as divisionQuot()
	  this function can handle negative dividend, but no negative divisor!!!


	return self / b, a BigNumber instance
***********************************/
BigNumber
BigNumber::divisionMod(BigNumber b){
    BigNumber quot = self.divisionQuot(b);
    return (self.sign==0)?self-(b*quot):b+(self-(b*quot));
}

/***********************************
	operator: +,-,*,/,%,==

	self + b <= self.Plus(b)
	self - b <= self.Minus(b)
	self * b <= self.Times(b)
	self / b <= self.divisionQuot(b)
	self % b <= self.divisionMod(b)
	self == b <= self.Equal(b)
	
	!!!!!! For easier to understand, we didn't use operator for implementing these functions.
***********************************/
BigNumber
BigNumber::operator +(const BigNumber& b){
	BigNumber res = self.Plus(b);
	return res;
}
BigNumber
BigNumber::operator -(const BigNumber& b){
	BigNumber res = self.Minus(b);
	return res;
}
BigNumber
BigNumber::operator *(const BigNumber& b){
	BigNumber res = self.Times(b);
	return res;
}
BigNumber
BigNumber::operator /(const BigNumber& b){
	BigNumber res = self.divisionQuot(b);
	return res;
}
BigNumber
BigNumber::operator %(const BigNumber& b){
	BigNumber res = self.divisionMod(b);
	return res;
}
bool
BigNumber::operator ==(const BigNumber& b){
	bool res = self.Equal(b);
	return res;
}




/***********************************
	BigNumber divideByTwo()

	->self / 2, return the result
	  we use bignumber/int to implement it. ref from 'algo note'
	  this function can handle negative bignumber calculation

	return self / 2, a BigNumber instance
***********************************/
BigNumber
BigNumber::divideByTwo(){
	BigNumber res_div2;
    res_div2.sign = self.sign;// sign will not change

    //get res_div2's value by implementing bignumber/int
    int i;
    int r = 0;
    for(i = self.length-1; i>=0; i--){
        r = r*16 + self.num_int[i];
        res_div2.num_int[i] = r/2;
        r %= 2;
    }

    //get res_div2's length
    for(i = self.length-1; i>=0; i--){
        if(res_div2.num_int[i]!=0)
            break;
    }
    res_div2.length = i+1;

    return res_div2;
}

/***********************************
	bool isDivideInteger(int divisor)

	->consider whether self % divisor is zero or not
	  we use bignumber/int to implement it. ref from 'algo note'
	  this function can handle negative bignumber calculation

	return true when self % divisor == 0
	return false when other situations 
***********************************/
bool
BigNumber::isDivideInteger(int divisor){
	BigNumber quot;
    
    int i;
    int r = 0;
    for (i=length-1; i>=0; i--){
        r = r * 16 + num_int[i];
        quot.num_int[i] = r / divisor;
        r %= divisor;
    }
    for(i = length-1; i>=0; i--){
        if(quot.num_int[i]!=0)
            break;
    }
    quot.length = i+1;

    // concept : F = Q*P + R.	F:self, Q:quot, P:prime_big(BigNumber instance of divisor) 
    BigNumber prime_big;
    while(divisor != 0){
    	prime_big.num_int[prime_big.length] = divisor%16;
    	divisor/=16;
    	prime_big.length++;
    }

    BigNumber time_res = quot.Times(prime_big);
    bool res = self.Equal(time_res);//is F == Q*P?	(R == 0)
    return res;
}

/***********************************
	BigNumber pow(BigNumber e, BigNumber n)

	->calculate self^e%n, we 'mod n' for the purpose of staying in same field.
	  this function can handle negative bignumber calculation

	return self^e%n, a BigNumber instance
***********************************/
BigNumber
BigNumber::Pow(BigNumber e, BigNumber n){
	BigNumber one;	one.num_int[0] = 1;	one.length = 1;
	BigNumber temp_self = self;// copy 'self' instance for Pow calculation
	BigNumber coeff = one;// initialize coefficient
    while(e.length != 0){
        if(e.isDivideInteger(2)){// e % 2 == 0
            e = e.divideByTwo();
            temp_self = (temp_self.Times(temp_self)).divisionMod(n);// self^2 mod n
        }
        else{
            e = e.Minus(one);
            coeff = (temp_self.Times(coeff)).divisionMod(n);
        }
    }
    return coeff;
}

/***********************************
	BigNumber squareRoot(BigNumber p)

	->calculate self^(1/2) mod p
	  ##In a Zp field, there is another squareRoot : p-result
		user can get another one by the Minus function

	return (one of the) self^(1/2) mod p, a BigNumber instance
***********************************/
BigNumber
BigNumber::squareRoot(BigNumber p){
	BigNumber one;	one.num_int[0] = 1;	one.length = 1;
	BigNumber clp = self.Pow(p.Minus(one).divideByTwo(), p);// clp = a^((p-1)/2) mod p
    BigNumber b = p.Minus(one);// b will let (b/p) = -1
    BigNumber t = p.Minus(one);
    int s = 0;
    while(t.isDivideInteger(2)){
    	t = t.divideByTwo();
    	s++;
    }
    BigNumber af = self.Pow(((p.Minus(one)).divideByTwo()).Minus(one), p);// af = a^(((p-1)/2)-1) mod p
    BigNumber c = b.Pow(t, p);
    BigNumber r = self.Pow(t.Plus(one).divideByTwo(), p);
    BigNumber d;
    for(int i = 1; i<s; i++){ // from 1 to s-1
    	d = one;
    	int d_pow = int(pow(2, s-i-1));
    	for(int j = 0; j<d_pow; j++){
    		d = d.Times(r.Times(r).divisionMod(p).Times(af).divisionMod(p));
    		if(d.Equal(p.Minus(one))) r = r.Times(c).divisionMod(p);
    		c = c.Times(c).divisionMod(p);
    	}
    }
    return r;
}

/***********************************
	BigNumber ExEuclid(BigNumber p)

	->cx+py = cx = 1, use Extended Euclid Theorem to calculate x, which is the inverse of c.
	  self & p need to be relative prime.

	return the inverse of c, a BigNumber instance
***********************************/
BigNumber recExEuclid(BigNumber a, BigNumber b, BigNumber* x, BigNumber* y){
    BigNumber one;  one.num_int[0] = 1; one.length = 1;
    BigNumber tmp, d, zero;
    if(b.Equal(zero)){
        *x = one;
        *y = zero;
        return a;
    }
    d=recExEuclid(b, a%b, x, y);
    tmp = *x;
    *x=*y;
    *y=tmp-(a/b*(*y));
    return d;
}
BigNumber
BigNumber::ExEuclid(BigNumber p){
    BigNumber x, y;
    BigNumber gcd = recExEuclid(self, p, &x, &y);
    //gcd.printBigNumber();
    return x%p;
}


int
BigNumber::getLength(){
    return self.length;
}

int
BigNumber::getSign(){
    return self.sign;
}
