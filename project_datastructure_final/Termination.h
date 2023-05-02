#pragma once
#include"Linkedlist.h"
#include "Processes.h"
class Termination 
{

private:
	LinkedList<Processes>* process;
public:
	Termination() {
		process = new LinkedList<Processes>;
	}
	void add_process(Processes&p) {
		process->InsertEnd(p);
	}
};