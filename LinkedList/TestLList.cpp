/*
 * TestLList.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: samue
 */

#include "LList.h"
#include <iostream>
#include <assert.h>
#include <new>

using std::cout;
using std::endl;

#define NDEBUG

/**
 * Helper function to sequentially populate a given list
 * @param list List to be populated
 * @param x Number os items to be generated
 * @param ch Starting char
 */
void populate(LList& list, int x, char ch) {
	for (int i = 0; i < x; ++i) {
		list.append(ch + i);
	}
}

int main() {
	// Tests simple constructor and isEmpty
	LList list;
	assert(list.isEmpty());

	// Tests length, destructor and deleteAll
	assert(list.length() == 0);
	list.append('a');
	assert(list.length() == 1);
	list.append('b');
	assert(list.length() == 2);
	populate(list, 100, '0');
	assert(list.length() == 102);
	list.~LList();
	assert(list.length() == 0);

	// Tests overloaded assignment operator
	// and compareTo
	// General case (list with 2 items)
	populate(list, 2, 'a');
	LList newList;
	// Copies populated list
	newList = list;
	assert(newList.length() == 2);
	assert(newList.compareTo(list));
	list.~LList();
	newList = list;
	assert(newList.isEmpty());

	// Tests the copy constructor
	populate(list, 2, 'a');
	newList = list;
	assert(list.compareTo(newList));
	// Empty list
	list.~LList();
	newList = list;
	assert(list.compareTo(newList));

	// Tests length
	populate(list, 12, 'a');
	assert(list.length() == 12);
	list.~LList();
	assert(!list.length());
	list.~LList();

	// Tests insertion in the beginning of the list
	populate(newList, 3, 'a');
	newList.cons('z');
	list.append('z');
	list.append('a');
	list.append('b');
	list.append('c');
	assert(newList.compareTo(list));
	list.~LList();
	newList.~LList();

	// Tests reverse
	// Populated list
	populate(newList, 3, 'a');
	newList.cons('z');
	list.append('c');
	list.append('b');
	list.append('a');
	list.append('z');
	newList.reverse();
	assert(newList.compareTo(list));
	list.~LList();
	newList.~LList();
	// Empty list
	list.reverse();
	newList = list;
	assert(list.compareTo(newList));
	// One element list
	list.append('a');
	list.reverse();
	newList = list;
	assert(list.compareTo(newList));
	list.~LList();
	newList.~LList();

	// Tests remove
	// General cases
	populate(newList, 3, 'a');
	newList.cons('z');
	assert(newList.remove('c'));
	assert(newList.remove('z'));
	// Non-existent item
	assert(!newList.remove('c'));
	// Last element
	assert(newList.remove('a'));
	// Only element left
	assert(newList.remove('b'));
	// Empty list
	assert(!newList.remove('z'));
	list.~LList();
	newList.~LList();

	// Tests copy constructor
	// Copy regular list
	list.append('a');
	list.append('0');
	newList = list;
	assert(list.length() == newList.length());
	list.~LList();
	newList.~LList();
	// Copy list w/ 1 element
	list.append('a');
	newList = list;
	assert(newList.length() == 1);
	// Copy copied list
	LList otherList(newList);
	assert(otherList.length() == 1 && otherList.remove('a'));
	// Copy empty list
	list.~LList();
	newList.~LList();
	otherList.~LList();
	newList = list;
	assert(list.isEmpty() && newList.isEmpty());
	// Copy list with 100 elements
	list.~LList();
	newList.~LList();
	populate(list, 100, 48);
	newList = list;
	assert(newList.length() == 100);
	list.~LList();
	newList.~LList();

	// Tests found
	// Empty list
	assert(!list.found('0'));
	populate(list, 10, '0');
	list.cons('9');
	// Populated list
	assert(list.found('9'));
	// Populated list
	assert(list.found('0'));
	// Non-existing item
	assert(!list.found('a'));
	// Empty char
	assert(!list.found('\0'));
	list.~LList();

	// Tests getFirst
	bool hasFirst = true;
	char firstChar = 'a';
	// Empty list
	newList = list; // Copy
	firstChar = list.getFirst(hasFirst);
	assert(!hasFirst);
	assert(firstChar == '\0');
	assert(list.compareTo(newList));
	// Populated list
	populate(list, 3, 'a');
	newList = list; // Copy
	firstChar = list.getFirst(hasFirst);
	assert(hasFirst);
	assert(firstChar == 'a');
	assert(list.compareTo(newList));
	// One item
	list.remove('a');
	list.remove('b');
	newList = list; // Copy
	firstChar = list.getFirst(hasFirst);
	assert(hasFirst);
	assert(firstChar == 'c');
	assert(list.compareTo(newList));
	list.~LList();
	newList.~LList();

	// Tests print
	list.print();
	list.cons('*');
	list.cons('*');
	list.cons('*');
	list.cons('D');
	list.cons('E');
	list.cons('S');
	list.cons('S');
	list.cons('A');
	list.cons('P');
	list.cons('*');
	list.cons('*');
	list.cons('*');
	list.print();
	list.~LList();

	// Finding the longest possible linked list using recursive algorithms
	unsigned long long counter(0);
	while (list.cons('a'))
		++counter;
	cout << "Elements created: " << counter << "\n";
}
