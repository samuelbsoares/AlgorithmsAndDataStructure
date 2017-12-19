/*
 * Staff.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Samuel Bechepeche Soares
 */

#ifndef STAFF_H_
#define STAFF_H_

#include "Employee.h"

using namespace std;

// A staff member has a title.
class Staff: public Employee {
	protected:
		string title;
		static unsigned int count;
	public:
		string toString() const;
		Staff(string name, string address, string phone, string email,
				string office, long sallary, MyDate dateHired, string title);
		static unsigned int created();
};

#endif /* STAFF_H_ */
