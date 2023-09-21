#include "queuearr.h"

template < class DT >
Queue<DT>::Queue(int maxNumber)
{
    maxSize = maxNumber + 1;
    front = maxSize - 1;
    rear = maxSize - 1;
    dataItems = new DT[maxSize];
}

template < class DT >
Queue<DT>::~Queue()
{
    delete[] dataItems;
}

template < class DT >
void Queue<DT>::enqueue(const DT& newDataItem)
{
    if (isFull() == true) {
        cout << "Error : Full Queue" << endl;
    }
    else {
        rear = (rear + 1) % maxSize;
        dataItems[rear] = newDataItem;
    }
}

template < class DT >
DT Queue<DT>::dequeue()
{
    DT dequeue_item;

    if (isEmpty() == true) 
    {
        cout << "Error : Empty Queue" << endl;
        front = maxSize - 1;
        rear = maxSize - 1;
    }
    else if (front - rear == -1)
    {
        front = (front + 1) % maxSize;
        dequeue_item = dataItems[front];
        front = maxSize - 1;
        rear = maxSize - 1;
        return dequeue_item;
    }
    else
    {
        front = (front + 1) % maxSize;
        dequeue_item = dataItems[front];
        return dequeue_item;
    }
}

template < class DT >
void Queue<DT>::clear()
{
    front = maxSize -1;
    rear = maxSize -1;

}

template < class DT >
bool Queue<DT>::isEmpty() const
{
    return (rear == front);
}

template < class DT >
bool Queue<DT>::isFull() const
{
    return ((rear + 1) % maxSize == front);
}

template < class DT >
void Queue<DT>::showStructure() const
{
    int j;   // Loop counter

    if (isEmpty())
        cout << "Empty queue" << endl;
    else
    {
        cout << "front = " << front << "  rear = " << rear << endl;
        for (j = 0; j < maxSize; j++)
            cout << j << "\t";
        cout << endl;
        if (rear > front)
            for (j = 0; j < maxSize; j++)
                if ((j > front) && (j <= rear))
                    cout << dataItems[j] << "\t";
                else
                    cout << " \t";
        else
            for (j = 0; j < maxSize; j++)
                if ((j > front) || (j <= rear))
                    cout << dataItems[j] << "\t";
                else
                    cout << " \t";
        cout << endl;
    }
  
}

 // In-lab operations
template < class DT >
void Queue<DT>::putFront(const DT& newDataItem)
{
    if (isFull()) 
    {
        cout << "Full Queue" << endl;
    }
    else
    {
        if (front - 1 < 0)
        {
            front = maxSize - 1;
            dataItems[front] = newDataItem;
        }
        else
            dataItems[front--] = newDataItem;
    }
}

template < class DT >
DT Queue<DT>::getRear()
{
    if (isEmpty() == true)
    { 
        cout << "Error : Empty Queue" << endl;
        return 0;
    }
    else
    {
        DT item;
        item = dataItems[rear];
        rear = (rear - 1) % maxSize;
        return item;
    }
}

template < class DT >
int Queue<DT>::getLength() const
{
       if (rear >= front) 
            return rear - front;
       else 
              return ((maxSize - front) + rear);
}