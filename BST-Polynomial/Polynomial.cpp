/*
 * Polynomial.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: Samuel Soares - 100271978
 */

#include "Polynomial.h"
#include <cmath>
#include <string>

/*
 * Constructor
 */
Polynomial::Polynomial() {
	root = nullptr;
	terms = 0;
}

/*
 * Constructor with one term
 */
Polynomial::Polynomial( int d, int c ): Polynomial() {
	insert( root, d, c );
}

/*
 * Destructor
 */
Polynomial::~Polynomial() {
	destroyPolynomial( root );
}

/*
 * Copy constructor
 */
Polynomial::Polynomial( const Polynomial & p ): Polynomial() {
	addInOrder( p.root );
}

/*
 * Overloaded assignment operator
 */
Polynomial & Polynomial::operator =( Polynomial const & rhs ) {
	if( this != &rhs ) {
		destroyPolynomial( root ); // free
		addInOrder( rhs.root ); // copy content
	}
	return *this;
}

/*
 * Returns the degree of the polynomial's highest term.
 */
int Polynomial::degree() const {
	int d = -1;
	Node * n = root;
	while( n ) {
		d = n->degree;
		n = n->left;
	}
	return d;
}

/*
 * Returns a string representation of the Polynomial
 */
std::string Polynomial::toString() const {
	if( root == nullptr )
		return "0";
	std::string str = "";
	toString( root, str );
	return str;
}

/*
 * Builds all the string containing all string representations
 * of the polynomial's terms.
 * @param node A pointer to the root node
 * @param str A reference to the resulting string
 */
void Polynomial::toString( Node * node, std::string & str ) const {
	if( node == nullptr )
		return;

	toString( node->left, str );

	if( str.empty() ) { // Special case for 1st Term
		if( std::abs( node->coefficient ) > 1 ) // If coeff > 1, displays it
			str += std::to_string( node->coefficient );
		else if( node->coefficient == -1 )
			str += "-";
		// Otherwise, do nothing (leave blank string)
	}
	else { // General case
		str += " "; // Not first -> space
		if( node->coefficient > 0 ) { // Positive
			str += "+ ";
		}
		else // if( n->coefficient < 0 ) // Negative
			str += "- ";
		if( std::abs( node->coefficient ) > 1 ||
				( std::abs( node->coefficient ) && node->degree == 0 ) )
			str += std::to_string( std::abs( node->coefficient ) );
	}
	if( node->degree != 0 ) {
		str += "x";
		if( node->degree != 1 ) {
			str += "^";
			str += std::to_string( node->degree );
		}
	}

	toString( node->right, str );
}

/*
 * Overloaded << operator to print polynomials
 */
std::ostream & operator << ( std::ostream& out, const Polynomial & p ) {
	out << p.toString();
	return out;
}


/*
 * Overloaded >> operator to read polynomials
 */
std::istream & operator >> ( std::istream& in, Polynomial & p ) {
	int n;
	in >> n;
	while( n-- ) {
		int c, d;
		in >> c >> d;
		p.insert( c, d );
	}
	return in;
}

/*
 * Recursively removes the node with the term of the given degree
 * @param root A pointer to the root node
 * @degree Degree of the polynomial to be removed
 * @return A pointer to the resulting root node
 */
Polynomial::Node * Polynomial::remove( Node * root, int degree ) {
	// Empty
	if( root == nullptr )
		 return root;
	// Finds the Node with the requested degree
	if( root->degree < degree )
		root->left = remove( root->left, degree );
	else if( root->degree > degree )
		root->right = remove( root->right, degree );
	else {
		// Has one or no child
		if( root->right == nullptr ) {
			Node * returnNode = root->left;
			delete root;
			this->terms--;
			return returnNode;
		} else if( root->left == nullptr ) {
			Node * returnNode = root->right;
			delete root;
			this->terms--;
			return returnNode;
		}
		// Otherwise, it has two children
		// Then we need to get the largest predecessor
		Node * pre = root->left;
		while( pre->left != nullptr )
			pre = pre->left;
		// Instead of deleting the original node, copies the predecessor's
		// value into it and deletes the predecessor
		root->degree = pre->degree;
		root->coefficient = pre->coefficient;
		// Deletes the predecessor
		root->left = remove( root->left, pre->degree );
	}
	return root;
}

void Polynomial::insert( int c, int d ) {
	if( c != 0 )
		root = insert( root, c, d );
}

/*
 * Inserts a valid term to a the polynomial (coefficient != 0)
 * @param root A pointer to the root node
 * @param c Node's coefficient
 * @param d Node's degree
 * @return A pointer to the resulting root
 */
Polynomial::Node * Polynomial::insert( Node * root, int c, int d ) {
	// Empty node
	if( root == nullptr )
		return makeLeaf( c, d );
	// Same degree
	else if( root->degree == d ) {
		root->coefficient += c;
		if( root->coefficient == 0 )
			root = remove( root, d );
	}
	// Left
	else if ( root->degree > d )
		root->right = insert( root->right, c, d );
	// Right
	else if ( root->degree < d )
		root->left = insert( root->left, c, d );
	return root;
}

/*
 * Creates a new Node
 * @param c Node's coefficient
 * @param d Node's degree
 * @return A new node
 */
Polynomial::Node * Polynomial::makeLeaf( int c, int d ) {
	Polynomial::Node * newNode = new Polynomial::Node();
	newNode ->right = nullptr;
	newNode ->left = nullptr;
	newNode ->coefficient = c;
	newNode ->degree = d;
	this->terms++;
	return newNode;
}

/*
 * Overloaded + operator to add polynomials
 * @param aPoly Operand 1
 * @param bPoly Operand 2
 * @return New Polynomial equals to the sum of the two operands
 */
Polynomial operator +( const Polynomial & aPoly, const Polynomial & bPoly ) {
	Polynomial newPoly;
	newPoly.addInOrder( aPoly.root );
	newPoly.addInOrder( bPoly.root );
	return newPoly;
}

/*
 * Adds all childrem from node into the Polynomial
 * @param node Root of the tree to be inserted
 */
void Polynomial::addInOrder( const Node * node ) {
	if( node != nullptr ) {
		insert( node->coefficient, node->degree );
		addInOrder( node->right );
		addInOrder( node->left );
	}
}

/*
 * Evaluates the Polynomial for a given x
 * @param x Value of the variable x
 */
int Polynomial::evaluate( int x ) const {
	return evaluate( x, root );
}

/*
 * Evaluates all elements from tree with root node for a given x
 * @param x Value of the variable x
 * @param node Root of the tree containing the polynomial terms
 * @return The value of the polynomial for x
 */
int Polynomial::evaluate( int x, Node * node ) const {
	if( node == nullptr )
		return 0;
	return  node->coefficient *
			pow( x, node->degree ) +
			evaluate( x, node->left ) +
			evaluate( x, node->right );
}

/*
 * Returns the coefficient of an element
 * @param degree Degree of the element
 * @return Coefficient of the element of the given degree
 */
int Polynomial::coeff( int degree ) const {
	return coeff( degree, root );
}

/*
 * Returns the coefficient of an element
 * @param degree Degree of the element
 * @param node Root of the tree
 * @return Coefficient of the element of the given degree
 */
int Polynomial::coeff( int degree, Node * node ) const {
	if( node == nullptr )
		return 0;
	if( node->degree == degree )
		return node->coefficient;
	else if( degree < node->degree )
		return coeff( degree, node->right );
	else
		return coeff( degree, node->left );
}

/*
 * Returns the numbers pf elements in the tree
 */
int Polynomial::numberOfTerms() const {
	return terms;
}

/*
 * Recursively deletes all elements from the tree
 */
void Polynomial::destroyPolynomial( Polynomial::Node * & node ) {
	if( node != nullptr ) {
		destroyPolynomial( node->left );
		destroyPolynomial( node->right );
		delete node;
		node = nullptr;
		terms = 0;
	}
}

/*
 * Determines if the polynomial is a zero polynomial
 */
bool Polynomial::isZero() const {
	return ( root == nullptr );
}

/*
 * Derives a polynomial
 */
Polynomial Polynomial::derive() const {
	Polynomial poly;
	derive( root, poly );
	return poly;
}

/*
 * Recursively derives all nodes from a given root
 */
void Polynomial::derive( Node * root, Polynomial & poly ) const {
	// Base case
	if( root == nullptr )
		return;
	// Derive root
	int coefficient = root->coefficient * root->degree;
	int degree = root->degree - 1;
	// Only inserts into polynomial if result is valid
	if( coefficient != 0 && degree >= 0 )
		poly.insert( coefficient, degree );
	// Recursively derive children
	derive( root->left, poly );
	derive( root->right, poly );
}
