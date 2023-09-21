#include "listdbl.h"

template < class DT >
ListNode<DT>::ListNode(const DT& data, ListNode* priorPtr, ListNode* nextPtr)
{
    dataItem = data;
    prior = priorPtr;
    next = nextPtr;
}

// Constructor
template < class DT >
List<DT>::List(int ignored)
{
    head = nullptr;
    cursor = nullptr;
}

// Destructor
template < class DT >
List<DT>::~List()
{
    clear();
}


//------------ List manipulation operations ------------------

// Insert after cursor
template < class DT >
void List<DT>::insert(const DT& newDataItem)
{
    ListNode<DT>* newNode;

    if (isEmpty())
    {
        newNode = new ListNode<DT>(newDataItem, nullptr, nullptr);
        newNode->prior = newNode;
        newNode->next = newNode;
        newNode->dataItem = newDataItem;
        head = newNode;
    }
    else
    {
        newNode = new ListNode<DT>(newDataItem, cursor, cursor->next);
        cursor->next->prior = newNode;
        cursor->next = newNode;
    }
    cursor = newNode;
}

// Remove data item
template < class DT >
void List<DT>::remove()
{
    if (isEmpty())
        cout << "Error : Empty List" << endl;
    else
    {
        if (getLength() == 1)
        {
            clear();
        }
        else if (cursor == head)
        {
            cursor->prior->next = cursor->next;
            cursor->next->prior = cursor->prior;
            head = cursor->next;
            cursor = cursor->next;
        }
        else if (getLength() == 1)
        {
            clear();
        }
        else
        {
            cursor->prior->next = cursor->next;
            cursor->next->prior = cursor->prior;

            if (cursor->next != head)
                cursor = cursor->next;
            else
                cursor = head;
        }

    }
}

// Replace data item
template < class DT >
void List<DT>::replace(const DT& newDataItem)
{
    if (isEmpty())
        cout << "Error : Empty List" << endl;
    else
        cursor->dataItem = newDataItem;
}

// Clear list
template < class DT >
void List<DT>::clear()
{
    head = nullptr;
    cursor = nullptr;
}


//------------ List status operations ------------------

// List is empty
template < class DT >
bool List<DT>::isEmpty() const
{
    if (head == nullptr)
        return true;
    else
        return false;
}

// List is full
template < class DT >
bool List<DT>::isFull() const
{
     ListNode<DT>* temp = new(nothrow)ListNode<DT>(NULL,nullptr,nullptr);
        if (temp == nullptr)
            return true;
        else
        {
            delete temp;
            return false;
        }
}


//------------ List manipulation operations ------------------

// Go to beginning
template < class DT >
void List<DT>::gotoBeginning()
{
    if (!isEmpty())
    {
        cursor = head;
    }
    else
        cout << "Error : Empty List" << endl;
}

// Go to end
template < class DT >
void List<DT>::gotoEnd()
{
    if (!isEmpty())
    {
        while (cursor->next != head)
        {
            cursor = cursor->next;
        }
    }
    else
        cout << "Error : Empty List" << endl;
}

// Go to next data item
template < class DT >
bool List<DT>::gotoNext()
{
    if (cursor->next != head)
    {
        cursor = cursor->next;
        return true;
    }
    else
        return false;
}

// Go to prior data item
template < class DT >
bool List<DT>::gotoPrior()
{
    if (cursor == head)
        return false;
    else
    {
        cursor = cursor->prior;
        return true;
    }
}


template < class DT >
DT List<DT>::getCursor() const
{
    if (!isEmpty())
    {
        return cursor->dataItem;
    }
    else
        cout << "Error : Empty List" << endl;
}


//-----------------------------------------------------------

template < class DT >
void List<DT>::showStructure() const
{
    ListNode<DT>* p;   // Iterates through the list

    if (isEmpty())
        cout << "Empty list" << endl;
    else
    {
        p = head;
        do
        {
            if (p == cursor)
                cout << "[" << p->dataItem << "] ";
            else
                cout << p->dataItem << " ";
            p = p->next;
        } while (p != head);
        cout << endl;
    }
}


//-----------------------------------------------------------
// In-lab2 operation
template <class DT>
void List<DT>::reverse()
{
    if (isEmpty())
    {
        cout << "Error : Empty List" << endl;
    }
    else
    {
        ListNode<DT>* location = head;
        ListNode<DT>* temp = nullptr;
        do
        {
            temp = location->prior;
            location->prior = location->next;
            location->next = temp;
            location = location->prior;
        } while (location != head);
        head = head -> next;
    }
}

// In-lab3 operation
template <class DT >
int List<DT>::getLength() const
{
    int length = 0;
    if (!isEmpty())
    {
        ListNode<DT>* temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
            length++;
        }
        return length + 1;
    }
    else
        return length;
}

template <class DT>
int List<DT>::getPosition() const
{
    int position = 0;
    if (!isEmpty())
    {
        ListNode<DT>* temp = head;
        while (temp != cursor)
        {
            temp = temp->next;
            position++;
        }
        return position;
    }
    else
        return position;
}