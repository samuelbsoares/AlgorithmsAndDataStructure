/*
 * Person.cpp
 *
 * Implements the Person Class.
 *
 *	Created on: Apr 6, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include "Person.h"

unsigned int Person::count = 0;
unsigned int Person::countStudent = 0;

/**
 * Implementation of the virtual destructor
 */
Person::~Person() { count--; };

/**
 * Complete Constructor
 */
Person::Person(string name, string address, string phone, string email) {
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->email = email;
	this->count++;
};

/**
 * String representation of the object
 */
string Person::toString() const {
	return (string("Person: ") + name);
};

/**
 * Counter getter
 */
unsigned int Person::created() {
	return Person::count;
};
