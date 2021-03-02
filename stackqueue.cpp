/*
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * Onat Deniz Dogan <oddogan@protonmail.com> wrote this code. As long as you retain this 
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

/*
#include "stackqueue.h"
#include <iostream>
using namespace std;

// StackQueue constructor, default values 0
template <class T>
StackQueue<T>::StackQueue(): front(0), rear(0), count(0){}

template <class T>
bool StackQueue<T>::is_full()
{
    return count == maxSize;
}

template <class T>
void StackQueue<T>::push_front(const T &state)
{
    if(is_full())
    {
        cerr << "Queue overflow!" << endl;
        exit(1);
    }

    count++;
    stackList[rear] = state;
    rear = (rear + 1) % maxSize;
}
*/
