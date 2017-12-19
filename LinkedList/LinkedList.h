/*
 * LinkedList.h
 *
 *  Created on: Mar 8, 2017
 *      Author: Samuel Bechepeche Soares
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template<typename T>
class Node {
public:
    T element;
    Node<T>* next;
    Node();
    Node(T element);
};


template<typename T>
class Iterator {
public:
    Iterator(Node<T>* p) {
        current = p;
    }

    Iterator next() {
        current = current->next;
        return *this;
    }

    T content() {
        return current->element;
    }

    bool isEqual(const Iterator<T>& iterator) {
        return current == iterator.current;
    }

    bool operator == (const Iterator<T>& rhs) const
    {
        return current == rhs.current;
    }

    bool operator != (const Iterator<T>& rhs) const
    {
        return current != rhs.current;
    }
private:
    Node<T>* current;
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList();
    LinkedList(const LinkedList<T> &list);

    virtual ~LinkedList();

    void addFirst(T element);
    void addLast(T element);

    T removeFirst();
    T removeLast();

    void add(T element);
    void add(int index, T element);

    T get(int index) const;
    int indexOf(T element) const;
    bool isEmpty() const;
    int lastIndexOf(T element) const;

    void remove(T element);
    int getSize() const;
    void clear();

    T removeAt(int index);
    T set(int index, T element);

    Iterator<T> begin() const {
        return Iterator<T>(head);
    }

    Iterator<T> end() const {
        return Iterator<T>(tail->next);
    }
};

#endif /* LINKEDLIST_H_ */
