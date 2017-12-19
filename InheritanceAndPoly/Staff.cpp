/*
 * Staff.cpp
 *
 * Implements the Staff Class, derived from the Employee Class.
 *
 *	Created on: Apr 6, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include "Staff.h"
#include "Student.h"

unsigned int Staff::count = 0;

/**
 * Constructor
 */
Staff::Staff(string name, string address, string phone, string email,
		string office, long sallary, MyDate dateHired, string title): Employee() {
		this->name = name;
		this->address = address;
		this->phone = phone;
		this->email = email;
		this->sallaryInCents = sallary;
		this->dateHired = dateHired;
		this->title = title;
		this->count++;
};

/**
 * String representation of the object
 */
string Staff::toString() const {
	return (string("Staff: ") + name);
};

/**
 * Counter getter
 */
unsigned int Staff::created() {
	return Staff::count;
};
