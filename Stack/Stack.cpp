/*
 * Stack.cpp
 *
 *  Created on: Sep 29, 2017
 *      Author: Samuel B. Soares
 */

#include <iostream>
#include "Stack.h"

template <typename T>
Stack<T>::Stack() {
	size = INITIAL_SIZE;
	rate = INITIAL_RATE;
	capacity = size;
	array = new T[size];
	top = -1;
//	base = -1;
}

// Constructor w/ arguments
template <typename T>
Stack<T>::Stack(long aSize, long aRate) {
	size = aSize;
	rate = aRate;
	capacity = size;
	array = new T[size];
	top = -1;
//	base = -1;
}

// Copy constructor
template <typename T>
Stack<T>::Stack(const Stack<T> & s) {
	*this = s;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Stack<T> & s) {
	   out << "{ ";
	   for(long i; i < s.size; ++i)
	      out << s.array[i] << " ";
	   out << "}";
	   return out;
}

// Overloaded assignment op.
template <typename T>
Stack<T>& Stack<T>::operator= (const Stack<T> & s) {
	if(size != s.size) {
		size = s.size;
		if(!array) {
			delete[] array;
		}
		array = new T[size];
	}
	rate = s.rate;
	capacity = size;
	top = s.top;
	for(long i = 0; i < top; ++i) {
		array[i] = s.array[i];
	}
}

// Destructor
template <typename T>
Stack<T>::~Stack() {
//	base = -1;
	top = -1;
	delete[] array;
}

// Push
template <typename T>
void Stack<T>::push(T t) {
	if(!hasCapacity()) {
		growArray();
	}
	top = (top == -1) ? 0 : top + 1;
	array[top] = t;
}

// Check capacity
template <typename T>
bool Stack<T>::hasCapacity() {
	return (top == size - 1);
}

// Grows the array
template <typename T>
void Stack<T>::growArray() {
	T * t = new T[size + rate];
	for(long i = 0; i < size; ++i) {
		t[i] = array[i];
	}
	capacity += rate;
	size = size + rate;
	delete[] array;
	array = t;
}

// Pop
template <typename T>
T Stack<T>::pop() {
	if(top == -1)
		return;
	return array[top--];
}

// Pop
template <typename T>
T Stack<T>::peek() {
	if(top == -1)
		return;
	return array[top];
}
