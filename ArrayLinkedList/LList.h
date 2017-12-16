#ifndef LLIST_H
#define LLIST_H

/* 
 * Assignment #2, CPSC 2150
 * Student Last Name: Soares
 * Student First Name: Samuel
 * Student Number: 100271978
 */

// when we do NOT want to debug, we do #define
//#define NDEBUG
// we comment out #define NDEBUG when we do not want debug statements

#include <fstream>

class  LList {
   public:
      // build a list
      LList();
      // Sets capacity and growth rate
      void setCapAndGrowth(int capacity, int growthRate);
      // determine if the list is empty
      bool isEmpty() const;
      // give length of list
      int length() const;
      // insert ch at the beginning (at the front) of the linked list
      // return true if successful, false otherwise
      bool cons(char ch);
      // append ch to the end of the linked list
      // return true if successful, false otherwise
      bool append(char ch);
      // delete the first occurence of ch in the list
      // if the deletion happens, return true,  false otherwise
      bool remove(char ch); 
      // search ch in the list, return true if found, false otherwise
      bool found(char ch) const;
      // if the list is empty,  getFirst is set to false and the character '\0' 
      // is returned, otherwise it returns the first character of the list and 
      // hasFirst is set to true
      char getFirst(bool& hasFirst) const;
      // reverses the list, the original list is mutated 
      void reverse();
      // print the list to standard output started with a  '[' and finished
      // with a ']' followed by an end-of-line  
      // dumps the array when NDEBUG is defined
      void print();
      void print(const std::string&);

      // copy constructor
      LList(const LList&); 
      // destructor 
      ~LList();
      // overloaded assignment operator 
      LList& operator = (const LList& rtSide);
      // overloaded assignment operator
      bool operator == (const LList& rtSide);

   private:
      struct Node {
    	  char item;
    	  int next;
      };
      
      // head and free indexes
      int head;
      int free;

      // null constant
      static const int NULL_INT = -1;
      // initial capacity of the list
      static const int INITIAL_CAPACITY = 5;
      // growth rate of the list array
      static const int INITIAL_GROTH_RATE = 2;
      // empty char used to fill empty nodes
      static const char EMPTY_CHAR = '\0';

      // current capacity of the list
      int capacity = INITIAL_CAPACITY;
      // current total size of the list
      int size = capacity;
      // growth rate of the list
      int growthRate = INITIAL_GROTH_RATE;

      // node array
      Node * array;

      // Output stream
      std::ofstream out;

      // functions to allow recursion (overloaded from public functions)
      int reverse(int node);
      bool found(const Node* node, char ch) const;
      void append(int node, char ch);
      bool remove(int node, char ch);
      bool found(int node, char ch) const;

      // helper methods
      // creates a new node
      Node makeNode(char ch, int nextNode = NULL_INT);
      // copies a list
      void copyAll(const LList& list);
      // deletes aint the content of the list and sets it to be empty
      void resetAll();
      // checks if the list has available capacity
      bool hasCapacity();
      // grows the array
      void growArray();

      #ifndef NDEBUG
      // dump the array
      void dumpNodesArray();
      #endif
};

#endif
