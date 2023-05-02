#pragma once
template<class T>
class QueueADT
{
public:
    QueueADT() {};
    virtual bool isEmpty()  = 0;                     // check if it is empty
    virtual bool enqueue(const T& newEntry) = 0;          // to add new item in queue
    virtual bool dequeue(T& FrontEntry) = 0;              // to remove an item in the queue
    virtual ~QueueADT() { }

};

