/*
 * FacultyMember.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Samuel Bechepeche Soares
 */

#ifndef FACULTYMEMBER_H_
#define FACULTYMEMBER_H_

#include "Employee.h"

using namespace std;

// A faculty member has office hour and a rank.
class FacultyMember: public Employee {
	protected:
		string officeHours;
		unsigned int rank;
		static unsigned int count;
	public:
		string toString() const;
		FacultyMember(string name, string address, string phone, string email, string office, long sallary,
				MyDate dateHired, string title, string officeHours, unsigned int rank);
		static unsigned int created();
};

#endif /* FACULTYMEMBER_H_ */
