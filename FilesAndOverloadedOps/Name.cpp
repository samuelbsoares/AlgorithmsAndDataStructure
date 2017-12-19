/*
 * Name.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: Samuel B. Soares
 */

#include "Name.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

string toStr(unsigned int i);
string toStr(double d);
string toStr(bool male);

Name::Name(string n, unsigned int y, unsigned int f, bool iM, unsigned int r) {
    this->name = n;
    this->year = y;
    this->frequency = f;
    this->isMale = iM;
    this->rank = r;
};

Name::Name() {
    this->name = "";
    this->year = 0;
    this->frequency = 0;
    this->isMale = false;
    this->rank = 0;
};

bool Name::operator >(const Name& n2) {
    return (frequency > n2.frequency &&
            name.compare(n2.name) > 0 &&
            isMale > n2.isMale &&
            year > n2.year);
    if (frequency > n2.frequency)
        return true;
    else if (frequency == n2.frequency) {
        if (name.compare(n2.name) > 0)
            return true;
        else if (name.compare(n2.name) == 0) {
            if (isMale > n2.isMale)
                return true;
            else if(isMale == n2.isMale) {
                if (year > n2.year)
                    return true;
            }
        }
    }
    return false;
};

bool Name::operator <(const Name& n2) {
    bool ans = false;
    if (frequency < n2.frequency)
        ans = true;
    else if (frequency == n2.frequency) {
        if (name.compare(n2.name) < 0)
            ans = true;
        else if (name.compare(n2.name) == 0) {
            if (isMale < n2.isMale)
                ans = true;
            else if(isMale == n2.isMale) {
                if (year < n2.year)
                    ans = true;
            }
        }
    }
    if(ans) {
        cout << *this << n2 << endl;
        cout.flush();
    }
    return ans;
};

bool Name::operator <=(const Name& n2) {
    if (frequency < n2.frequency)
        return true;
    else if (frequency == n2.frequency) {
        if (name.compare(n2.name) < 0)
            return true;
        else if (name.compare(n2.name) == 0) {
            if (isMale < n2.isMale)
                return true;
            else if(isMale == n2.isMale) {
                if (year <= n2.year)
                    return true;
            }
        }
    }
    return false;
};

string Name::toString() const {
    return toStr(frequency) + sStr + name + sStr + toStr(isMale) + sStr + toStr(year) + sStr + toStr(rank);
};

string Name::toString(string sep) const {
    return toStr(frequency) + sep + name + sep + toStr(isMale) + sep + toStr(year) + sep + toStr(rank);
};

bool Name::operator == (const Name& n2) {
    return (frequency == n2.frequency &&
            !name.compare(n2.name) &&
            isMale == n2.isMale &&
            year == n2.year);
};

ofstream& operator << (ofstream& out, Name &name) {
    int size = name.name.size();
    out.write(reinterpret_cast<char*>(&size), sizeof(int));
    out.write(name.name.c_str(), size);
//    out.write(reinterpret_cast<char*>(&name), sizeof(Name));
    out.write(reinterpret_cast<char*>(&name.frequency), sizeof(name.frequency));
    out.write(reinterpret_cast<char*>(&name.isMale), sizeof(name.isMale));
    out.write(reinterpret_cast<char*>(&name.rank), sizeof(name.rank));
    out.write(reinterpret_cast<char*>(&name.year), sizeof(name.year));
//    out.write(reinterpret_cast<char*>(&name), sizeof(Name));
    return out;
};

ifstream& operator >> (ifstream& in, Name &name) {
    int size;
    in.read(reinterpret_cast<char*>(&size), sizeof(int));
    char *buf = new char[size];
    in.read(buf, size);
    string str(buf, size);
    name.name = str;
    delete[] buf;

    in.read(reinterpret_cast<char*>(&name.frequency), sizeof(name.frequency));
    in.read(reinterpret_cast<char*>(&name.isMale), sizeof(name.isMale));
    in.read(reinterpret_cast<char*>(&name.rank), sizeof(name.rank));
    in.read(reinterpret_cast<char*>(&name.year), sizeof(name.year));
//    in.read(reinterpret_cast<char*>(&name), sizeof(Name));
    //in.read(reinterpret_cast<char*>(&name.name), sizeof(name.name));
    return in;
};

ostream& operator << (ostream& out, const Name& name) {
    out << name.toString() << "\n";
    return out;
};

istream& operator >> (istream& in, Name& name) {
    in >> name.frequency >> name.name >> name.isMale >> name.year >> name.rank;
    return in;
};

string toStr(unsigned int i) {
        stringstream ss;
        ss << i;
        string iStr;
        ss >> iStr;
        return iStr;
};

string toStr(double d) {
    stringstream ss;
    ss << d;
    string fStr;
    ss >> fStr;
    return fStr + "%";
};

string toStr(bool male) {
    return male ? "Male" : "Female";
};
