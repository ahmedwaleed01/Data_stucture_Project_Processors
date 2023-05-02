#pragma once
#include "Processes.h"
#include "LinkedQueue.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"
#include <iostream>
#define NULL
using namespace std;
class NewList
{
private:
	LinkedQueue<Processes>* process;
	LinkedQueue<Processes>* temp;
	int num_fcfs;
	int num_rr;
	int num_sjf;
	int num_process;
	FCFS* fcfs_p;
	RR* rr_p;
	SJF* sjf_p;
public:
	NewList(int num_fcfs, int num_rr, int num_sjf, int time_slice, int num_process) {
		this->num_fcfs = num_fcfs;
		this->num_rr = num_rr;
		this->num_sjf = num_sjf;
		this->num_process = num_process;
		rr_p = new RR[num_rr];
		sjf_p = new SJF[num_sjf];
		rr_p->settimeslice(time_slice);
		fcfs_p = new FCFS[num_fcfs];                   // array of fcfs processors
		process = new LinkedQueue<Processes>;
		temp = new LinkedQueue<Processes>;
	};
	Processes get_process() {
		Processes pop;
		bool done = process->dequeue(pop);
		num_process--;
		if (done)
		{
			return pop;
		}

	}
	
	Node<Processes>* getprocessptr() {
		return process->getfrontptr();
	}
	LinkedQueue<Processes>*& getlinked_process() {
		return  process;
	}
	Processes getprocess() {
		return (process->getfrontptr()->getItem());
	}
	int getnum_fcfs() { return num_fcfs; }
	int getnum_rr() { return num_rr; }
	int getnum_sjf() { return num_sjf; }
	int getnumprocees() { return num_process; }
	void add_process(Processes& p) {
		bool done = process->enqueue(p);
		bool done2 = temp->enqueue(p);
	}
	FCFS* getfcfs() {
		return fcfs_p;
	}
	RR* getrr_p() {
		return rr_p;
	}
	SJF* getsjf_p() {
		return sjf_p;
	}

	FCFS* getshortest_FCFS()
	{
		FCFS* FCFS_min;
		int min = fcfs_p[0].gettotal_time();
		FCFS_min = &fcfs_p[0];
		for (int i = 0; i < this->num_fcfs; i++) {
			int time = fcfs_p[i].gettotal_time();
			if (time < min) {
				FCFS_min = &fcfs_p[i];
				min = time;
			}
		}
		return FCFS_min;
	}
	RR* getshortest_RR()
	{
		RR* RR_min;
		int min = rr_p[0].gettotal_time();
		RR_min = &rr_p[0];
		for (int i = 0; i < this->num_rr; i++) {
			int time = rr_p[i].gettotal_time();
			if (time < min) {
				RR_min = &rr_p[i];
				min = time;
			}
		}
		return RR_min;
	}
	SJF* getshortest_SJF()
	{
		SJF* SJF_min;
		int min = sjf_p[0].getTotalTime();
		SJF_min = &sjf_p[0];
		for (int i = 0; i < this->num_sjf; i++) {
			int time = sjf_p[i].getTotalTime();
			if (time < min) {
				SJF_min = &sjf_p[i];
				min = time;
			}
		}
		return SJF_min;
	}
};