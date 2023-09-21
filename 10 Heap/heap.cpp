//--------------------------------------------------------------------
//
//  Laboratory 13                                             heap.cpp
//
//  Actual implementation of class in the Heap ADT
//--------------------------------------------------------------------

#include "heap.h"

//--------------------------------------------------------------------


template<class DT>
Heap<DT>::Heap(int maxNumber)
{
    maxSize = maxNumber;
    size = 0;
    dataItems = new DT[maxSize];
}

template < class DT >
Heap<DT>::~Heap()
{
    delete[] dataItems;
    size = 0;
}

//--------------------------------------------------------------------

template < class DT >
void Heap<DT>::insert(const DT& newDataItem)
{
    if (isFull())
        cout << "Error : Full heap" << endl;
    else if(isEmpty())
    {
        size++;
        dataItems[size-1] = newDataItem;
    }
    else
    {
        size++;
        dataItems[size - 1] = newDataItem;
        int temp = size - 1;
        DT swap_helper;
        while (dataItems[temp].pty() > dataItems[(temp - 1) / 2].pty() && temp != 0)
        {
            swap_helper = dataItems[temp];
            dataItems[temp] = dataItems[(temp-1)/2];
            dataItems[(temp-1)/2] = swap_helper;
            temp = (temp - 1) / 2;
        }
    }
}

template < class DT >
DT Heap<DT>::removeMax()
     {
    if (isEmpty())
    {
        cout << "Error : Empty heap" << endl; 
        DT result;
        result.setPty(-1);
        return result;
    }
    else
    {
        DT result = dataItems[0];
        dataItems[0] = dataItems[size - 1];
        size--;
        int temp = 0;
        DT swap_helper;
        while ((dataItems[temp].pty() < dataItems[temp * 2 + 1].pty() || dataItems[temp].pty() < dataItems[temp * 2 + 2].pty()) && temp*2+1 < size)
        {
            if (dataItems[temp * 2 + 1].pty() >= dataItems[temp * 2 + 2].pty())
            {
                swap_helper = dataItems[temp];
                dataItems[temp] = dataItems[temp * 2 + 1];
                dataItems[temp * 2 + 1] = swap_helper;
                temp = temp * 2 + 1;
            }
            else
            {
                swap_helper = dataItems[temp];
                dataItems[temp] = dataItems[temp * 2 + 2];
                dataItems[temp * 2 + 2] = swap_helper;
                temp = temp * 2 + 2;
            }
        }
        return result;
    }
}

template < class DT >
void Heap<DT>::clear()
{
    size = 0;
}

//--------------------------------------------------------------------

template < class DT >
bool Heap<DT>::isEmpty() const
{
    if (size == 0)
        return true;
    else
        return false;
}

template < class DT >
bool Heap<DT>::isFull() const
{
    if (size == maxSize)
        return true;
    else
        return false; 
}

//--------------------------------------------------------------------

template < class DT >
void Heap<DT>::showStructure () const

// Outputs the priorities of the data in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].pty() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void Heap<DT>::showSubtree ( int index, int level ) const

// Recursive partner of the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].pty();   // Output dataItems's pty
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void Heap<DT>::writeLevels() const
{
    if (isEmpty())
        cout << "Error : Empty heap" << endl;
    else
    {
        int print = 1;  //  프린트할 개수
        int index = 0;  // 인덱스

        while (index < size)
        {
            for (int i = 0; i < print; i++)
            {
                if (index + i < size)
                    cout << dataItems[index + i].pty() << " ";
                else
                    break;
            }
            index += print;
            print *= 2;
            cout << endl;
        }
    }
}