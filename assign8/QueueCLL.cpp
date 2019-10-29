// FILE: QueueCLL.cpp
// IMPLEMENTS: QueueCLL (see QueueCLL.h for documentation.)
//
// INVARIANT for the QueueCLL class:
//   1. The number of items in the QueueCLL is stored in the member
//      variable numItems.
//   2. The items themselves are stored in a circular linked list
//      of Nodes.
//      2.1 The member variable rear_ptr points to the rear of the
//          QueueCLL (tail node of the circular linked list).
//          heap[0] through heap[used - 1].
//      2.2 The rear_ptr is set to the null address if the circular
//          linked list (thus queue) is empty.

#include <iostream>
#include <cassert>  // provides assert
#include <cstdlib>  // provides size_t
using namespace std;

#include "QueueCLL.h"

QueueCLL::QueueCLL() : rear_ptr(NULL), numItems(0)
{

}

QueueCLL::QueueCLL(const QueueCLL& src) : rear_ptr(0), numItems(src.numItems)
{
    if(!src.empty())
   {
       rear_ptr = new Node;
       rear_ptr->data = src.rear_ptr->data;
       Node *srcCur = src.rear_ptr->link;
       Node *thisCur = rear_ptr;
       for(size_type i = 1; i < src.numItems; ++i)
       {
           thisCur->link = new Node;
           thisCur = thisCur->link;
           thisCur->data = srcCur->data;
           srcCur = srcCur->link;
       }
       thisCur->link = rear_ptr;
   }
}

QueueCLL::~QueueCLL()
{
    Node *prev = rear_ptr;

    while(numItems != 0)
    {
        rear_ptr = rear_ptr->link;
        delete prev;
        prev = rear_ptr;
        --numItems;
    }
}

QueueCLL& QueueCLL::operator=(const QueueCLL& rhs)
{
    if(this != &rhs)
   {
       if(numItems != 0)
       {
           Node *prev = rear_ptr->link;
           rear_ptr = rear_ptr->link->link;
           while(numItems != 1)
           {
               rear_ptr = rear_ptr->link;
               delete prev;
               prev = rear_ptr;
               --numItems;
           }
           delete rear_ptr;
       }
       if(!rhs.numItems == 0)
       {
           rear_ptr = new Node;
           rear_ptr->data = rhs.rear_ptr->data;
           Node *current = rhs.rear_ptr->link;
           Node *thisCur = rear_ptr;

           for(size_type i = 1; i < rhs.numItems; ++i)
           {
               thisCur->link = new Node;
               thisCur = thisCur->link;
               thisCur->data = current->data;
               current = current->link;
           }
           thisCur->link = rear_ptr;
           numItems = rhs.numItems;
       }
   }
   return *this;
}

void QueueCLL::push(const value_type& entry)
{
    if(numItems == 0)
    {
        rear_ptr = new Node;
        rear_ptr->data = entry;
        rear_ptr->link = rear_ptr;
    }
    else
    {
        Node *newNode = new Node;
        newNode->data = entry;
        newNode->link = rear_ptr->link;
        rear_ptr->link = newNode;
        rear_ptr = newNode;
    }
    ++numItems;
}

QueueCLL::value_type QueueCLL::front( ) const
{
    assert(numItems > 0);

    return(rear_ptr->link->data);
}

void QueueCLL::pop( )
{
    assert(numItems > 0);

    if(numItems == 1)
        delete rear_ptr;
    else
    {
        Node *head = rear_ptr->link;
        rear_ptr->link = head->link;
        delete head;
    }
    --numItems;
}

QueueCLL::size_type QueueCLL::size() const
{
    return numItems;
}

bool QueueCLL::empty() const
{
    return (numItems == 0) ? true : false;
}

QueueCLL::value_type QueueCLL::peek(size_type n) const
{
    assert(numItems > 0);

    Node *current = rear_ptr->link;

    for(size_type i = 1; i < n; ++i)
        current = current->link;

    return(current->data);
}

