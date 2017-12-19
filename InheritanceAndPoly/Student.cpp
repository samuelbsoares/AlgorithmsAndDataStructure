/*
 * Student.cpp
 *
 *	Implements the Student Class, derived from the Person Class.
 *
 *  Created on: Apr 6, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include "Student.h"
#include "Employee.h"

using namespace std;

unsigned int Student::count = 0;

/**
 * Constructor performs the maximum ratio of Student/Employees and throws an exception
 * if conditions are not met. If no employees were hired, it allows the admission of
 * MAX_RATIO students.
 */
Student::Student(string name, string address, string phone, string email, Status status): Person() {
	if((Employee::created() == 0 && count <= MAX_RATIO) ||
	  (count + 1) / (double)Employee::created() <= MAX_RATIO) {
		this->name = name;
		this->address = address;
		this->phone = phone;
		this->email = email;
		this->status = status;
		this->count++;
	} else {
		cout << "Current Ratio is: " << ((count) / (double)Employee::created()) << endl;
		throw runtime_error("You should hire an Employee before admitting a new student!");
	}
};

/**
 * String representation of the object
 */
string Student::toString() const {
	return (string("Student: ") + name);
};

/**
 * Counter getter
 */
unsigned int Student::created() {
	return Student::count;
};
