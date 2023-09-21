//--------------------------------------------------------------------
//
//  Laboratory 5                                        stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
//
//--------------------------------------------------------------------
#include "stackarr.h"

//--------------------------------------------------------------------

template <class DT>
Stack<DT>::Stack(int maxNumber)
{
    maxSize = maxNumber;
    top = -1;
    dataItems = new DT[maxSize];  
}

//--------------------------------------------------------------------

template <class DT>
Stack<DT>:: ~Stack()
{
    delete[] dataItems;
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::push(const DT& newDataItem)
{
    if (top == maxSize - 1)
    {
        cout << "Full Stack" << endl;
    }
    else 
    {
        top += 1;
        dataItems[top] = newDataItem;
    }
}


//--------------------------------------------------------------------

template <class DT>
DT Stack<DT>::pop()
{
    DT item = NULL;
    if (isEmpty() == true)
    {
        cout << "Empty Stack" << endl;
    }
    else
    {
        item = dataItems[top];
        top -= 1;
        return item;
    }
}
//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::clear()
{
    top = -1;
}   

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isEmpty() const
{
    if (top == -1)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isFull() const
{
    if (top == maxSize - 1)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------

template < class DT >
void Stack<DT>::showStructure() const

// Array implementation. Outputs the data items in a stack. If the
// stack is empty, outputs "Empty stack". This operation is intended
// for testing and debugging purposes only.

{
    int j;   // Loop counter

    if (top == -1)
        cout << "Empty stack" << endl;
    else
    {
        cout << "top = " << top << endl;
        for (j = 0; j < maxSize; j++)
            cout << j << "\t";
        cout << endl;
        for (j = 0; j <= top; j++)
            cout << dataItems[j] << "\t";
        cout << endl;
    }
}