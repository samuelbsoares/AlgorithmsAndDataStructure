/*
 * BabyNames.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Samuel B. Soares
 */

	// Not the right approach! Should have used divide-and-conquer, sorting
	// all the files beforehand and merging them into the new file.

	// This approach would require a huge amount of available memory to generate
	// an array to keep all the names.


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>

#include "Name.h"

using namespace std;

string getStat(const string year);
void getStat();
string toStr(unsigned int i);
string toStr(double f);
void combinFilesToBinary();
void sort();
void get20Populars();

int main() {
    getStat();
    combinFilesToBinary();
    sort();
//    get20Populars();
//    cout << getStat("2010");
    return 0;
}

void get20Populars() {
    string filename = "allSortedNames.dat";
    ifstream input(filename.c_str(), ios::in | ios::binary);
    int counter = 0;
    filename = "20Names.txt";
    ofstream outputFile(filename.c_str(), ios::out);
    if (outputFile.fail()) {
        cout << "Couldn't open the file! Exiting program.";
        return;
    }
    while (!input.eof()) {
        vector<Name> v;
        queue<Name> q;
        if (!input.good()) break;
        Name name;
        input >> name;
        q.push(name);
        if (counter < 10) {
            v.push_back(name);
            q.pop();
        } else {
            if (q.size() > 10) q.pop();
        }

        // Inputs array and queue values
        for (int i = 0; i < counter; ++i) {
            cout << "from vector -> " << v[i];
            outputFile << v[i].toString(", ");
        }
        while (!q.empty()) {
            cout << "from queue -> " << q.front();
            outputFile << q.front().toString(", ");
            q.pop();
        }
    }
    input.close();
    outputFile.close();
};

void sort() {
    string filename = "allNames.dat";
    ifstream input(filename.c_str(), ios::in | ios::binary);
    vector<Name> names;
    if (input.fail()) {
        cout << "Couldn't open the file! Exiting program.";
        return;
    }
    while (!input.eof()) {
        string line;
        Name name;
        input >> name;
        if (!input.good()) break;
        names.push_back(name);
    }
    sort(names.begin(), names.end());

    input.close();

    filename = "allSortedNames.dat";
    ofstream outputFile(filename.c_str(), ios::out | ios::binary);
    if (outputFile.fail()) {
        cout << "Couldn't open the file! Exiting program.";
        return;
    }
    for(auto i = names.begin(); i < names.end(); i++)
        outputFile << *i;
    outputFile.close();
}

void combinFilesToBinary() {
    string filename = "allNames.dat";
    ofstream output(filename.c_str(), ios::out | ios::binary);
    ofstream out("out.txt", ios::out);
    unsigned int begin = 2010, end = 2015;
    for(unsigned int year = begin; year <= end; year++) {
    //    string filename = "./Names/Babynameranking" + year  + ".txt";
        string filename = "Babynameranking" + toStr(year)  + ".txt";
        ifstream input(filename.c_str());
        if (input.fail()) {
            cout << "Couldn't open the file! Exiting program.";
            return;
        }
        stringstream ss;

        string line;
        getline(input, line); // Skips first line (header)


        while (!input.eof()) {
            string maleName;
            unsigned int maleAmount;
            string femaleName;
            unsigned int femaleAmount;
            unsigned int rank;
            getline(input, line);
            if (!input.good()) break;
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            stringstream ss(line);
            ss >> rank >> maleName >> maleAmount >> femaleName >> femaleAmount;
            Name     male(maleName, year, maleAmount, true, rank),
                    female(femaleName, year, femaleAmount, false, rank);
            if (rank == 1000) {
                cout << "s";
            }
            output << male;
            output << female;
            out << male << endl;
            out << female << endl;
        }
        input.close();
    }
    output.close();
    out.close();
}

string getStat(const string year) {
    // Open a file
//    string filename = "./Names/Babynameranking" + year  + ".txt";
    string filename = "Babynameranking" + year  + ".txt";
    ifstream input(filename.c_str());
    if (input.fail()) {
        return "Couldn't open the file! Exiting program.";
    }

    // Read data
    unsigned int mp = 0;
    double mpp = 0.0;
    unsigned int fp = 0;
    double fpp = 0.0;
    unsigned int total = 0;

    string ans;
    string line;
    unsigned int rank;
    stringstream ss;

    getline(input, line); // Skips first line (header)

    while (!input.eof()) {
        string maleName;
        unsigned int maleAmount;
        string femaleName;
        unsigned int femaleAmount;
        getline(input, line);
        if (!input.good()) break;
        line.erase(remove(line.begin(), line.end(), ','), line.end());
        stringstream ss(line);
        ss >> rank >> maleName >> maleAmount >> femaleName >> femaleAmount;
        mp += maleAmount;
        fp += femaleAmount;
    }

    total = mp + fp;
    input.close();
    mpp = 100.00 * (double)mp / total;
    fpp = 100.00 * (double)fp / total;
    ans = year + ", " + toStr(mp) + ", " + toStr(mpp) + ", " +
            toStr(fp) + ", " + toStr(fpp) + ", " + toStr(mp + fp);
    input.close();
    return ans;
}

void getStat() {
    unsigned int begin = 2010;
    unsigned int end = 2015;
    string outputFilename = "stats.txt";
    string header = "Year, MalePopulation, MPP, FemalePopulation, FPP, TotalPopulation";
    ofstream output(outputFilename.c_str(), std::ofstream::out);
    output << header << "\n";
    for(unsigned int year = begin; year <= end; year++) {
        string line = getStat(toStr(year).c_str());
        output << line << "\n";
    }
    output.close();
}
