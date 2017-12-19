/*
 * TestCode.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: SeP
 */
#include <iostream>

// For exercise 2
#include "IntVector.h"

// For exercise 3
#include "Vector.h"
#include "Vector.cpp"
using namespace std;

// For exercise 1
int* doubleCapacity(const int* list, int size);
void print(const int* const list, const int size);

int main() {
   // Exercise 1
   cout << "Exercise 1" << endl;
   int size = 5;
   int* list = new int[size];
   print(list, size);
   list = doubleCapacity(list, size);
   print(list, size << 1);

   // Exercise 2
   cout << endl << endl << "Exercise 2" << endl;
   IntVector myVector;
   // Store numbers 1, 2, 3, 4, 5, ...,10 to the vector
   for(int i = 9; i < 20; i++)
      myVector.add(i + 1);
   // Display the numbers in the vector
   cout << "Numbers in the vector: ";
   for(unsigned int i = 0; i < myVector.getSize(); i++)
      cout << myVector.at(i);
   // Remove the last element
   myVector.remove();
   IntVector myVector2(5, 13);
   cout << "\nThe capacity of myVector2 is : " << myVector2.getCapacity();
   if(! myVector.isEmpty())
      cout << "\nThe myVector is not empty.";
   myVector2.add(17);
   IntVector myVector3 = myVector.intersect(myVector2);
   cout << "\nThe intersection between myVector and myVector2 is : ";
   for(unsigned int i = 0; i < myVector3.getSize(); i++)
      cout << myVector3.at(i) << " ";
   myVector2.clear();
   if(myVector2.isEmpty())
      cout << "\nThe myVector2 is empty.";
   // Increase the size of vector dynamically
   for(int i = 0; i < 100; i++)
      myVector2.add(i+1);
   cout << "\nThe capacity of myVector2 is : "<< myVector2.getCapacity() <<endl;

   // Exercise 3
   cout << endl << endl << "Exercise 2" << endl;
   Vector<int> v1;
   // Store numbers 1, 2, 3, 4, 5, ...,10 to the vector
   for(int i = 0; i < 20; i++)
      v1.add(i + 1);
   // Display the numbers in the vector
   cout << "Numbers in the vector: ";
   for(unsigned int i = 0; i < v1.getSize(); i++)
      cout << v1.at(i);
   // Remove the last element
   v1.remove();
   Vector<int> v2(5, 4);
   cout << "\nThe capacity of v2 is : " << v2.getCapacity();
   if(!v1.isEmpty())
      cout << "\nThe v1 is not empty.";
   v2.add(7);
   v2.add(9);
   v2.add(15);
   Vector<int> v3 = v1.intersect(v2);
   cout << "\nThe intersection between v1 and v2 is : ";
   for(unsigned int i = 0; i < v3.getSize(); i++)
      cout << v3.at(i) << " ";
   v2.clear();
   if(v2.isEmpty())
      cout << "\nThe v2 is empty.";
   // Increase the size of vector dynamically
   for(int i = 0; i < 100; i++)
      v2.add(i+1);
   cout << "\nThe capacity of v2 is : "<< v2.getCapacity() <<endl;
   return 0;
}

int* doubleCapacity(const int* list, int size) {
   int* newList = new int[size*2];
   int i = 0;
   for(; i < size; ++i) {
      newList[i] = list[i];
   }
   for(; i < size << 1; ++i) {
      newList[i] = 0;
   }
   delete[] list;
   return newList;
}

void print(const int* const list, const int size) {
   cout << "(";
   for(int i = 0; i < size - 1; ++i) {
      cout << list[i] << ", ";
   }
   cout << list[size - 1] << ")" << endl;
}
