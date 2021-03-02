/*
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * Onat Deniz Dogan <oddogan@protonmail.com> wrote this code. As long as you retain this 
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

#ifndef stackqueue
#define stackqueue

#include <iostream>
using namespace std;

const int maxSize = 100;

template <class T>
class Stack
{
    private:
        T stackList[maxSize];
        int top;
    public:
        Stack();
        void Push(const T &item);
        T Pop();
        bool stack_empty() const;
        bool stack_full() const;
        T Peek() const;
};

template <class T>
Stack<T>::Stack(): top(-1){}

template <class T>
bool Stack<T>::stack_empty() const
{
    return top == -1; // If value is equal to -1, it is initial state
}

template <class T>
bool Stack<T>::stack_full() const
{
    return top == maxSize-1; // If top reached the item count
}

template <class T>
void Stack<T>::Push(const T &item)
{
    // Check if there is empty space
    if (stack_full())
    {
        cerr << "Stack overflow!" << endl;
        exit(1);
    }
    // Go to next address and copy the new element
    top++;
    stackList[top] = item;
}

template <class T>
T Stack<T>::Pop()
{
    T temp; // Temporary variable to hold the value
    // Check if there are any elements to pop
    if (stack_empty())
    {
        cerr << "Stack is empty!" << endl;
        exit(1);
    }
    // Hold the current top element
    temp = stackList[top];
    // Set new top address as the previous address
    top--;
    // Return the popped element
    return temp;
}

template <class T>
T Stack<T>::Peek() const
{
    return stackList[top];
}

/* Implementation of class StackQueue */

template <class T>
class StackQueue
{
    private:
        Stack<T> mLIFO, mFIFO;
        int moveCount;
    public:
        StackQueue();
        void push_front(const T &state);
        T pop_front();
        T pop_rear();
        bool is_full() const;
        bool is_empty() const;
};

// StackQueue constructor, default values 0
template <class T>
StackQueue<T>::StackQueue(): moveCount(0){}

template <class T>
bool StackQueue<T>::is_full() const
{
    return mLIFO.stack_full();
}

template <class T>
bool StackQueue<T>::is_empty() const
{
    return mLIFO.stack_empty();
}

template <class T>
void StackQueue<T>::push_front(const T &state)
{
    if(is_full())
    {
        cerr << "No moves left!" << endl;
        return;
    }

    while(!is_empty())
        mFIFO.Push(mLIFO.Pop());
    // Push the new state
    mFIFO.Push(state);
    moveCount++;
    while(!mFIFO.stack_empty())
        mLIFO.Push(mFIFO.Pop());
}

template <class T>
T StackQueue<T>::pop_front()
{
    if(is_empty() || moveCount==1)
    {
        cerr << "No older moves!" << endl;
        return mLIFO.Peek();
    }
    T temp;
    while(!is_empty())
        mFIFO.Push(mLIFO.Pop());
    // Pop the last state
    temp = mFIFO.Pop();
    moveCount--;
    while(!mFIFO.stack_empty())
        mLIFO.Push(mFIFO.Pop());
    return temp;
}

template <class T>
T StackQueue<T>::pop_rear()
{
    if(is_empty())
    {
        cerr << "No older moves!" << endl;
        exit(1);
    }
    T temp;
    // Pop the last state
    temp = mLIFO.Pop();
    moveCount--;
    return temp;
}



#endif
