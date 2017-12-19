/*
 * Student.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Samuel Bechepeche Soares
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include "Person.h"

// A  student  has  class  status  (freshman,  sophomore,  junior,  or senior).
class Student: public Person {
	public:
		enum Status { freshman, sophomore, junior, senior };
		Student(string name, string address, string phone, string email, Status status);
		string toString() const;
		static unsigned int created();
	protected:
		const string statusStrings[4] = { "Freshman", "Sophomore", "Junior", "Senior" };
		Status status;
		static unsigned int count;
};

#endif /* STUDENT_H_ */
