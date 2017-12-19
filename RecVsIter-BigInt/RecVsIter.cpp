/*
 * RecVsIter.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Samuel B. Soares
 *   StudentID: 100271978
 *   	Course: CPSC1160-003
 *  Assignment: 3 (Recursive)
 *
 *   	References:
 *   	http://en.cppreference.com/w/cpp/language/operators
 *   	http://en.cppreference.com/w/cpp/language/types
 *   	https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx
 *
 */

#include <iostream>
#include <limits.h>

using namespace std;

const int DIGITS = 3000;

class BigInt {
		char digits[DIGITS] = { 0 };
		int length;
		friend ostream& operator <<(ostream& os, const BigInt& bigint);
		friend BigInt operator * (const int i, const BigInt bigint);
	public:
		BigInt(unsigned long long ull);
		BigInt();
		void factorial(BigInt bigint);
		BigInt operator + (const BigInt& bigint);
		BigInt& operator += (const BigInt& bigint);
		BigInt& operator *= (const int i);
		//TODO implement the rest!
//		BigInt operator -(const BigInt& bigint);
//		BigInt operator -=(const BigInt& bigint);
//		BigInt operator *(const BigInt& bigint);
//		BigInt operator *=(const BigInt& bigint);
};

BigInt::BigInt() {
	length = 1;
}

BigInt::BigInt(unsigned long long start) {
	int i = 0;
	for (; i < DIGITS && start > 0; ++i) {
		this->digits[i] = (start % 10);
		start /= 10;
	}
	length = i;
}

ostream& operator <<(ostream& os, const BigInt& big) {
	for(int i = big.length; i > 0; --i) {
		os << char(big.digits[i - 1] + '0');
	}
	return os;
}

BigInt BigInt::operator +(const BigInt& bigint) {
	BigInt bigResult;
	int result(0);
	int maxLength = length > bigint.length ? length : bigint.length;
	for (int i = 0; i < maxLength; ++i) {
		result += digits[i] + bigint.digits[i];
		bigResult.digits[i] = result % 10;
		result /= 10;
	}
	while (result) {
		bigResult.digits[maxLength] = result % 10;
		result /= 10;
		maxLength++;
	}
	bigResult.length = maxLength;
	return bigResult;
}

BigInt& BigInt::operator +=(const BigInt& bigint) {
	int result(0);
	int maxLength = length > bigint.length ? length : bigint.length;
	for (int i = 0; i < maxLength; ++i) {
		result += digits[i] + bigint.digits[i];
		digits[i] = result % 10;
		result /= 10;
	}
	while (result) {
		digits[maxLength] = result % 10;
		result /= 10;
		maxLength++;
	}
	length = maxLength;
	return *this;
}

BigInt operator * (const int i, const BigInt bi){
	BigInt ans = bi;
	int k = i;
	while(--k) {
		ans += bi;
	}
	return ans;
}

BigInt& BigInt::operator *= (const int i){
	int k = i;
	BigInt ans = *this;
	while(--k) {
		*this += ans;
	}
	return *this;
}

// Asked functions prototypes
unsigned long long iterFibo(int n);
unsigned long long recFibo(int n);
BigInt iterFact(int n);
BigInt recFact(int n);

int main() {
    char answer = 'Y';
    int n;
    do {
        cout << endl<< endl;
        cout <<">===============( New RUN )===============<"<<endl;
        cout << "\nPlease enter an integer number: ";
        cin >> n;
        cout << endl;
        cout << "Iterative Factorial("<< n <<") is "<< iterFact(n) << endl;
        cout << "Recursive Factorial("<< n <<") is "<< recFact(n) << endl;
        cout << "Iterative Fibonacci("<< n <<") is "<< iterFibo(n) << endl;
        cout << "Recursive Fibonacci("<< n <<") is "<< recFibo(n) << endl<< endl;
        cout << "Do you want to continue? (Y/N)";
        cin >> answer;
    } while (toupper(answer) == 'Y');
    cout << "The Program has ended gracefully!";
	return 0;
}

// Results overflowing for ull variables in Factorial functions
// - 18446744073709551615 	-> max value for unsigned long long
// - 2432902008176640000 	-> fact(20)
// - 51090942171709440000 	-> fact(21) OVERFLOWS
// - 1124000727777607680000 -> fact(22)

// Generates according to the sequence A000045
// https://oeis.org/A000045/list
unsigned long long iterFibo(int n) {
	if (n < 0) {
		return 0;
	}
	else if (n < 2) {
		return n;
	}
	unsigned long long first = 0;
	unsigned long long second = 1;
	while (n-- > 1) {
		second += first;
		first = second - first;
	}
    return second;
}

// Generates according to the sequence A000045
// https://oeis.org/A000045/list
unsigned long long recFibo(int n) {
    if (n < 1) return 0;
    return (n < 2) ? n : recFibo(n - 1) + recFibo(n - 2);
}

// Generates according to the sequence A000142
// https://oeis.org/A000142/list
BigInt iterFact(int n) {
	// factorial of a negative number should be -INFINITY
	if (n < 0) return 0;
    BigInt f = 1;
    for (int k = n; k > 1; --k) {
		f *= k;
	}
    return f;
}

// Generates according to the sequence A000142
// https://oeis.org/A000142/list
BigInt recFact(int n) {
	// factorial of a negative number should be -INFINITY
	if (n < 0) return BigInt(0);
	else if (n == 1 || n == 0) return BigInt(1);
    return n * recFact(n - 1);
}
