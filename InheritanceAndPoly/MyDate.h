/*
 * MyDate.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Samuel Bechepeche Soares
 */

#ifndef MYDATE_H_
#define MYDATE_H_

using namespace std;

//  Define a class named MyDate that contains the fields year, month, and day.
class MyDate {
		unsigned int day;
		unsigned int month;
		unsigned int year;
	public:
		MyDate() { };
		MyDate(unsigned int aDay, unsigned int aMonth, unsigned int aYear);
		string toString();
};

#endif /* MYDATE_H_ */
