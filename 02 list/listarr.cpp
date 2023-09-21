//--------------------------------------------------------------------
//
//                                                       listarr.cpp
//
//  SOLUTION: Array implementation of the List ADT
//
//--------------------------------------------------------------------

#include "listarr.h"
using namespace std;
//--------------------------------------------------------------------

List::List(int maxNumber)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).
{
	cursor = -1;
	size = 0;
	maxSize = maxNumber;
	dataItems = new DataType[maxNumber];
}

//--------------------------------------------------------------------

List:: ~List()
// Frees the memory used by a list.

{
	delete[] dataItems;

}

//--------------------------------------------------------------------

void List::insert(const DataType& newDataItem)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	if (size >= maxSize)
		cout << "Full List" << endl;
	else if(size == 0)
	{
		dataItems[0] = newDataItem;
		cursor += 1;
		size += 1;
	}
	else
	{
		for (int i = size; i >= cursor; i--)
		{
			dataItems[i] = dataItems[i-1];
			cursor += 1;
			size += 1;
		}
		dataItems[cursor] = newDataItem;
	}
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.
{
	if (size == 0 || size == 1)
	{
		for (int i = 0; i < 2; i++)
			dataItems[i] = NULL;
		cout << "Empty List" << endl;
		cursor = -1;
		size = 0;
	}
	else if (size != 0)
	{
		for (int i = cursor + 1; i <= size; i++)
		{
			dataItems[i - 1] = dataItems[i];
		}
		size -= 1;	
		if (cursor > size-1)
			cursor = 0;
	}
}

//--------------------------------------------------------------------

void List::replace(const DataType& newDataItem)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.
{
	if (size == 0)
	{
		cout << "Empty List" << endl;
	}
	else if (size != 0)
	{
		dataItems[cursor] = newDataItem;
	}

}
//--------------------------------------------------------------------

void List::clear() 
// Removes all the data items from a list.
{
	if (size == 0)
	{
		cout << "Already Empty List" << endl;
	}
	else if (size != 0)
	{
		for (int i = 0; i < size; i++)
			dataItems[i] = NULL;
		size = 0;
		cursor = -1;
	}
}

//--------------------------------------------------------------------

bool List::isEmpty() const throw (logic_error)
// Returns true if a list is empty. Otherwise, returns false.
{
	if (size == 0)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------

bool List::isFull() const throw (logic_error)
// Returns true if a list is full. Otherwise, returns false.
{
	if (size == maxSize)
		return true;
	else
		return false;

}

//--------------------------------------------------------------------

void List::gotoBeginning() throw (logic_error)
// Moves the cursor to the beginning of the list.
{
	if (size == 0) return ;					
	else                                           
	{
		cursor = 0;
	}
}

//--------------------------------------------------------------------

void List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	cursor = size - 1;
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.
{
	if (cursor != size - 1)
	{
		cursor += 1;
		return true;
	}
	else
		return false;
}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	if (cursor != 0) {
		cursor -= 1;
		return true;
	}
	else
		return false;
}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)
// Returns the item marked by the cursor.

{
	return dataItems[cursor];
}

//--------------------------------------------------------------------

void List::showStructure() const
// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
    // pre-lab
	cout << "size = " << size << "\t" << "cursor = " << cursor << endl;
	for (int i = 0; i < maxSize; i++)
	{
		cout << "[ " << i << " ]\t";
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "  " << dataItems[i] << "  \t";
	}
	cout << endl;
}

//--------------------------------------------------------------------

//in-lab
void List::moveToNth(int n)
{
	char temp = NULL ;
	temp = dataItems[cursor];
	if (cursor < n)
	{
		for (int i = cursor; i < n; i++)
		{
			dataItems[i] = dataItems[i + 1];
		}
		dataItems[n] = temp;
		cursor = n;
	}
	else if (cursor > n)
	{
		for (int i = cursor-1; i >= n; i--)
		{
			dataItems[i+1] = dataItems[i];
		}
		dataItems[n] = temp;
		cursor = n;
	}
	else if (cursor == n)
	{
		cout << "Nothing change"<< endl; 
	}
	// in-lab 2

}

bool List::find(const DataType& searchDataItem)
{
	// in-lab 3
	int i = cursor;
	while (i<size)
	{
		if (dataItems[i] == searchDataItem)
		{
			cursor = i;
			return true;
		}
		i++;
	}
	cursor = size - 1;
	return false;
}