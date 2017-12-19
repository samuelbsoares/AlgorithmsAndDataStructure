#ifndef LLIST_H
#define LLIST_H
/* 
 *  Assignment #1, CPSC 2150
 * Student Last Name: B. Soares
 * Student First Name: Samuel
 * Student Number: 100271978
 * 
 */

// when we do NOT want to debug, we do #define
//#define NDEBUG
// we comment out #define NDEBUG when we do not want debug statements

class  LList {
   public:
      // build a list
      LList();
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
      // delete the first occurrence of ch in the list
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
      void print() const;
      
      // copy constructor
      LList(const LList&); 
      // destructor 
      ~LList();
      // overloaded assignment operator 
      LList& operator=(const LList& rtSide);
      // Compares two lists
      bool compareTo(LList rtSide);

   private:
      struct Node {
         char item;
         Node* next;
      };

      // pointer to the linked list
      Node* head;

      // for the assignment, you are NOT allowed to have a tail pointer
      // i.e. one that points to the last node of the list
      
      // get the length of the list p
      static int length(Node *p);
      
      // Creates a new node
      static Node* makeNode(char ch, Node* nextNode = nullptr);

      // Recursively reverses the list
      Node* reverse(Node* node);

      // Recursively removes a given char
      bool remove(Node* node, char ch);

      // Recursively searches a given char
      bool found(const Node* node, char ch) const;

      // Recursively appends a given char
      void append(Node* node, char ch);

      // Delete whole list and deallocates memory
      void deleteAll(Node* node);

      // Copies the whole list
      void copyAll(Node* node);

      // Compares two lists
      bool compareNodes(Node* node, Node* nodeTwo);
};
#endif
