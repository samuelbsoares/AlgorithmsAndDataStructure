/*
 * Assignment #2, CPSC 2150
 * Student Last Name: Soares
 * Student First Name: Samuel
 * Student Number: 100271978
 *
 *  Created on: Sep 22, 2017
 */

#include "LList.h"
#include <iostream>
#include <cassert>
#include <string>
#include <fstream>

using std::cout;

/**
 * Constructor
 */
LList::LList() {
	out.open("output.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	resetAll();
}

/**
 * Constructor to set capacity and growth rate
 */
void LList::setCapAndGrowth(int capacity, int growthRate) {
	this->capacity = capacity;
	this->growthRate = growthRate;
	resetAll();
}

/**
 * Copy constructor
 * @param list Linked List to be copied.
 */
LList::LList(const LList& list) {
	out.open("output.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	head = NULL_INT;
	free = 0;
	copyAll(list);
}

/**
 * Destructor
 */
LList::~LList() {
	out.close();
	delete[] array;
}

/**
 * Overloaded assignment operator
 * @param rtSide A reference to the right side list of the operation
 * @return A pointer to itself
 */
LList& LList::operator=(const LList& rtSide) {
	if (this != &rtSide) {
		copyAll(rtSide);
	}
	return *this;
}

/**
 * Overloaded assignment operator
 * @param rtSide A reference to the right side list of the operation
 * @return A pointer to itself
 */
bool LList::operator==(const LList& rtSide) {
	// Evaluates empty lists
	// If both are empty, returns true
	if(head == NULL_INT && rtSide.head == NULL_INT) {
		return true;
	}
	// If only one is empty, returns false
	if(head == NULL_INT || rtSide.head == NULL_INT) {
		return false;
	}
	Node p = array[head];
	Node q = rtSide.array[rtSide.head];
	// while elements are equal and a next element exists for both
	while(p.item == q.item &&
			p.next != NULL_INT && q.next != NULL_INT) {
		p = array[p.next];
		q = rtSide.array[q.next];
	}
	// true if reached the end with equal elements
	return (p.next == NULL_INT || q.next == NULL_INT);
}

/**
 * Checks if the LList is empty
 */
bool LList::isEmpty() const {
	return (head == NULL_INT &&
			capacity == size);
}

/**
 * Gets the length of the LList
 * @return Length of the LList
 */
int LList::length() const {
	int count(0);
	int node = head;
	while (node != NULL_INT) {
		++count;
		node = array[node].next;
	}
	return count;
}

/**
 * Inserts a new node in the beginning of the LList
 * @param ch Char to be inserted
 * @return true if successful, false otherwise
 */
bool LList::cons(char ch) {
	bool ret = false;
	try {
		// test array capacity
		if(!hasCapacity()) {
			growArray();
		}
		int newFree = (array[free].next == NULL_INT) ? -1 : array[free].next;
		array[free] = makeNode(ch, head);
		head = free;
		free = newFree;
		--capacity;
		ret = true;
	} catch (std::exception& e) {
		cout << "\nException handled! (" << e.what() << ")\n\n";
	}
	return ret;
}

/**
 * Checks if the array has capacity for one more element
 * @return true if there is enough capacity, false otherwise
 */
bool LList::hasCapacity() {
	return (capacity > 0);
}

/**
 * Doubles the size of the array
 */
void LList::growArray() {
	Node *newArray = new Node[size * growthRate];
	capacity = (size * growthRate) - size; // Only newly generated are computed
	int currentFree = (free == NULL_INT) ? size : free;
	int currentHead = head;
	int i = 0;
	// copies the old nodes into the new array
	for(; i < size; ++i) {
		if(i == currentFree && array[currentFree].next != NULL_INT)
			currentFree = array[currentFree].next;
		newArray[i].item = array[i].item;
		newArray[i].next = array[i].next;
	}
	// links the last free to the rest of the new nodes
	for(; i < size * growthRate - 1; ++i) {
		newArray[i].item = LList::EMPTY_CHAR;
		newArray[i].next = i + 1;
	}
	newArray[i].item = LList::EMPTY_CHAR;
	newArray[i].next = NULL_INT;
	// sets the new array
	free = currentFree;
	head = currentHead;
	delete[] array;
	array = newArray;
	size *= growthRate;
}

/**
 * Appends a char to the end of the linked list
 * @param ch Char to be appended
 * @return true if successful, false otherwise
 */
bool LList::append(char ch) {
	bool ret = true;
	try {
		if(!hasCapacity())
			growArray();
		append(head, ch);
	} catch (std::exception& e) {
		cout << "\nException handled! (" << e.what() << ")\n\n";
		ret = false;
	}
	return ret;
}

/**
 * Recursively appends to a list
 * @param node Base Node
 */
void LList::append(int node, char ch) {
	// Empty array
	if(node == NULL_INT) {
		cons(ch);
	}
	// Last item
	else if(array[node].next == NULL_INT) {
		int firstFree = free;
		free = array[free].next;
		array[firstFree] = makeNode(ch);
		array[node].next = firstFree;
		--capacity;
	}
	// Starts recursion
	else {
		append(array[node].next, ch);
	}
}

/**
 * Removes the first occurrence of ch in the list
 * @param ch Char to be removed
 * @return true is removal occurs
 */
bool LList::remove(char ch) {
	// Empty
	if (isEmpty()) {
		return false;
	}
	return remove(head, ch);
}

/**
 * Recursively removes the first occurrence in the list
 * @param ch Char to be removed
 * @return Node to the
 */
bool LList::remove(int node, char ch) {
	// No match
	if(node == NULL_INT) {
		return false;
	}
	// Case 1st is a match
	if(array[node].item == ch && node == head) {
		array[node].item = EMPTY_CHAR;
		head = array[node].next; // NULL_INT if length == 1
		array[node].next = free;
		free = node;
		capacity++;
		return true;
	}
	// Normal case
	if(array[node].next != NULL_INT && array[array[node].next].item == ch) {
		int toRemove = array[node].next;
		array[node].next = array[toRemove].next; // NULL_INT if last
		array[toRemove].next = free;
		array[toRemove].item = EMPTY_CHAR;
		free = toRemove;
		capacity++;
		return true;
	}
	// Starts recursion if none of the cases occur
	return remove(array[node].next, ch);
}

/**
 * Checks the occurrence of ch in the list
 * @param ch Char to be searched
 * @return true is ch present
 */
bool LList::found(char ch) const {
	return found(head, ch);
}

/**
 * Recursively checks the occurrence of ch in the list
 * @param ch Char to be searched
 * @return true is ch present
 */
bool LList::found(int node, char ch) const {
	if (node == NULL_INT) {
		return false;
	}
	return (array[node].item == ch) ? true : (found(array[node].next, ch));
}

/**
 * Reverses the list
 */
void LList::reverse() {
	if (head == NULL_INT) {
		return;
	}
	int node = reverse(head);
	array[node].next = NULL_INT;
}

/**
 * Recursively reverses the list in the same order
 * @param node Pointer to the pivot Node
 * @return Pointer to the new head Node
 */
int LList::reverse(int node) {
	if (array[node].next == NULL_INT) {
		head = node;
	}
	else {
		int reverseNode = reverse(array[node].next);
		array[reverseNode].next = node;
	}
	return node;
}

/**
 * Prints every item in the LList
 */
void LList::print() {
	cout << "\n\n***********************\n* Dumping Nodes Array *\n***********************\n";
	cout << "Free: " << free << "\n";
	cout << "Head: " << head << "\n\n";
	cout << "Index \tItem \tNext\n";
	for(int i = 0; i < size; ++i) {
		cout << i <<
				"\t" << (array[i].item == EMPTY_CHAR ? '#' : array[i].item) <<
				"\t" << array[i].next << "\n";
	}
}

/**
 * Gets the first item of the first element of the list
 * @param hasFist Is set to true if the list is not empty, false otherwise
 * @return The char in the first element of the list
 */
char LList::getFirst(bool& hasFirst) const {
	hasFirst = (!isEmpty());
	return (hasFirst) ? array[head].item : '\0';
}

/**
 * Generates a new Node
 * precondition: needs at least one free slot in the array and
 * 				 free memory to Allocate the new node
 * @param ch Value of the new Node
 * @param nextNode index of the node where the new Node should point to
 * @return index of the new Node
 */
LList::Node LList::makeNode(char ch, int nextNode) {
	// Creates new node
	Node * newNode = new Node();
	newNode->item = ch;
	newNode->next = nextNode;
	return *newNode;
}

/**
 * Deletes recursively All subsequent Nodes
 * DOES NOT DEAllOCATES MEMORY!!! MUST BE
 * DEAllOCATED FIRST!!!
 * @param node Pointer to the start Node
 */
void LList::resetAll() {
	array = new Node[size]; // current size
	for(int i = 0; i < size - 1; ++i) {
		array[i].item = LList::EMPTY_CHAR;
		array[i].next = i + 1;
	}
	array[size - 1].item = LList::EMPTY_CHAR;
	array[size - 1].next = NULL_INT;
	capacity = size;
	free = 0;
	head = NULL_INT;
}

/**
 * Copies the list recursively from a given Node
 * @param node Pointer to the start Node
 */
void LList::copyAll(const LList& list) {
	// Re-organizes this to have a clean free list
	resetAll();
	int nodeToCopy = list.head;
	int i = 0;
	int listSize = list.length();
	for(; i < listSize && nodeToCopy != NULL_INT; ++i) {
		cons(list.array[nodeToCopy].item);
		nodeToCopy = list.array[nodeToCopy].next;
	}
	// Sets free to the next free node
	free = i;
	size = list.size;
	capacity = list.capacity;
	reverse();
}

#ifndef NDEBUG
void LList::print(const std::string& str) {
	cout << "\n\n" << str << "\n";
	out << "\n\n" << str << "\n";
	dumpNodesArray(); // could've created one single function with
	print(); 		  // different output streams for these functions
}
// dumps the array with expected values into the file
void LList::dumpNodesArray() {
	out << "\n\n***********************\n* Dumping Nodes Array *\n***********************\n";
	out << "Free: " << free << "\n";
	out << "Head: " << head << "\n\n";
	out << "Index \tItem \tNext\n";
	for(int i = 0; i < size; ++i) {
		out << i <<
				"\t" << (array[i].item == EMPTY_CHAR ? '#' : array[i].item) <<
				"\t" << array[i].next << "\n";
	}
}
#endif
