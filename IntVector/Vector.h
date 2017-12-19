/*
 * Vector.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Samuel B. Soares
 */

#ifndef Vector_H_
#define Vector_H_

template <typename T>
class Vector {
private:
   unsigned int capacity;
   unsigned int size;
   T* vector;
public:
   // Constructors
   Vector();
   Vector(unsigned int capacity);
   Vector(unsigned int capacity, T defaultValue);
   Vector(const Vector<T>&);
   // Desctructor
   ~Vector();

   void add(T element);
   void remove();
   unsigned int const getSize();

   unsigned int const getCapacity();
   T const at(unsigned int const index);

   bool isEmpty();
   void clear();
   Vector<T> intersect(Vector& other);
};

#endif /* Vector_H_ */
