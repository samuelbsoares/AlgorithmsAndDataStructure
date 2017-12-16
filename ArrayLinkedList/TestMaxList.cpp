/*
 * TestMaxList.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: Samuel B. Soares
 */

#include "LList.h"
#include <iostream>
#include <assert.h>
#include <new>
#include <sstream>

using std::cout;
using std::endl;

void testLargestList(int capacity, int growthRate) {
	unsigned long long counter(0);
	LList list;
	if(!capacity || !growthRate)
		list.setCapAndGrowth(capacity, growthRate);
	while (list.cons('a')) {
		++counter;
	}
	cout << "Elements created: " << counter << "\n";
}

/**
 * Tests the maximum elements with the LList object
 */
int main(int argc, char *argv[]) {
	int c;
	int g;
	// handles arguments using sstream
	if(argc == 2) {
		std::istringstream ssCap(argv[0]), ssGro(argv[1]);
		if(!(ssCap >> c) && !(ssGro >> g)) {
			testLargestList(c, g);
		}
		return -1;
	}
	testLargestList(0, 0);
}
