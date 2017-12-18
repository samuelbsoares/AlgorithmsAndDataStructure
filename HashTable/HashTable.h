/*
 * Hash.h
 *
 *  Created on: Nov 27, 2017
 *      Author: Samuel B. Soares
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

// My defines and includes
#define ui unsigned int

#include <iostream> // cout

class HashTable {
private:
	// Value used for empty table slots
	const int EMPTY = -1;
	// The Hash Table
	int * table;
	// Table size
	ui size;
	// Remaining capacity
	ui capacity;
	// Load Factor
	float load_factor;
	// Cumulative counter of comparisons performed for keys found
	int foundComparisons;
	// Cumulative counter of comparisons performed for keys NOT found
	int notFoundComparisons;
	// Hashing function
	int (*probe)( int, int, int );
public:
	// Min and max values of Key values
	static const int MIN = 0;
	static const int MAX = 1073741824;
	// Constructor
	HashTable( ui size, int (*fnct)( int, int, int ), double alpha );//bool linear = true );
	// Destructor
	~HashTable();
	// Resets object to original state
	void reset();
	// Searches a given key
	bool search( int K );
	// Inserts a given key
	void insert( int K );
	// Hash function
	int h( int K ) const;
	// Gets the number of comparisons performed so far for objects found
	int getFoundComp() const;
	// Gets the number of comparisons performed so far for objects not found
	int getNotFoundComp() const;
	// Sets a new load factor value
	void setAlpha( double );
};

#endif /* HASHTABLE_H_ */
