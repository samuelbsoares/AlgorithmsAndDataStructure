/*
 * IntVector.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: Samuel B. Soares
 */

#include "IntVector.h"

#include <algorithm>
#include <stdlib.h>
#include <iostream>
using namespace std;

/**
 * Implementation of the Class IntVector
 */

// Prototype of helper function
bool bSearch(int* array, int num, int value);

/**
 * Default Constructor
 */
IntVector::IntVector() {
    int capacity = 1;
    int defaultValue = 0;
    this->capacity = capacity;
    this->size = 0;
    this->vector = new int[capacity];
    for(unsigned int i = 0; i < this->size; ++i)
        this->vector[i] = defaultValue;
}

/**
 * Constructor
 * @param capacity Vector capacity
 */
IntVector::IntVector(unsigned int capacity) {
    int defaultValue = 0;
    this->capacity = capacity;
    this->size = 0;
    this->vector = new int[capacity];
    for(unsigned int i = 0; i < this->size; ++i)
        this->vector[i] = defaultValue;
}

/**
 * Constructor
 * @param capacity Vector capacity
 * @param defaultValue Value to be used to fill the vector
 */
IntVector::IntVector(unsigned int capacity, int defaultValue) {
    this->capacity = capacity;
    this->size = capacity;
    this->vector = new int[capacity];
    for(unsigned int i = 0; i < this->size; ++i)
        this->vector[i] = defaultValue;
}

/**
 * Destructor
 */
IntVector::~IntVector() {
    delete[] this->vector;
}

/**
 * Adds an integer to the vector
 * @param element Integer to be added
 */
void IntVector::add(int element) {
    // Expansion required
    if(this->capacity == this->size) {
        int* newVector = new int[++this->size];
        this->capacity = this->size;
        for(unsigned int i = 0; i < this->size; ++i)
            newVector[i] = this->vector[i];
        newVector[this->size - 1] = element;
        delete[] this->vector;
        this->vector = newVector;
    // No expansion requires
    } else if (this->capacity > this->size) {
        this->vector[this->size++] = element;
    // Undesired behaviour!!!
    } else
        return;
}

/**
 * Removes the last element of the vector
 */
void IntVector::remove() {
    int* newVector = new int[--this->size];
    for(unsigned int i = 0; i < this->size; ++i)
        newVector[i] = this->vector[i];
    delete[] this->vector;
    this->vector = newVector;
}

/**
 * Size getter
 */
unsigned int const IntVector::getSize() {
    return this->size;
}

/**
 * Capacity getter
 */
unsigned int const IntVector::getCapacity() {
    return this->capacity;
}

/**
 * Returns the value of an element
 * @param index The element's index
 */
int const IntVector::at(unsigned int const index) {
    return this->vector[index];
}

/**
 * Checks if the vector is empty
 */
bool IntVector::isEmpty() {
    return (this->vector) ||
            this->size == 0;
}

/**
 * Clears the object's vector
 */
void IntVector::clear() {
    this->capacity = 1;
    delete[] this->vector;
    this->size = 0;
    this->vector = new int[this->capacity];
}

/**
 * Finds the intersection between two objects
 * @param other IntVector to find the intersection
 * @return New IntVector object with unique values common
 * to both initial InVector objects
 */
IntVector IntVector::intersect(IntVector& other) {
    IntVector ans(0, 0);
    int* sortedThis = new int[this->size];
    for(unsigned int i = 0; i < this->size; ++i)
        sortedThis[i] = this->vector[i];
    sort(sortedThis, sortedThis + this->size);
    for(unsigned int i = 0; i < other.getSize(); ++i) {
        if(bSearch(sortedThis, this->size, other.at(i)))
            if(other.at(i) != ans.at(ans.getSize() - 1) ||
                    ans.getSize() == 0)
                ans.add(other.at(i));
    }
    delete[] sortedThis;
    return ans;
}

/**
 * Helper function that implements the binary search
 * @param array Array to do the search
 * @param num Size of the array
 * @param value Value to be searched
 */
bool bSearch(int* array, int size, int value) {
    int mid;
    int lower = 0;
    int upper = size - 1;
    while(lower <= upper) {
        mid = (lower + upper) / 2;
        if(value > array[mid])
            lower = mid + 1;
        else if(value < array[mid])
            upper = mid - 1;
        else
            return true;
    }
    return false;
}
