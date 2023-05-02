#pragma once

#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private:
	T item;         // A data item
	Node<T>* next; // Pointer to next node
public:
	Node(){ next = nullptr; }
	Node(const T& Item){
		item = Item;
		next = nullptr;
	}
	Node(const T& Item, Node<T>* nextNodePtr) {
		item = Item;
		next = nextNodePtr;
	}
	void setItem(const T& Item) {
		item = Item;
	}
	void setNext(Node<T>* nextNodePtr) {
		next = nextNodePtr;
	}
	T getItem() const {
		return item;
	}
	Node<T>* getNext() const{ return next; }
}; 
#endif
