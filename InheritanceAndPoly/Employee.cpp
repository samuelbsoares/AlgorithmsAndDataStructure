/*
 * Employee.cpp
 *
 * Implements the Employee Class, derived from the Person Class.
 *
 *	Created on: Apr 6, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include "Employee.h"
#include "Student.h"

unsigned int Employee::count = 0;

/**
 * Constructor with parameters
 */
Employee::Employee(string name, string address, string phone,
		string email, string office, long sallary, MyDate dateHired): Employee() {
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->email = email;
	this->sallaryInCents = sallary;
	this->dateHired = dateHired;
};

/**
 * Constructor that performs the check and increments the counter
 */
Employee::Employee(): Person() {
	checkRatio();
	++count;
};

/**
 * Performs the minimum ratio of Student/Employees and throws an exception
 * if conditions are not met.
 */
void Employee::checkRatio() {
	if(!(Employee::created() == 0 ||
	   (Student::created() / (double)count) > MIN_RATIO)) {
		cout << "Current Ratio is: " << (Student::created() / (double)count) << endl;
		throw runtime_error("You should admit more students before hiring another employee!");
	}
}

/**
 * String representation of the object
 */
string Employee::toString() const {
	return (string("Employee: ") + name);
};

/**
 * Counter getter
 */
unsigned int Employee::created() {
	return Employee::count;
};
