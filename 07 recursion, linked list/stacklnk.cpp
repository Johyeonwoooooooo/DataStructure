//--------------------------------------------------------------------
//
//  Laboratory 5    stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
//
//--------------------------------------------------------------------
#include "stacklnk.h"

//--------------------------------------------------------------------

template <class DT>
StackNode<DT>::StackNode(const DT& nodeData, StackNode* nextPtr)
{
    dataItem = nodeData;
    next = nextPtr;
}


//--------------------------------------------------------------------

template <class DT>
Stack<DT>::Stack(int ignored)
{
    top = NULL; 
}

//--------------------------------------------------------------------

template <class DT>
Stack<DT>:: ~Stack()
{
    clear();
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::push(const DT& newDataItem)
{
    if (isFull())
        cout << "Err-Stack is Full" << endl;
    else
        top = new StackNode<DT>(newDataItem, top); 
}

//--------------------------------------------------------------------

template <class DT>
DT Stack<DT>::pop()
{
    if (isEmpty())
        cout << "Err-Stack is Empty" << endl;
    else
    {
        DT item;
        StackNode<DT>* tempPtr;
        item = top->dataItem; 
        tempPtr = top;
        top = top->next;
        delete tempPtr;
        return item; 
    }
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::clear()
{
    StackNode<DT>* tempPtr;
    while (top != NULL)
    {
        tempPtr = top;
        top = top->next;
        delete tempPtr;
    }
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isEmpty() const
{
    if (top == NULL)
        return true;

    else return false;
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isFull() const
{
    StackNode<DT>* temp = new(nothrow)StackNode<DT> (NULL, nullptr);
    if (temp == nullptr)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------

template < class DT >
void Stack<DT>::showStructure() const

// Linked list implementation. Outputs the data items in a stack.
// If the stack is empty, outputs "Empty stack". This operation is
// intended for testing and debugging purposes only.

{
    StackNode<DT>* p;   // Iterates through the stack

    if (top == 0)
        cout << "Empty stack" << endl;
    else
    {
        cout << "top ";
        for (p = top; p != nullptr; p = p->next)
            cout << p->dataItem << " ";
        cout << "bottom" << endl;
    }
}