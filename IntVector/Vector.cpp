/*
 * Vector.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: Samuel B. Soares
 */

#include "Vector.h"

#include <algorithm>
#include <stdlib.h>
#include <iostream>
using namespace std;

/**
 * Implementation of the Class Vector
 */

// Prototype of helper function
template <typename T>
bool bSearch(T* array, int num, T value);

/**
 * Default Constructor
 */
template <typename T>
Vector<T>::Vector() {
    this->capacity = 1;
    this->size = 0;
    this->vector = new T[this->capacity];
}

/**
 * Constructor
 * @param capacity Vector capacity
 */
template <typename T>
Vector<T>::Vector(unsigned int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->vector = new T[capacity];
}

/**
 * Constructor
 * @param capacity Vector capacity
 * @param defaultValue Value to be used to fill the vector
 */
template <typename T>
Vector<T>::Vector(unsigned int capacity, T defaultValue) {
    this->capacity = capacity;
    this->size = capacity;
    this->vector = new T[capacity];
    for(unsigned int i = 0; i < this->size; ++i)
        this->vector[i] = defaultValue;
}

/**
 * Destructor
 */
template <typename T>
Vector<T>::~Vector() {
    delete[] this->vector;
}

/**
 * Adds an integer to the vector
 * @param element Integer to be added
 */
template <typename T>
void Vector<T>::add(T element) {
    // Expansion required
    if(this->capacity == this->size) {
        T* newVector = new T[++this->size];
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
template <typename T>
void Vector<T>::remove() {
    T* newVector = new T[--this->size];
    for(unsigned int i = 0; i < this->size; ++i)
        newVector[i] = this->vector[i];
    delete[] this->vector;
    this->vector = newVector;
}

/**
 * Size getter
 */
template <typename T>
unsigned int const Vector<T>::getSize() {
    return this->size;
}

/**
 * Capacity getter
 */
template <typename T>
unsigned int const Vector<T>::getCapacity() {
    return this->capacity;
}

/**
 * Returns the value of an element
 * @param index The element's index
 */
template <typename T>
T const Vector<T>::at(unsigned int const index) {
    return this->vector[index];
}

/**
 * Checks if the vector is empty
 */
template <typename T>
bool Vector<T>::isEmpty() {
    return (this->vector) ||
            this->size == 0;
}

/**
 * Clears the object's vector
 */
template <typename T>
void Vector<T>::clear() {
    this->capacity = 1;
    delete[] this->vector;
    this->size = 0;
    this->vector = new T[this->capacity];
}

/**
 * Finds the intersection between two objects
 * @param other Vector to find the intersection
 * @return New Vector object with unique values common
 * to both initial InVector objects
 */
template <typename T>
Vector<T> Vector<T>::intersect(Vector<T>& other) {
    Vector<T> ans(0, 0);
    T* sortedThis = new T[this->size];
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
template <typename T>
bool bSearch(T* array, int size, T value) {
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
