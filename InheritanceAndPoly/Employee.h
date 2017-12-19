/*
 * Employee.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Samuel Bechepeche Soares
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include "Person.h"
#include "MyDate.h"

using namespace std;

// An employee has an office, salary, and date-hired.
class Employee: public Person {
	protected:
		string office;
		long sallaryInCents;
		MyDate dateHired;
		static unsigned int count;
	public:
		Employee(string name, string address, string phone, string email, string office, long sallary, MyDate dateHired);
		Employee();
		~Employee() { --count; };
		void checkRatio();
		string toString() const;
		static unsigned int created();
};
#endif /* EMPLOYEE_H_ */
