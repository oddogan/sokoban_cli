/*
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * Onat Deniz Dogan <oddogan@protonmail.com> wrote this code. As long as you retain this 
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

#ifndef node
#define node

#include <iostream>

/* Declaration and Implementation of Node class */
template <class T>
class Node
{
    private:
        Node<T> *next; // Pointer to the next node in list
        Node<T> *prev; // Pointer to the previous node in list
    public:
        T data; // Data stored in node
        Node(const T &item, Node<T> *ptrNext=NULL); // Constructor, default next is 0
        // List modification methods
        void insertAfter(Node<T> *p); // add a node after this node
        Node<T>* deleteAfter(void); // delete the node after this node
        Node<T>* nextNode(void) const; // get the address of the next node
        Node<T>* prevNode(void) const; // get the address of the previous node
};

template <class T>
Node<T>::Node(const T &item, Node<T> *ptrNext): data(item), next(ptrNext), prev(NULL){}

template <class T>
Node<T>* Node<T>::nextNode(void) const
{
    return next;
}

template <class T>
Node<T>* Node<T>::prevNode(void) const
{
    return prev;
}


template <class T>
void Node<T>::insertAfter(Node<T> *p)
{
    p->next = NULL; // Set new node's next to current next node
    p->prev = this; // Set new node's prev to current node
    next = p; // Set current next node to new node
}

template <class T>
Node<T>* Node<T>::deleteAfter(void)
{
    // If no nodes after this node:
    if(next == NULL)
        return NULL;
    // Save the address of the node that will be deleted
    Node<T> *tempPtr = next;
    // delete next node by copying its next address to the current
    next = tempPtr->next; // Set new next to other node
    if(next != NULL)
        tempPtr->next->prev = this; // Set new next node's prev as current
    return tempPtr; // Return deleted node
}

// Define a function to dynamically allocates a node and initializes
template <class T>
Node<T> *getNode(const T &item, Node<T> *nextPtr = NULL)
{
    Node<T> *newNode; // pointer declaration
    newNode = new Node<T>(item, nextPtr); // Allocate memory and initalize
    // If not successful:
    if(newNode == NULL)
    {
        cerr << "Memory allocation failed!" << endl;
        exit(1);
    }
    return newNode; // Return the address of the created node
}

#endif
