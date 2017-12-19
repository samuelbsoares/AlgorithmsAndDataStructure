/*
 * Person.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Samuel Bechepeche Soares
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// A person has a name, address,phone number,  and  e-mail address.
class Person {
	protected:
		string name;
		string address;
		string phone;
		string email;
		static unsigned int count;
		static unsigned int countStudent;
		const double MIN_RATIO = 10.0;
		const double MAX_RATIO = 12.0;
	public:
		Person() { count++; };
		Person(string name, string address, string phone, string email);
		virtual ~Person(); // Must be declared as virtual
		virtual string toString() const;
		static unsigned int created();
};

#endif /* PERSON_H_ */
