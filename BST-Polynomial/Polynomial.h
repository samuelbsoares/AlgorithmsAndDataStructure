/*
 * Polynomial.h
 *
 *  Created on: Nov 7, 2017
 *      Author: Samuel Soares - 100271978
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>

class Polynomial {
private:
	class Node {
	public:
		Node * left;
		int coefficient;
		int degree;
		Node * right;
	};

	Node * root;
	int terms;

	// Generates a leaf (node)
    Node * makeLeaf( int c, int d );
    // Destroys the whole polynomial from a given root
	void destroyPolynomial( Node * & );

	// Concatenates all terms of the polynomial
	// in a string from the root
    void toString( Node *, std::string & ) const;
    // Evaluates the polynomial for x
    int evaluate( int x, Node * n ) const;
    // Recursivelly gets the coefficient with
    // the desired degree if existent
    // returns 0 if the term doesn't exist
	int coeff( int degree, Node * n ) const;
	// Derives each element w.r.t. x
    void derive( Node * root, Polynomial & poly ) const;

public:
	// Constructor with zero polynomial
	Polynomial();
	// Constructor with one term to be inserted
	Polynomial( int, int );
	// Destructor
	~Polynomial();
	// Copy constructor
	Polynomial( const Polynomial & );

	// Overloaded assignment operator
	Polynomial & operator =( Polynomial const & );

	// Gets the highest degree of the polynomial
	int degree() const;
	// Evaluates the polynomial for a given x
	int evaluate( int x ) const;
	// Returns the coefficient of the term with
	// the provided degree.
	// If it doesn't exist, returns 0
	int coeff( int degree ) const;
	// Returns the number of nonzero terms in the polynomial
	int numberOfTerms() const;
    // Determines if the polynomial is a zero polynomial
    bool isZero() const;
    // Inserts a term into the polynomial
    void insert( int, int );
    // Inserts a new element into the tree of the provided
    // root (Node *) with the provided degree and coefficient
    // If the degree already exists, adds the coefficient to
    // the existing term
    // If an insertion results in a zero coefficient term,
    // removes it from the polynomial
    // Returns a pointer to the new root term
    Node * insert( Node *, int, int );
    // Removes the polynomial with the given degree from the
    // tree woth the given root node if it exists
    // Returns a reference to the new root term
    Node * remove( Node *, int );
    // Adds all elements from the tree of the provided root node
    // in the same order ( root, right sub-tree, left-sub-tree)
    void addInOrder( const Node * n );
    // Outputs the string representation of the polynomial
	friend std::ostream & operator << ( std::ostream &, const Polynomial & );
	// Reads a new polynomial from the istream
	friend std::istream & operator >> ( std::istream &, Polynomial & );
	// Adds two polynomials and returns the resulting polynomial
    friend Polynomial operator +( const Polynomial &, const Polynomial & );
    // Returns the string representation of the polynomial
    std::string toString() const;
    // Returns the derivative of the polynomial
    Polynomial derive() const;
};

#endif /* POLYNOMIAL_H_ */
