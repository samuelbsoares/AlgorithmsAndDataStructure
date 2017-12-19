/*
 * Test.cpp
 *
 *	Tests the Classes created for the Assignment 10 of the 1160 course
 *
 *  Created on: Mar 29, 2017
 *
 *      Author: Samuel Bechepeche Soares
 */

#include "Person.h"
#include "Student.h"
#include "Employee.h"
#include "Staff.h"
#include "FacultyMember.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main(int argc, char **argv) {

	// Variables to initialize objects
	string name = "Name";
	string address = "Street";
	string phone = "(604) 123-4567";
	string email = "em@ail.com";
	string office = "123A";
	unsigned int sallaryInCents = 1000000;
	Student::Status status = Student::sophomore;
	string title = "PHd";
	MyDate date(01, 10, 2014);
	string officeHours = "14:00 - 15:00";
	unsigned int rank = 10;
	Person *s;

	const int TOTAL = 1000; // Number of objects to generate
	const int STAFF_RATIO = 7; // Desired ratios of Staff
	const int FACULTY_RATIO = 2; // Desired ratios of Faculty Members

	// Initializes the seed
	srand(time(NULL));


	// Problems 4 & 5
	/**
	 * Generates pseudo-random numbers and creates objects according to the desired distribution:
	 * 91% Students
	 * 7% Staff
	 * 2% Faculty Members
	 *
	 * If an exception is thrown, prints the exception description.
	 */
	for(int i = 0; Person::created() < TOTAL; ++i) {
		int num = rand() % 100;
		if(num < FACULTY_RATIO) {
			try {
				s = new FacultyMember(name, address, phone, email, office, sallaryInCents, date, title, officeHours, rank);
			} catch (exception &e) { cout << e.what() << endl; }
		} else if(num < STAFF_RATIO) {
			try {
				s = new Staff(name, address, phone, email, office, sallaryInCents, date, title);
			} catch (exception &e) { cout << e.what() << endl; }
		} else {
			try {
				s = new Student(name, phone, address, email, status);
			} catch (exception &e) { cout << e.what() << endl; }
		}
	}

	cout << "\nFinal Stats:\n Student/Employee Ratio: " << ((double)Student::created() /
			(FacultyMember::created() + Staff::created())) << endl;
	cout << " Students: " << Student::created() << endl;
	cout << " Staff: " << Staff::created() << endl;
	cout << " Faculty Member: " << FacultyMember::created() << endl;
	cout << " Employee: " << Employee::created() << endl;
	cout << " Person: " << Person::created() << "\n\n";


	// Problem 3
	// Test generated here because the Ratio should not be severely affected by
	// creating only a few instances.
	cout << "String representation:\n";
	name = "Name Test";
	Person p(name, address, phone, email);
	cout << " " << p.toString() << endl;
	name = "Student Test";
	Student st(name, address, phone, email, Student::senior);
	cout << " " << st.toString() << endl;
	name = "Employee Test";
	Employee e(name, address, phone, email, office, sallaryInCents, date);
	cout << " " << e.toString() << endl;
	name = "Staff Test";
	Staff sta(name, address, phone, email, office, sallaryInCents, date, title);
	cout << " " << sta.toString() << endl;
	name = "Faculty Member Test";
	FacultyMember f(name, address, phone, email, office, sallaryInCents, date, title, officeHours, rank);
	cout << " " << f.toString() << endl;
}

