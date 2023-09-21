//--------------------------------------------------------------------
//
//  Laboratory 5                                        stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
//
//--------------------------------------------------------------------
#include "stacklnk.h"

//--------------------------------------------------------------------

template <class DT>
StackNode<DT>::StackNode(const DT& nodeData, StackNode* nextPtr) // 초기화, 생성자
{
    dataItem = nodeData;
    next = nextPtr;
}


//--------------------------------------------------------------------

template <class DT>
Stack<DT>::Stack(int ignored)  // ignored 구현
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
    StackNode<DT>* temp = new StackNode<DT>;
    temp -> dataItem = newDataItem;
    temp -> next = top;
    top = temp;

}

//--------------------------------------------------------------------

template <class DT>
DT Stack<DT>::pop()
{
    if (isEmpty() != true)
    {
        DT popdata = top->dataItem;
        StackNode<DT>* temp;
        temp = top;
        top = top->next;
        delete temp;
        return popdata;
    }
    else
        cout << "Empty Stack";
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::clear()
{
    while (isEmpty() == false) {
        StackNode<DT>* temp = top;
        top = top->next;
        delete temp;
    }
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isEmpty() const
{
    if (top == NULL)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isFull() const
{

    StackNode<DT>* temp = new(nothrow)NodeType<DT>; 
    if (temp == NULL)
        return true;
    else {
        delete temp;
        return false;
    }
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