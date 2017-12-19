/*
 * IntVector.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Samuel B. Soares
 */

#ifndef INTVECTOR_H_
#define INTVECTOR_H_

class IntVector {
private:
    unsigned int capacity;
    unsigned int size;
    int* vector;
public:
    // Constructors
    IntVector();
    IntVector(unsigned int capacity);
    IntVector(unsigned int capacity, int defaultValue);
    IntVector(const IntVector&);
    // Desctructor
    ~IntVector();

    void add(int element);
    void remove();
    unsigned int const getSize();

    unsigned int const getCapacity();
    int const at(unsigned int const index);

    bool isEmpty();
    void clear();
    IntVector intersect(IntVector& other);
};

#endif /* INTVECTOR_H_ */
