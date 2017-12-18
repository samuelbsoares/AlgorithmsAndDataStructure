/*
 * This program performs the proposed tests in the HasTable class
 * to obtain Empirical results of comparisons performed for different
 * probing methods.
 *
 * TestHashTable.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: Samuel B. Soares
 */


// Define unsigned int to ui
#define ui unsigned int

// Includes
#include <iostream> 		// cout, endl
#include <iomanip> 			// setw
#include "HashTable.h" 		// class HashTable
#include <string> 			// string
#include <set> 				// set
#include <cmath> 			// log
#include <random> 			// random_devices, mt19937, uniform_int_distribution
#include <bits/random.h> 	// Due to a bug in eclipse for random lib, may be removed if not needed.

// Constants and random generator globals
const int HASH_TABLE_SIZE = 1999; 	// asked value
const int HASH2_PRIME = 1997; 		// largest prime smaller than 1999
//const ui NUM_OF_DISTINCT = 1000; 	// Fixed size of distinct numbers
const ui ITERATIONS = 100; 			// number of iterations
const int ALPHAS_TO_TEST = 6; 		// has to prime the length of the array ALPHAS
const double ALPHAS[ALPHAS_TO_TEST] = { 0.25f, 0.5f, 0.75f, 0.85f, 0.90f, 0.95f }; // Values of alpha
//const double ALPHAS[ALPHAS_TO_TEST] = { 0.5f };

// Size of the ansewer grid, ( Found, not Found X Linear, Quadadratic, Double Hash ).
const int ROWS = 2;
const int COLS = 3;

// Printing strings
const std::string labels1[] = { "LINEAR", "QUADRATIC", "DOUBLE HASH" };
const std::string labels2[] = { "Found", "Not Found" };
const std::string labels3[] = { "THEORETICAL", "EMPIRICAL", "DIFFERNCE", "(THE./EMP.)" };

// Random generator globals
std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<int> dis;

// Function prototypes
int getKey();
int linear( int K, int i, int TSize );
int quadratic( int K, int i, int TSize );
int double_hashing( int K, int i, int TSize );
double linFoundComp( double alpha );
double linNotFoundComp( double alpha );
double quadFoundComp( double alpha );
double quadNotFoundComp( double alpha );
double doubleFoundComp( double alpha );
double doubleNotFoundComp( double alpha );
ui testHash( const ui IT, const ui SIZE, const double alpha,
		HashTable * TL, HashTable * TQ, HashTable * TD, double results[ROWS][COLS] );
void printResults( double results[ROWS][COLS], std::ostream&, const double alpha );

// Expected values function array
typedef double (*functions)( double );
// Functions to compute Theoretical Values
functions expected_fncts[ROWS][COLS] = {
		{ linFoundComp, quadFoundComp, doubleFoundComp },
		{ linNotFoundComp, quadNotFoundComp, doubleNotFoundComp}
};

// Test
int main() {
	// initializes the random generator
	dis = std::uniform_int_distribution<int>(HashTable::MIN, HashTable::MAX);

	// Creates HashTable Objects
	HashTable TL( HASH_TABLE_SIZE, &linear, ALPHAS[0] );
	HashTable TQ( HASH_TABLE_SIZE, &quadratic, ALPHAS[0] );
	HashTable TD( HASH_TABLE_SIZE, &double_hashing, ALPHAS[0] );

	ui N;

	for( int i = 0; i < ALPHAS_TO_TEST; ++i ) {
		// Array to store comparisons
		double results[2][3] = { 0 };
		// Tests and prints results
		N = testHash( ITERATIONS, HASH_TABLE_SIZE, ALPHAS[i], &TL, &TQ, &TD, results );
		// Prints results
		printResults( results, std::cout, ALPHAS[i] );
	}

	std:: cout << N;
}

///////////////////////
// Testing functions //
///////////////////////

// Generates next random number
int getKey() { return dis( gen ); }

// Tests all three functions and returns a grid with the results as follows
//   Rows:    0 - Found, 1 - Not Found
//   Columns: 0 - Linear Probing, 1 - Quadratic probing, 2 - Double hash probing
ui testHash( const ui ITERATIONS, const ui SIZE, const double alpha,
		HashTable * TL, HashTable * TQ, HashTable * TD, double results[ROWS][COLS] ) {

	const ui DISTINCT = ( int ) std::ceil( SIZE * alpha );

	for( ui dummy = 0; dummy < ITERATIONS; ++dummy ) {
		// Resets all HashTable objects
		TL->reset();
		TL->setAlpha( alpha );
		TQ->reset();
		TQ->setAlpha( alpha );
		TD->reset();
		TD->setAlpha( alpha );

		// Set of distinct items that ARE present in the tables
		std::set<int> s1;
		while( s1.size() < DISTINCT )
			s1.insert( getKey() );
		std::set<int> s2(s1); // copies

		// Adds all items in tables
		while( !s2.empty() ) {
			int n = *s2.begin();
			s2.erase( n );
			TL->insert( n );
			TQ->insert( n );
			TD->insert( n );
		}

		// search all existing numbers
		while( !s1.empty() ) {
			int n = *s1.begin();
			s1.erase( n );
			TL->search( n );
			TQ->search( n );
			TD->search( n );
		}

		// Set of distinct items that are NOT present in the tables
		std::set<int> q1;
		while( q1.size() < DISTINCT ) {
			int i = getKey();
			if( s1.find( i ) == s1.end() ) {
				q1.insert( i );
			}
		}

		// search all NON-existing numbers
		while( !q1.empty() ) {
			int n = *q1.begin();
			q1.erase( n );
			TL->search( n );
			TQ->search( n );
			TD->search( n );
		}

		//   Rows:    0 - Found
		//            1 - Not Found
		//   Columns: 0 - Linear Probing
		//            1 - Quadratic probing
		//            2 - Double hash probing
		results[0][0] += TL->getFoundComp();
		results[0][1] += TQ->getFoundComp();
		results[0][2] += TD->getFoundComp();
		results[1][0] += TL->getNotFoundComp();
		results[1][1] += TQ->getNotFoundComp();
		results[1][2] += TD->getNotFoundComp();
	}

	// Divides by number of iteration to get the average
	for( int i = 0; i < 2; ++i )
		for( int j = 0; j < 3; ++j )
			results[i][j] /= ( ITERATIONS * DISTINCT );

	return DISTINCT;

}

/*
 * Prints the obtained results
 * @param results[][] Empirical results array
 * @param out Output ostream
 * @param alpha Load factor used to obtain the results
 */
void printResults( double results[ROWS][COLS], std::ostream& out, const double alpha ) {
	const int W = 15;
	const int W1 = 12;

	out << "\n+====================== NUMBER OF COMPARISONS FOR ALPHA = " <<
			std::fixed << std::setprecision(2) <<
			alpha << " ====================+\n" << std::setfill(' ') <<
			std::setprecision(5);

	for( int j = 0; j < COLS; ++j) {
			// Case header
			out << "| " << std::setw( W1 ) << labels1[j] << " |"
					<< std::setw( W ) << labels3[0] << " |"
					<< std::setw( W ) << labels3[1]  << " |"
					<< std::setw( W ) << labels3[2]  << " |"
					<< std::setw( W ) << labels3[3] << " |\n";

		for( int i = 0; i < ROWS; ++i ) {

			// Results
			out << "| " << std::setw( W1 ) << labels2[i] << " |";
			double e = expected_fncts[i][j]( alpha );
			double ratio = ( results[i][j] / e );
			// Theoretical
			out << std::setw( W ) << e << " |";
			// Empirical
			out << std::setw( W ) << results[i][j] << " |";
			// Difference
			out << std::setw( W ) << e - results[i][j] << " |";
			// Emp. / Theor.
			out << std::setw( W ) << ratio << " |\n";
		}
	}

	out << "+======================================="
			"===========================================+\n";
}

///////////////////////
// Hashing functions //
///////////////////////

// Linear probing hash function
int linear( int K, int i, int TSize ) {
	return ( K + i ) % TSize;
}

// Quadratic probing hash function
int quadratic( int K, int i, int TSize ) {
	return ( K + i * i ) % TSize;
}

// Double hash probing hash function
// h1 and h2 were coded inside for simplicity
int double_hashing( int K, int i, int TSize ) {
	int hash1 = K % TSize;
	int hash2 = HASH2_PRIME - ( i * K ) % HASH2_PRIME;
	return ( hash1 + hash2 ) % TSize;
}

//////////////
// Formulae //
//////////////

// Expected Comparison numbers for
// successful Linear Probing Searches
double linFoundComp( double alpha ) {
	return ( double )( 0.5 * ( 1 + 1 / ( 1 - alpha ) ) );
}

// Expected Comparison numbers for
// unsuccessful Linear Probing Searches
double linNotFoundComp( double alpha ) {
	return ( double )( 0.5 * ( 1 + 1 / ( ( 1 - alpha ) * ( 1 - alpha ) ) ) );
}

// Expected Comparison numbers for
// successful Quadratic Probing Searches
double quadFoundComp( double alpha ) {
	return ( double )( 1 - std::log( 1 - alpha ) - ( alpha / 2 ) );
}

// Expected Comparison numbers for
// unsuccessful Quadratic Probing Searches
double quadNotFoundComp( double alpha ) {
	return ( double )( 1 / ( 1 - alpha ) - alpha - std::log( 1 - alpha ) );
}

// Expected Comparison numbers for successful
// Double Hashing Probing Searches
double doubleFoundComp( double alpha ) {
	return ( double )( ( 1 / ( alpha ) ) * std::log( 1 / ( 1 - alpha ) ) );
}

// Expected Comparison numbers for unsuccessful
// Double Hashing Probing Searches
double doubleNotFoundComp( double alpha ) {
	return ( double )( 1 / ( 1 - alpha ) );
}
