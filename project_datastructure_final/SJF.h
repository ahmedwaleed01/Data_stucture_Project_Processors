#pragma once
#include "Processes.h"
#include "Processor.h"
#include "LinkedQueue.h"
#include "Linkedlist.h"
#include <cstdlib>
class SJF : public Processors
{
private:
	LinkedList<Processes>* RDY_List;
	LinkedList<Processes>* RUN_List;
	LinkedList<Processes>* RDYhead;
	LinkedList<Processes>* termination;
	int Total_time;
	int count;
	int min_cpu;
	Processes current;
	int c;
	int arrOfIds[100] = { -1000000 };
	int idrun;
	int countnum;
public:
	SJF() {
		Total_time = 0;
		RDY_List = new LinkedList<Processes>;
		RUN_List = new LinkedList<Processes>;
		RDYhead = new LinkedList<Processes>;
		min_cpu = 8000;
		count = 0;
		countnum = 0;
		c = 0;
		idrun = -100;
	}
	int getidrun() {
		return idrun;
	}
	int* getarrofid()
	{
		return arrOfIds;
	}
	void terminate(Processes& p) {
		RUN_List->DeleteNode(p);
		LinkedList<Processes>* termination = gettermination();
		termination->InsertEnd(p);
	}
	void addprocesses(Processes p) {
		RDY_List->InsertEnd(p);
		RDYhead->InsertEnd(p);
		Total_time = Total_time + p.getcpu_time();
		count++;
		countnum++;
		arrOfIds[count - 1] = p.get_id();
	};
	int getcountnum() { return countnum; }
	LinkedList<Processes>* getrdy_list() { return RDY_List; }
	LinkedList<Processes>* getrun_list() { return RUN_List; }
	int getcount()
	{
		return count;
	}
	void schuldingalgo(int time_step)
	{
		Processes current_run;
		if (!RUN_List->ISEMPTY()) {
			current_run = RUN_List->gethead()->getItem();
		}
		if (RUN_List->ISEMPTY() && !RDY_List->ISEMPTY() && time_step>1)
		{
			Node<Processes>* ptrtemp = RDY_List->gethead();
			Processes current= ptrtemp->getItem();
			int min_cput = RDY_List->gethead()->getItem().getcpu_time();
			while (ptrtemp) {
				if (ptrtemp->getItem().getcpu_time() < min_cput) {
					current = ptrtemp->getItem();
				}
				ptrtemp = ptrtemp->getNext();
			}
			Processes ttt=current;
			RDY_List->DeleteNode(ttt);
			Total_time = Total_time - current.getcpu_time();
			current.setresponse_time(time_step);
			RUN_List->InsertEnd(current);
			int random_number = rand() % 100 + 1;
			if (random_number <= 15 && random_number >= 1) {
				/*
				BLK* blk = getblk();
				blk->add_process(RUN_List->gethead()->getItem());
				RUN_List->DeleteNode(RUN_List->gethead()->getItem()); */      ///////////////////////////////////    to be editeddd  ///////////////////////////////////////////
			}
			else if (random_number >= 20 && random_number <= 30) {
				RDY_List->InsertEnd(RUN_List->gethead()->getItem());
				RUN_List->DeleteNode(RUN_List->gethead()->getItem());
				Total_time = Total_time + current.getcpu_time();

			}
			else if (random_number >= 50 && random_number <= 60)
			{
				current.settermination_time(time_step);
				terminate(current);
			}
		}else if (!RUN_List->ISEMPTY() &&!current_run.getIO_REQ()->isEmpty() && current_run.getIO_REQ()->getfrontptr()->getItem().getIO_R() <= time_step)
		{                       
			BLK* blk = getblk();
			blk->add_process(RUN_List->gethead()->getItem());
			RUN_List->DeleteNode(RUN_List->gethead()->getItem());
		}
		else if (!RUN_List->ISEMPTY() && current_run.getIO_REQ()->isEmpty() && current_run.getcpu_time() <= time_step - current_run.getresponse_time() + 1)
		{                                              
			idrun = -100;
			RUN_List->gethead()->getItem().settermination_time(time_step);
			terminate(RUN_List->gethead()->getItem());
		}
	}
	int getTotalTime() {
		return Total_time;
	}
};