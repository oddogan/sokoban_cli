/*
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * Onat Deniz Dogan <oddogan@protonmail.com> wrote this code. As long as you retain this 
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

#ifndef doublylinkedlist
#define doublylinkedlist

#include <iostream>
#include "node.h"

/* Declaration and Implementation of the Doubly-Linked List class */

template <class T>
class LinkedList
{
    private:
        Node<T> *head, *last; // Pointers to access
        Node<T> *prevPtr, *currPtr; // For traversal
        int listSize; // Element count in the list
        int position; // Position of the current node
    public:
        LinkedList();
        // Check list status
        int getListSize(void) const;
        bool listEmpty(void) const;
        // Traversal
        void reset(int pos = 0);
        void next(void);
        void previous(void);
        bool endOfList(void) const; // Indicate if reached to end
        int currentPosition(void) const; // Return current location
        // Insertion
        void insertNode(const T& item); // Insert after current node
        // Deletion
        T deleteLast(void);
        // Data retrieval or modification
        T& data(void) const; // Return the data of the current node
};

template <class T>
LinkedList<T>::LinkedList()
{
    listSize = 0;
    position = 0;
    head = NULL;
    last = NULL;
    prevPtr = NULL;
    currPtr = NULL;
}

template <class T>
void LinkedList<T>::insertNode(const T& item)
{
    if(listSize == 0) // If the list is empty
    {
        head = getNode(item); // Set the new node as the head node
        currPtr = head; // Set the current pointer to head
        listSize++; // Increase list size
        return;
    }
    // If the list is not empty
    currPtr->insertAfter(getNode(item)); // Insert the node after the current node
    listSize++; // Increase the list size
    next(); // Move to the new node
    return;
}

template <class T>
int LinkedList<T>::getListSize(void) const
{
    return listSize;
}

template <class T>
bool LinkedList<T>::listEmpty(void) const
{
    return listSize == 0;
}

template <class T>
void LinkedList<T>::reset(int pos)
{
    // Move the position to the given position
    // Default target is 0, i.e HEAD
    position = 0;
    currPtr = head;
    while (position != pos)
    {
        next();
    }
}

template <class T>
void LinkedList<T>::next(void)
{
    // If at the end of the list, don't move
    if(endOfList())
    {
        return;
    }
    // If not at the end, assign current pointer as the next node's pointer
    currPtr = currPtr->nextNode();
    position++;
}

template <class T>
void LinkedList<T>::previous(void)
{
    // If at the beginning, throw error and don't move
    if(currPtr == head)
    {
        cerr << "You are at the beginning of the list!" << endl;
        return;
    }
    // If not at the beginning, assign current pointer as the prev node's pointer
    currPtr = currPtr->prevNode();
    position--;
}

template <class T>
bool LinkedList<T>::endOfList(void) const
{
    return position == listSize-1;
}

template <class T>
int LinkedList<T>::currentPosition(void) const
{
    return position;
}

template <class T>
T LinkedList<T>::deleteLast(void)
{
    T temp;
    while(!endOfList()) // Move to the last node on the list
    {
        next();
    }
    if (listSize != 1) // If the last node is not HEAD
    {
        previous();
        temp = currPtr->deleteAfter()->data;
        listSize--;
    }
    else // If the last node is also HEAD
    {
        temp = currPtr->data;
    }

    return temp;
}

template <class T>
T& LinkedList<T>::data(void) const
{
    return currPtr->data;
}


#endif
