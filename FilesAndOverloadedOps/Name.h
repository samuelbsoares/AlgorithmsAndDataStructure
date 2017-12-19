/*
 * Name.h
 *
 *  Created on: Mar 26, 2017
 *      Author: SeP
 */

#ifndef NAME_H_
#define NAME_H_

#include <string>

using namespace std;

class Name {

public:
    string name;
    unsigned int year;
    unsigned int frequency;
    bool isMale;
    unsigned int rank;
    string sStr = " ";
    Name(string n, unsigned int y, unsigned int f, bool iM, unsigned int r);
    Name();
    string toString() const;
    string toString(string sep) const;
    //Operators
    bool operator<(const Name& n2);
    bool operator>(const Name& n2);
    bool operator<=(const Name& n2);
    bool operator==(const Name& n2);
    friend ofstream& operator << (ofstream& out, Name& name);
    friend ifstream& operator >> (ifstream& in, Name& name);
    friend ostream& operator << (ostream& out, const Name& name);
    friend istream& operator >> (istream& in, Name& name);
};

#endif /* NAME_H_ */
