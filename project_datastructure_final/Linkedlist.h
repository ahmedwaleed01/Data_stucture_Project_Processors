#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include "Processes.h"
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;

public:
	LinkedList()
	{
		Head = nullptr;
	}
	Node<T>*& gethead() {
		return Head;
	}
	~LinkedList()
	{
		DeleteAll();
	}
	void sett() {
		Head = nullptr;
	}
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}

	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}

	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}


	void InsertEnd(const T& data) {
		Node<T>* R = new Node<T>(data);
		R->setItem(data);
		if (!Head) {
			Head = R;
			return;
		}
		Node<T>* p = Head;
		while (p->getNext()) {
			p = p->getNext();
		}
		p->setNext(R);
	}

	bool Find(int Key) {
		Node<T>* prev = Head;
		Node<T>* next = prev->getNext();
		if (next == nullptr) {
			if (prev->getItem() == Key) {
				return true;
			}
		}
		else {
			if (prev->getItem() == Key) {
				return true;
			}
		}
		while (next) {
			if (next->getItem() == Key) {
				return true;
			}
			prev = prev->getNext();
			next = next->getNext();
		}
		return false;
	}

	bool DeleteNode(const T& value) {
		Node<T>* prev = Head;
		Node<T>* next = prev->getNext();
		if (next == nullptr) {
			if (prev->getItem() == value) { ///------------------------>> /// operator overloading /////<--------------------------------/////
				Node<T>* temp = Head;
				Head = nullptr;
				delete temp;
				return true;
			}
		}
		else {
			if (prev->getItem() == value) {
				Node<T>* temp = Head;
				Head = Head->getNext();
				prev = nullptr;
				delete temp;
				return true;
			}
		}
		while (next) {
			if (next->getItem() == value) {
				Node<T>* temp = next;
				prev->setNext(temp->getNext());
				next->setNext(nullptr);
				next = nullptr;
				delete temp;
				return true;
			}
			prev = prev->getNext();
			next = next->getNext();
		}
		return false;
	}
	bool ISEMPTY()
	{
		if (Head == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(const Node<T>& other) const {
		return (item == other.getItem());
	}

	
	void Merge(const LinkedList& L) {
		Node<T>* ptr = L.Head;
		if (!ptr)
			return;
		Node<T>* head2 = new Node<T>;
		head2->setItem(ptr->getItem());
		if (ptr->getNext() == nullptr) {
			ptr->setNext(head2);
			head2->setNext(nullptr);
			return;
		}
		Node<T>* p2 = head2;
		while (ptr->getNext()) {
			Node<T>* n = new Node<T>;
			n->setItem(ptr->getNext()->getItem());
			p2->setNext(n);
			p2 = p2->getNext();
			ptr = ptr->getNext();
		}
		//node* lastone = new node;
		//lastone->item = ptr->item;
		p2->setNext(nullptr);
		//lastone->next = NULL;
		ptr->setNext(head2);
	}
};

#endif	
