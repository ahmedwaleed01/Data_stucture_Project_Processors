#pragma once
#include "Processes.h"
#include "Processor.h"
#include "LinkedQueue.h"
#include "Linkedlist.h"
#include "BLK.h"
#include <cstdlib>
class FCFS : public Processors
{
private:
	LinkedQueue<Processes>* RDY_List;
	LinkedQueue<Processes>* RUN_List;
	LinkedList<Processes>* termination;
	int Total_time;
	int count;
	int idrun;
	int arrOfIds[100] = { -1000000 };
	int countnum;
public:
	FCFS()
	{
		Total_time = 0;
		RDY_List = new LinkedQueue<Processes>;
		RUN_List = new LinkedQueue<Processes>;
		termination = gettermination();
		count = 0;
		idrun = -100;
		countnum = 0;
	};
	void addprocesses(Processes p) {
		RDY_List->enqueue(p);
		Total_time = Total_time + p.getcpu_time();
		count++;
		countnum++;
		arrOfIds[count - 1] = p.get_id();
	};
	LinkedQueue<Processes>* getrdy_list() { return RDY_List; }
	LinkedQueue<Processes>* getrun_list() { return RUN_List; }
	void terminate(Processes& p) {
		RUN_List->dequeue(p);
		LinkedList<Processes>* termination = gettermination();
		termination->InsertEnd(p);
	}
	int gettotal_time() {
		return Total_time;
	}
	int getcount() {
		return count;
	}
	void addtotal_time(int time) {
		Total_time = Total_time + time;
	}
	void schuldingalgo(int time_step)
	{
		Processes current;
		if (RDY_List->getfrontptr()) {
			current = RDY_List->getfrontptr()->getItem();
		}
		Processes current_run;
		if (!RUN_List->isEmpty()) {
			current_run = RUN_List->getfrontptr()->getItem();
		}
		if (RUN_List->isEmpty()&& !RDY_List->isEmpty() && current.getarrival_time() < time_step )
		{
			Processes Temp;
			RDY_List->dequeue(Temp);
			Total_time = Total_time - Temp.getcpu_time();
			Temp.setresponse_time(time_step);
			RUN_List->enqueue(Temp);
			int random_number = rand() % 100 + 1;
			if (random_number <= 15 && random_number >= 1) {
				/*Processes tem;
				RUN_List->dequeue(tem);
				BLK* blk = getblk();
				blk->add_process(tem);   */                                       ///////////////////////////    to be editeddd  ///////////////////////////////////////////
			}
			else if (random_number >= 20 && random_number <= 30) {
				Processes tem;
				RUN_List->dequeue(tem);
				RDY_List->enqueue(tem);
				Total_time = Total_time + Temp.getcpu_time();
			}
			else if (random_number >= 50 && random_number <= 60)
			{
				Processes Temp;
				Temp.settermination_time(time_step);
				terminate(Temp);
			}
		}
		else if (!RUN_List->isEmpty() && !current_run.getIO_REQ()->isEmpty() && current_run.getIO_REQ()->getfrontptr()->getItem().getIO_R() <= time_step) {
			Processes tem;
			RUN_List->dequeue(tem);                                                  //// if process have IO_Request the it moves it from Run state TO Blk State/////////////////
			BLK* blk = getblk();
			blk->add_process(tem);
		}
		else if (!RUN_List->isEmpty() && current_run.getIO_REQ()->isEmpty() &&current_run.getcpu_time() <= time_step - current_run.getresponse_time() + 1) { ////////////// if the process done its cpu time in run state then, terminate it ////
			Processes Temp;         // time_step>=
			terminate(Temp);
			Temp.settermination_time(time_step);
		}
	}
	int* getarrofid()
	{
		return arrOfIds;
	}

	int getidrun() {
		return idrun;
	}
	int getcountnum() {
		return countnum;
	}
};