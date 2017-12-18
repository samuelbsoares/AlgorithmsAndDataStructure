/*
 * TestStack.cpp
 *
 *  Created on: Sep 29, 2017
 *      Author: samue
 */

#include <ctime>
#include "Stack.cpp"
#include <stack>

template <typename T> // how to enforce same Type???? TODO:
void populateStack(Stack<T>& s, T t, long amount) {
	while(amount--) {
		s.push(t);
	}
}

template <typename T> // how to enforce same Type???? TODO:
void populateStack(std::stack<T>& s, T t, long amount) {
	while(amount--) {
		s.push(t);
	}
}

using std::cout;

int main() {
	clock_t start, stop;

	// start trials
	int nArray[] = {1000, 2000, 4000, 8000, 16000};

	double testArray[4][5];

	cout << "\t\t" << nArray[0] << "\t" << nArray[1] << "\t" << nArray[2] << "\t"
			<< nArray[3] << "\t" << nArray[4] << "\n";


	// grow by one
	for(int i = 0; i < 5; ++i) {
		int n = nArray[i];
		int rate = 1;
		Stack<int> s(n, rate);
		start = clock();
		populateStack(s, 1, n);
		stop = clock();
		testArray[0][i] = (double)(stop - start);
	}

	cout << "by one\t" << testArray[0][0] << "\t" << testArray[0][1] << "\t" << testArray[0][2] << "\t"
			<< testArray[0][3] << "\t" << testArray[0][4] << "\n";

	// grow by ten
	for(int i = 0; i < 5; ++i) {
		int n = nArray[i];
		int rate = 10;
		Stack<int> s(n, rate);
		start = clock();
		populateStack(s, 1, n);
		stop = clock();
		testArray[1][i] = (double)(stop - start);
	}

	cout << "by ten\t" << testArray[1][0] << "\t" << testArray[1][1] << "\t" << testArray[1][2] << "\t"
			<< testArray[1][3] << "\t" << testArray[1][4] << "\n";

	// doubles
	for(int i = 0; i < 5; ++i) {
		int n = nArray[i];
		int rate = n * 2;
		Stack<int> s(n, rate);
		start = clock();
		populateStack(s, 1, n);
		stop = clock();
		testArray[2][i] = (double)(stop - start);
	}

	cout << "doubles\t" << testArray[2][0] << "\t" << testArray[2][1] << "\t" << testArray[2][2] << "\t"
			<< testArray[2][3] << "\t" << testArray[2][4] << "\n";

	// using STL
	for(int i = 0; i < 5; ++i) {
		int n = nArray[i];
		std::stack<int> s;
		start = clock();
		populateStack(s, 1, n);
		stop = clock();
		testArray[1][i] = (double)(stop - start);
	}

	// Draw table
	cout << "STL\t" << testArray[3][0] << "\t" << testArray[3][1] << "\t" << testArray[3][2] << "\t"
			<< testArray[3][3] << "\t" << testArray[3][4] << "\n";

}
