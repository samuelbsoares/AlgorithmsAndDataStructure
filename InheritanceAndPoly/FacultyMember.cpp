/*
 * FacultyMember.cpp
 *
 * Implements the Faculty Member Class, derived from the Employee Class.
 *
 *	Created on: Apr 6, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include "FacultyMember.h"
#include "Student.h"

unsigned int FacultyMember::count = 0;

/**
 * Constructor
 */
FacultyMember::FacultyMember(string name, string address, string phone, string email, string office, long sallary,
		MyDate dateHired, string title, string officeHours, unsigned int rank): Employee() {
		this->name = name;
		this->address = address;
		this->phone = phone;
		this->email = email;
		this->sallaryInCents = sallary;
		this->officeHours = officeHours;
		this->rank = rank;
		this->count++;
};

/**
 * String representation of the object
 */
string FacultyMember::toString() const {
	return (string("Faculty Member: ") + name);
};

/**
 * Counter getter
 */
unsigned int FacultyMember::created() {
	return FacultyMember::count;
};
