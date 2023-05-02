#pragma once
template<class T>
class StackADT
{
public:
    virtual bool isEmpty()  = 0;
    virtual bool push(const T& newEntry) = 0;
    virtual bool pop(T& TopEntry) = 0;
   // virtual bool peek(T& TopEntry) const = 0;
    virtual ~StackADT() { }
};

