/*
 * TestLList.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: Samuel B. Soares
 */

#include "LList.h"
#include <iostream>
#include <assert.h>
#include <new>
#include <fstream>

using std::cout;
using std::endl;

#define NDEBUG

/**
 * Helper function to sequentially populate a given list
 * @param list List to be populated
 * @param x Number os items to be generated
 * @param ch Starting char
 */
void populate(LList& list, int x, char ch, bool repeat = false) {
	for (int i = 0; i < x; ++i) {
		list.cons((repeat) ? (ch) : (ch + i));
	}
}

void testA() {
	// Tests simple constructor and isEmpty
	LList list;
	list.print("Empty list:");
	assert(list.isEmpty());

	// Tests length, destructor and deleteAll
	assert(list.length() == 0);
	list.print("Empty list:");
	list.append('a');
	list.print("Operation: append(a)");
	assert(list.length() == 1);
	list.append('b');
	list.print("Operation: append(b)");
	assert(list.length() == 2);
	populate(list, 10, 'a', true);
	list.print("Operation: cons(a) 10 times");
	assert(list.length() == 12);
}

void testB() {
	// Tests overloaded assignment operator
	// and compareTo
	// General case (list with 2 items)
	LList list;
	list.print("Empty list:");
	populate(list, 2, 'a');
	list.print("Operation: cons(b, a)");
	// Copies populated list
	LList newList;
	newList.print("Empty list:");
	newList = list;
	newList.print("Copied previous populated list:");
	assert(newList.length() == 2);
	assert(newList == list);
}

void testC() {
	// Tests copy constructor
	// Copy regular list
	LList newList;
	LList list;
	list.print("Empty list:");
	newList.print("Empty list:");
	list.append('a');
	list.append('0');
	list.print("Operation: append(a, 0)");
	newList = list;
	assert(list.length() == newList.length());
	// Copy empty list
	LList blank;
	list = blank;
	newList = blank;
	list.print("Empty list:");
	newList.print("Empty list:");
	assert(list.isEmpty() && newList.isEmpty());
	// Copy list w/ 1 element
	list.append('a');
	newList = list;
	newList.print("Operation: append(a)");
	assert(newList.length() == 1);
	// Copy copied list
	LList otherList(newList);
	assert(otherList.length() == 1 && otherList.remove('a'));
	// Copy list with 20 elements
	list = blank;
	newList = blank;
	list.print("Operation: append(char(48))");
	populate(list, 20, 48);
	newList = list;
	assert(newList.length() == 20);
}

void testD() {
	// Tests insertion in the beginning of the list
	LList newList;
	LList list;
	list.print("Empty list:");
	populate(newList, 3, 'a');
	newList.cons('z');
	newList.print("Operation: cons(z, c, b, a)");
	list.append('z');
	list.append('c');
	list.append('b');
	list.append('a');
	assert(newList == list);
}

void testE() {
	// Tests reverse
	// Populated list
	LList newList;
	LList list;
	// Empty list
	list.print("Empty list:");
	list.reverse();
	newList = list;
	assert(list==newList);
	// Populated list
	populate(newList, 3, 'a');
	newList.cons('z');
	newList.print("Operation: cons(z, c, b, a)");
	list.append('a');
	list.append('b');
	list.append('c');
	list.append('z');
	newList.print("Reversed previous list");
	newList.reverse();
	assert(newList==list);
}

void testF() {
	// Tests remove
	// General cases
	LList newList;
	newList.print("Empty list:");
	populate(newList, 3, 'a');
	newList.cons('z');
	newList.print("Operation: cons(z, c, b, a)");
	assert(newList.remove('c'));
	newList.print("Operation: remove(c)");
	assert(newList.remove('z'));
	newList.print("Operation: remove(z)");
	// Non-existent item
	assert(!newList.remove('c'));
	newList.print("Operation: remove(c)");
	// Last element
	assert(newList.remove('a'));
	newList.print("Operation: remove(a)");
	// Only element left
	assert(newList.remove('b'));
	newList.print("Operation: remove(b)");
	// Empty list
	assert(!newList.remove('z'));
	newList.print("Operation: remove(z)");
}

void testG() {
	// Tests found
	// Empty list
	LList list;
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
}

void testH() {
	// Tests getFirst
	// Empty list
	bool hasFirst = true;
	LList list;
	char firstChar = list.getFirst(hasFirst);
	assert(!hasFirst);
	assert(firstChar == '\0');
	// Populated list
	populate(list, 3, 'a');
	LList newList(list); // Copy
	firstChar = list.getFirst(hasFirst);
	assert(hasFirst);
	assert(firstChar == 'c');
	assert(list==newList);
	// One item
	list.remove('a');
	list.remove('b');
	newList = list; // Copy
	firstChar = list.getFirst(hasFirst);
	assert(hasFirst);
	assert(firstChar == 'c');
	assert(list==newList);
}

void testI() {
	// Tests print
	LList list;
	list.print("Empty list:");
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
	list.print("Operation: cons({*, *, *, P, A, S, S, E, D, *, *, *})");
}

int main() {

	if(remove("output.txt") != 0) {
		cout << "Error clearing output file! Delete it before running the program.";
	}
	else {
		cout << "Output file cleared!\n\n";
	}

	testA();
	testB();
	testC();
	testD();
	testE();
	testF();
	testG();
	testH();
	testI();

	cout << "\n\n\nPASSED all tests successfully!\n\n\n";
}
