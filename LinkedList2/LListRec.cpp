/*
 *  Assignment #1, CPSC 2150
 * Student Last Name: Soares
 * Student First Name: Samuel
 * Student Number: 100271978
 *
 *  Created on: Sep 14, 2017
 */

#include "LList.h"
#include <iostream>

using std::cout;

/**
 * Constructor
 */
LList::LList() {
	head = nullptr;
}

/**
 * Copy constructor
 * @param list Linked List to be copied.
 */
LList::LList(const LList& list): LList() {
	copyAll(list.head);
}

/**
 * Destructor
 */
LList::~LList() {
	if (!isEmpty())
		deleteAll(head);
	head = nullptr;
}

/**
 * Overloaded assignment operator
 * @param rtSide A reference to the right side list of the operation
 * @return A pointer to itself
 */
LList& LList::operator=(const LList& rtSide) {
	if (this != &rtSide) {
		if (head != nullptr) {
			deleteAll(head);
			head = nullptr;
		}
		copyAll(rtSide.head);
	}
	return *this;
}


/**
 * Overloaded equals to operator
 */
bool LList::compareTo(LList rtSide) {
	return compareNodes(this->head, rtSide.head);
}

/**
 * Compare both lists based on a given starting Node
 * Both pointers must be non-null
 */
bool LList::compareNodes(LList::Node* ltSide, LList::Node* rtSide) {
	if (!ltSide && !rtSide)
		return true;
	if (ltSide && rtSide)
		return ltSide->item == rtSide->item &&
				compareNodes(ltSide->next, rtSide->next);
	else
		return false;
}

/**
 * Checks if the LList is empty
 */
bool LList::isEmpty() const {
	return head == nullptr;
}

/**
 * Gets the length of the LList
 * @return Length of the LList
 */
int LList::length() const {
	int count(0);
	Node* node = head;
	while (node != nullptr) {
		++count;
		node = node->next;
	}
	return count;
}

/**
 * Inserts a new node in the beginning of the LList
 * @param ch Char to be inserted
 * @return true if successful, false otherwise
 */
bool LList::cons(char ch) {
	bool ret = true;
	try {
		head = makeNode(ch, head);
		// Just to make sure the try/catch is working
//		if (length() > 100)
//			throw std::bad_alloc();
	} catch (std::bad_alloc& e) {
		cout << "\nException handled! (" << e.what() << ")\n\n";
		ret = false;
	}
	return ret;
}

/**
 * Appends a char to the end of the linked list
 * @param ch Char to be appended
 * @return true if successful, false otherwise
 */
bool LList::append(char ch) {
	bool ret = true;
	try {
		append(head, ch);
	} catch (std::bad_alloc& e) {
		cout << "\nException handled! (" << e.what() << ")\n\n";
		ret = false;
	}
	return ret;
}

/**
 * Recursively appends to a list
 * @param node Base Node
 */
void LList::append(LList::Node* node, char ch) {
	if (node == nullptr) {
		head = makeNode(ch);
		return;
	}
	if (node->next == nullptr) {
		node->next = makeNode(ch);
	} else {
		append(node->next, ch);
	}
}

/**
 * Removes the first occurrence of ch in the list
 * @param ch Char to be removed
 * @return true is removal occurs
 */
bool LList::remove(char ch) {
	return remove(head, ch);
}

/**
 * Recursively removes the first occurrence in the list
 * @param ch Char to be removed
 * @return Node to the
 */
bool LList::remove(Node* node, char ch) {
	// Empty list
	if (node == nullptr)
		return false;
	// Case 1st is a match
	if (node->item == ch && node == head) {
		head = node->next; // nullptr if length == 1
		delete node;
		return true;
	}
	// Normal case
	if (node->next != nullptr && node->next->item == ch) {
		Node* toRemove = node->next;
		node->next = toRemove->next; // nullptr if last
		delete toRemove;
		return true;
	}
	// Starts recursion if none of the cases occur
	return remove(node->next, ch);
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
bool LList::found(const Node* node, char ch) const {
	if (node == nullptr)
		return false;
	return (node->item == ch) ? true : (found(node->next, ch));
}

/**
 * Reverses the list
 */
void LList::reverse() {
	if (head == nullptr)
		return;
	Node* node = reverse(head);
	node->next = nullptr;
}

/**
 * Recursively reverses the list in the same order
 * @param node Pointer to the pivot Node
 * @return Pointer to the new head Node
 */
LList::Node* LList::reverse(LList::Node* node) {
	if (node->next == nullptr) {
		head = node;
	} else {
		Node* reverseNode = reverse(node->next);
		reverseNode->next = node;
	}
	return node;
}

/**
 * Prints every item in the LList
 */
void LList::print() const {
	cout << "[";
	Node* nodePointer = head;
	while (nodePointer != nullptr) {
		cout << nodePointer->item;
		if (nodePointer->next != nullptr) {
			cout << ", ";
		}
		nodePointer = nodePointer->next;
	}
	cout << "]\n";
}

/**
 * Gets the first item of the first element of the list
 * @param hasFist Is set to true if the list is not empty, false otherwise
 * @return The char in the first element of the list
 */
char LList::getFirst(bool& hasFirst) const {
	hasFirst = (!isEmpty());
	return (hasFirst) ? head->item : '\0';
}

/**
 * Generates a new Node
 * @param ch Value of the new Node
 * @param nextNode Node where the new Node should point to
 * @return Pointer to the new Node
 */
LList::Node* LList::makeNode(char ch, Node* nextNode) {
	Node* newNode = new Node;
	newNode->item = ch;
	newNode->next = nextNode;
	return newNode;
}

/**
 * Deletes recursively all subsequent Nodes
 * @param node Pointer to the start Node
 */
void LList::deleteAll(LList::Node* node) {
	if (node == nullptr)
        return;
	deleteAll(node->next);
	delete node;
}

/**
 * Copies the list recursively from a given Node
 * @param node Pointer to the start Node
 */
void LList::copyAll(LList::Node* node) {
	if (node != nullptr) {
		append(node->item);
		copyAll(node->next);
	}
}
