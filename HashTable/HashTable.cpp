/*
 * Hash.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: Samuel B. Soares
 */

#define ui unsigned int
#include "HashTable.h"

/*
 * Constructor
 * @param size Size of the Table
 * @param fnct Hash function
 * @param alpha Load factor
 */
HashTable::HashTable( ui size, int (*fnct)( int, int, int ), const double alpha ) {
	this->table = new int[ size ];
	this->probe = fnct;
	this->size = size;
	for( ui i = 0; i < this->size; ++i )
		this->table[ i ] = EMPTY;
	this->capacity = size;
	this->foundComparisons = 0;
	this->notFoundComparisons = 0;
	this->load_factor = alpha;
}

/*
 * Resets values from object to original state
 */
void HashTable::reset() {
	for( ui i = 0; i < this->size; ++i )
		this->table[ i ] = EMPTY;
	this->size = size;
	this->capacity = size;
	this->foundComparisons = 0;
	this->notFoundComparisons = 0;
}

/*
 * Destructor
 */
HashTable::~HashTable() {
	delete[] this->table;
}

/*
 * Returns number of comparisons performed
 * for items found in the table
 */
int HashTable::getFoundComp() const {
	return this->foundComparisons;
}

/*
 * Returns number of comparisons performed
 * for items not found in the table
 */
int HashTable::getNotFoundComp() const {
	return this->notFoundComparisons;
}

/*
 * Searches the Table for the given Key
 * @param key Key to be found
 * @return True if found, false otherwise
 *
 * postcondition:
 * 		comparisons counters are updated
 */
bool HashTable::search( int K ) {
	int comparisons = 0;
	for( unsigned int i = 0; i < this->size; ++i ) {
		comparisons++;
		int index = probe( K, i, this->size ); //this->h( probe( K, i, this->size ) );
		if( this->table[ index ] == EMPTY ) {
			this->notFoundComparisons += comparisons;
			return false;
		}
		else if( this->table[ index ] == K ) {
			this->foundComparisons += comparisons;
			return true;
		}
	}
	// Only if table is full
	this->notFoundComparisons += comparisons;
	return false;
}

/*
 * Inserts an element in the Table
 * @param K Key to be inserted
 */
void HashTable::insert( int K ) {
	for( unsigned int i = 0; i < this->size; ++i ) {
		int index = probe( K, i, this->size );//this->h( probe( K, i, this->size ) );
		if( this->table[ index ] == EMPTY ) {
			this->table[ index ] = K;
			this->capacity--;
			return;
		}
	}
}

/*
 * Basic Inernal Hash Function
 * @param K Key to be hashed
 */
int HashTable::h( int K ) const {
	return K % this->size;
}

/*
 * Sets a new Load Factor to the table
 * @param alpha New load factor
 */
void HashTable::setAlpha( double alpha ) {
	this->load_factor = alpha;
}
