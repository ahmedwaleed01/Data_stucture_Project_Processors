#pragma once
#include "Processes.h"
#include "Processor.h"
#include "LinkedQueue.h"
#include "Linkedlist.h"
#include <cstdlib>
class RR : public Processors
{
private:
	LinkedList<Processes>* RDY_List;
	LinkedQueue<Processes>* RUN_List;
	LinkedList<Processes>* termination;
	int Total_time;
	int Time_slice;
	int count;
	int arrOfIds[100] = { -1000000 };
	int idrun;
	int countnum;
public:
	RR() {
		Total_time = 0;
		count = 0;
		countnum = 0;
		RDY_List = new LinkedList<Processes>;
		RUN_List = new LinkedQueue<Processes>;
		termination = gettermination();
	}
	int getidrun() {
		return idrun;
	}
	int* getarrofid()
	{
		return arrOfIds;
	}
	void terminate(Processes& p) {
		RUN_List->dequeue(p);
		LinkedList<Processes>* termination = gettermination();
		termination->InsertEnd(p);
	}
	void addprocesses(Processes& p) {
		RDY_List->InsertEnd(p);
		Total_time = Total_time + p.getcpu_time();
		count++;
		countnum++;
		arrOfIds[count - 1] = p.get_id();
	};
	int getcountnum() { return countnum; }
	int getcount() { return count; }
	int gettotal_time() {
		return Total_time;
	}
	void addtotal_time(int time) {
		Total_time = Total_time + time;
	}
	LinkedList<Processes>* getrdy_list() { return RDY_List; }
	LinkedQueue<Processes>* getrun_list() { return RUN_List; }
	void settimeslice(int Time_slice) { this->Time_slice = Time_slice; }
	void schuldingalgo(int time_step)
	{
		
		Processes current;
		if (RDY_List->gethead()) {
			current = RDY_List->gethead()->getItem();
		}
		Processes current_run;
		if (!RUN_List->isEmpty()) {
			current_run = RUN_List->getfrontptr()->getItem();
		}
		if (RUN_List->isEmpty() && !RDY_List->ISEMPTY() && current.getarrival_time() < time_step)
		{

			Processes Temp=current;
			RDY_List->DeleteNode(current);
			Total_time = Total_time - Temp.getcpu_time();
			Temp.setresponse_time(time_step);
			RUN_List->enqueue(Temp);

			int random_number = rand() % 100 + 1;
			if (random_number <= 15 && random_number >= 1) {
				///////////////////////////    to be editeddd  ///////////////////////////////////////////
			}
			else if (random_number >= 20 && random_number <= 30) {
				Processes tem;
				RUN_List->dequeue(tem);
				RDY_List->InsertEnd(tem);
				Total_time = Total_time + tem.getcpu_time();
			}
			else if (random_number >= 50 && random_number <= 60)
			{
				Processes Temp;
				Temp.settermination_time(time_step);
				terminate(Temp);
			}
		}
		else if (!RUN_List->isEmpty() && current_run.getcpu_time() <= 0) {
			Processes Temp;
			Temp.settermination_time(time_step);
			terminate(Temp);
		}
		else if (!RUN_List->isEmpty() && Time_slice <= time_step - current_run.getresponse_time() + 1 && current_run.getIO_REQ()->isEmpty()) {
			Processes Temp;
			RUN_List->dequeue(Temp);
			Temp.setcpu_time(Temp.getcpu_time() - Time_slice);
			RDY_List->InsertEnd(Temp);
			Total_time = Total_time + Temp.getcpu_time();
		}
		/*else if (!RUN_List->isEmpty() && current_run.getcpu_time() <= time_step - current_run.getresponse_time() + 1) {
			Processes Temp;
			Temp.settermination_time(time_step);
			terminate(Temp);
		}*/
		else if (!RUN_List->isEmpty() && !current_run.getIO_REQ()->isEmpty() && current_run.getIO_REQ()->getfrontptr()->getItem().getIO_R() <= time_step) {
			Processes tem;
			RUN_List->dequeue(tem);                                                  //// if process have IO_Request the it moves it from Run state TO Blk State/////////////////
			BLK* blk = getblk();
			blk->add_process(tem);
		}
	}

};