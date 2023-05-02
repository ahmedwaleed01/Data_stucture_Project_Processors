#pragma once
#include"Linkedlist.h"
#include "Processes.h"
#include "Node.h"
#include "IO_REQUEST.h"
class BLK
{
private:
	LinkedList<Processes>* process;
public:
	BLK() {
		process = new LinkedList<Processes>;
	}
	void add_process(Processes& p) {
		process->InsertEnd(p);
	}
	LinkedList<Processes>* getblk_process() { return process; }
	Processes algho(int time_step) {
		if (process->ISEMPTY()!=1 && process->gethead()->getItem().getio_r() != 0) {
			Node<Processes>* proc_ptr = process->gethead();
			while (proc_ptr) {
				int IO_D = proc_ptr->getItem().getIO_REQ()->getfrontptr()->getItem().getIO_D();
				int IO_R = proc_ptr->getItem().getIO_REQ()->getfrontptr()->getItem().getIO_R();
				if (IO_D <= time_step - IO_R) {
					IO_REQUEST i;
					proc_ptr->getItem().getIO_REQ()->dequeue(i);
					Processes ss = proc_ptr->getItem();
					ss.setio_r(ss.getio_r() - 1);
					process->DeleteNode(proc_ptr->getItem());
					return ss;
				}
				proc_ptr = proc_ptr->getNext();
			}
		}
		Processes s;
		return s;
	}
	//////////////////////////////// I NEED TO MAKE A FUNCTION THAT ADD THE PROCESS TO THE SHORTEST READY LIST //////////////////////////////////////
};