/*
 * Stack.h
 *
 *  Created on: Sep 29, 2017
 *      Author: samue
 */

#ifndef STACK_H_
#define STACK_H_

#include <iostream>

template <typename T>
class Stack {

public:
	// Constructor
	Stack();

	// Constructor
	Stack(long, long);

	// Copy constructor
	Stack(const Stack<T> &);

	// Overloaded assignment op.
	Stack<T>& operator= (const Stack<T> &);

	// Overloaded output stream
	template <typename K>
	friend std::ostream& operator<< (std::ostream&, const Stack<K> &);

	// Destructor
	~Stack();

	// Push
	void push(T);

	// Pop
	T pop();

	// Peek
	T peek();

private:
	T * array;

	const long INITIAL_SIZE = 1000;
	const long INITIAL_RATE = 2;

	long size;
	long rate;
	long capacity;

	long top;

	bool hasCapacity();
	void growArray();
//	void copyAll(Stack<T> &);
};

#endif /* STACK_H_ */
