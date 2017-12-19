/*
 * LinkedList.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: Samuel Bechepeche Soares
 */

#include "LinkedList.h"
#include <stdexcept>    /* runtime_exception */

using namespace std;

template<typename T>
Node<T>::Node() {
    element = new T;
    next = nullptr;
}

template<typename T>
Node<T>::Node(T element) {
    this->element = element;
    next = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList() {
    head = tail = nullptr;
    size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    head = tail = nullptr;
    size = 0;
    Node<T>* current = list.head;
    while (current != nullptr) {
        this->add(current->element);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while( current != 0 ) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = 0;
}

template<typename T>
void LinkedList<T>::addFirst(T element) {
    Node<T>* newNode = new Node<T>(element);
    newNode->next = head;
    size++;
    // First element
    if(tail == NULL) {
        tail = head;
    }
}

template<typename T>
void LinkedList<T>::addLast(T element) {
    // First element
    if(tail == NULL) {
        head = tail = new Node<T>(element);
    } else {
        tail->next = new Node<T>(element);
        tail = tail->next;
    }
    size++;
}

template<typename T>
void LinkedList<T>::add(T element) {
    addLast(element);
}

template<typename T>
void LinkedList<T>::add(int index, T element) {
    if(index == 0)
        addFirst(element);
    else if(index >= size)
        addLast(element);
    else {
        Node<T>* current = head;
        for(int i = 1; i < index; ++i)
            current = current->next;
        Node<T>* temp = current->next;
        current->next = new Node<T>(element);
        (current->next)->next = temp;
    }
}

template<typename T>
T LinkedList<T>::removeFirst() {
    if(size == 0)
        return NULL;
    else {
        Node<T>* temp = head;
        head = head->next;
        size--;
        if(head == NULL)
            tail == NULL;
        T element = temp->element;
        delete temp;
        return element;
    }
}

template<typename T>
T LinkedList<T>::removeLast() {
    if(size == 0)
        throw runtime_error("No elements in the list");
    else if (size == 1) {
        Node<T>* temp = head;
        head = tail = NULL;
        size = 0;
        T element = temp->element;
        delete temp;
        return element;
    } else {
        T element = tail->element;
        tail->next = NULL;
        size--;
        return element;
    }
}

template<typename T>
T LinkedList<T>::get(int index) const {
    if(index > size || index  < 0) {
        throw std::runtime_error("Index out of bounds!");
    }
    Node<T>* node = head;
    for(int i = 0; i < index; ++i) {
        node = node->next;
    }
    return node->element;
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template<typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template<typename T>
T LinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= size)
        throw std::runtime_error("Index out of bounds!");
    else if (index == 0)
        return removeFirst();
    else if (index == size - 1)
        return removeLast();
    else {
        Node<T>* previous = head;
        for (int i = 1; i < index; i++) {
            previous = previous->next;
        }
        T element = previous->next->element;
        previous->next = (previous->next)->next;
        size--;
        return element;
    }
}
//
//template<typename T>
//T LinkedList<T>::set(int index, T element) {
//}
//
//template<typename T>
//int LinkedList<T>::lastIndexOf(T element) const {
////    return NULL;
//    throw std::runtime_error("Erro!");
//}
//
//template<typename T>
//void LinkedList<T>::remove(T element) {
//}
//
//template<typename T>
//int LinkedList<T>::indexOf(T element) const {
//    throw std::runtime_error("Erro!");
//}
