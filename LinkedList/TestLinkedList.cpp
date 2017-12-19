/*
 * TestLinkedList.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include "LinkedList.h"
#include "LinkedList.cpp"
#include <iostream>        /* cout, cin */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>         /* ceil */

using namespace std;

int const UP = 100;

int getInput();
void genLinkedList(int n, LinkedList<int> & list);
void printList(LinkedList<int> list);
void split(LinkedList<int> source, LinkedList<int>&frontList, LinkedList<int>& backList);
void merge(LinkedList<int>& merged, LinkedList<int> list1, LinkedList<int> list2);
void mergeSort(LinkedList<int>& list);

int main() {
    // Use the function from last assignment
    int n = getInput();

    //Test Problem 2
    cout << "Test-cases for Exercise 2:" << endl;
    LinkedList<int> list;
    genLinkedList(n, list);
    cout << "The random list: ";
    printList(list);

    //Test Problem 3
    cout << endl << "Test-cases for Exercise 3:" << endl;
    LinkedList<int> first;
    LinkedList<int> second;
    split(list, first, second);
    cout << "The list after splitting: ";
    printList(list);
    cout << "The first half of list: ";
    printList(first);
    cout << "The second half of list: ";
    printList(second);
    LinkedList<int> n1;
    LinkedList<int> n2;
    split(first, n1, n2);
    cout << "The first half of the first half of list: ";
    printList(n1);
    cout << "The second half of the first half of list: ";
    printList(n2);
    LinkedList<int> n3;
    LinkedList<int> n4;
    split(n1, n3, n4);
    cout << "The first half of the first half of the first half of list: ";
    printList(n3);
    cout << "The second half of the second half of the first half of list: ";
    printList(n4);
    LinkedList<int> n5;
    LinkedList<int> n6;
    split(n3, n5, n6);
    cout << "The first half of the first half of the first half of the first half of list: ";
    printList(n5);
    cout << "The second half of the second half of the second half of the first half of list: ";
    printList(n6);
    cout << endl;


    //Test Problem 5 (explicitly) and Problem 4 (implicitly)
    cout << endl << "Test-cases for Exercise 4 and 5:" << endl;
    mergeSort(list);
    cout << "The list after sorting: ";
    printList(list);
    // test for special cases
    LinkedList<int> l;
    l.add(1);
    mergeSort(l);
    cout << "List with one element: ";
    printList(l);
    l.add(-1);
    mergeSort(l);
    cout << "List with two elements: ";
    printList(l);
    l.clear();
    mergeSort(l);
    cout << "Empty list: ";
    printList(l);

    return 0;
}

/**
 * Helper function that asks the user for an input and
 * keeps asking until an integer in the range [0, 50]
 * is provided.
 * @return n Valid integer provided by user
 */
int getInput() {
    cout << "Enter a number between 0 and 50: ";
    int n;
    cin >> n;
    while (n < 0 || n > 50) {
        cout << "Invalid number, try again: ";
        cin >> n;
    }
    return n;
}

/**
 * Generates n random numbers in the range [0, UP) and
 * populates the LinkedList
 * @param n Number of numbers to be generated
 * @param list LinkedList
 */
void genLinkedList(int n, LinkedList<int> & list) {
    srand(time(NULL));
    for(int i = 0; i < n; ++i) {
        list.add(rand() % UP);
    }
}

/**
 * Prints the provided LinkedList
 * @param list LinkedList
 */
void printList(LinkedList<int> list) {
    cout << "<( ";
    for(int i = 0; i < list.getSize(); ++i)
        cout << list.get(i) << " ";
    cout << ")>" << endl;
}

/**
 * Splits the list into two sublists — one for the front half, and one for the back half.
 * If the list has odd elements, the first half should have the middle element.
 * @param source Original LinkedList
 * @param frontList First half
 * @param bakList Other half
 */
void split(LinkedList<int> source, LinkedList<int>&frontList, LinkedList<int>& backList) {
    // Clears both lists
    LinkedList<int> n;
    frontList = n;
    backList = n;
    int sSize = source.getSize();
    // Handles special cases
    if(sSize < 1) return;
    else if(sSize == 1) frontList.add(source.get(0));
    // Handles general case of size > 1
    else {
        int i = 0;
        Iterator<int> it = source.begin();
        for(; i < ceil(sSize / 2.0); ++i) {
            frontList.add(it.content());
            it = it.next();
        }
        for(; i < sSize; ++i) {
            backList.add(it.content());
            it = it.next();
        }
    }
}

/**
 * Takes two sorted in increasing order LinkedLists and merges them together into one
 * LinkedList that is also sorted in increasing order.
 * @param merged Final LinkedList
 * @param list1 A sorted LinkedList
 * @param list2 Another sorted LinkedList
 */
void merge(LinkedList<int>& merged, LinkedList<int> list1, LinkedList<int> list2) {
    // Clears resulting list
    merged.clear();
    Iterator<int> it1 = list1.begin();
    Iterator<int> it2 = list2.begin();
    // Iterates until one of the lists reaches their end
    while(it1 != list1.end() && it2 != list2.end()) {
        if(it1.content() > it2.content()) {
            merged.add(it2.content());
            it2 = it2.next();
        }
        else {
            merged.add(it1.content());
            it1 = it1.next();
        }
    }
    // Ensures that all elements are added
    while(it1 != list1.end()) {
        merged.add(it1.content());
        it1 = it1.next();
    }
    while(it2 != list2.end()) {
        merged.add(it2.content());
        it2 = it2.next();
    }
}


/**
 * Sorts a LinkedList usgin the MergeSort algorithm
 * @param list LinkedList to be sorted
 */
void mergeSort(LinkedList<int>& list) {
    // Base case
    if(list.getSize() < 2) return;

    // Recursive case
    LinkedList<int> left;
    LinkedList<int> right;
    split(list, left, right);

    // Sorts recursively
    mergeSort(left);
    mergeSort(right);

    // Merges both sub-lists together
    return merge(list, left, right);
}
