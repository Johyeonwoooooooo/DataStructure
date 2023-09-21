#include "queuelnk.h"

template <class DT>
QueueNode<DT>::QueueNode(const DT& nodeData, QueueNode* nextPtr)
{
    dataItem = nodeData;
    next = nextPtr;
}

template <class DT>
Queue<DT>::Queue(int ignored)
{
    front = nullptr;
    rear = nullptr;
}

template<class DT>
Queue<DT>::~Queue()
{
    clear();
}

template<class DT>
void Queue<DT>::enqueue(const DT& newDataItem)
{
    if (isFull()) 
        cout << "Error : Full Queue" << endl;
    else 
    {
        QueueNode<DT>* newNode;
        newNode = new QueueNode<DT>(newDataItem, NULL);
        if (rear == NULL) 
            front = newNode;
        else 
            rear->next = newNode;
        rear = newNode; 
    }
}

template<class DT>
DT Queue<DT>::dequeue()
{
    DT queueItem; 

    if (isEmpty())
        cout << "Error : Empty Queue" << endl;
    else 
    {
        QueueNode<DT>* temp; 

        temp = front; 
        queueItem = front->dataItem; 
        front = front->next; 
     
        if (front == NULL)
            rear = NULL;
        delete temp;
        return queueItem;
    }

}

template <class DT>
void Queue<DT>::clear()
{
    front = nullptr;
    rear = nullptr;
}

template<class DT>
bool Queue<DT>::isEmpty() const
{
    return(front == nullptr);
}

template<class DT>
bool Queue<DT>::isFull() const
{
    Queue<DT>* temp = new(nothrow)Queue<DT>;
    if (temp == NULL)
        return true;
    else {
        delete temp;
        return false;
    }
}

template<class DT>
void Queue<DT>::showStructure() const
{
    QueueNode<DT>* p;   // Iterates through the queue

    if (isEmpty())
        cout << "Empty queue" << endl;
    else
    {
        cout << "front ";
        for (p = front; p != nullptr; p = p->next)
            cout << p->dataItem << " ";
        cout << "rear" << endl;
    }
}