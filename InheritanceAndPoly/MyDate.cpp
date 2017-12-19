/*
 * MyDate.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include <sstream>
#include <string>

#include "MyDate.h"

using namespace std;

/**
 * Complete Constructor
 */
MyDate::MyDate(unsigned int aDay, unsigned int aMonth, unsigned int aYear) {
	day = aDay;
	month = aMonth;
	year = aYear;
};

/**
 * String representation of the object
 */
string MyDate::toString() {
	stringstream ss;
	ss << this-> day << "-" << this->month << "-" << this->year;
	return ss.str();
}

