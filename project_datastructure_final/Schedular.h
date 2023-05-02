#pragma once
#include"Linkedlist.h"
#include "Processes.h"
#include "Node.h"
#include "FCFS.h"
#include "IO_REQUEST.h"
#include "NewList.h"
#include "BLK.h"
class	Schedular
{
private:
	NewList* new_list;
	BLK* blk;
	Processes* proc;
public:
	Schedular(NewList*&neww,BLK*&bl) {
		new_list = neww;
		blk =bl;
	}
	NewList* getlist() {

		return new_list;
	}
	void check_blk(int time_step) {
		proc=&blk->algho(time_step);
		 if(proc->get_id()>0) {
			Processes ll = *proc;
			FCFS* fcfs = getshortest_fcfs();
			RR* rr = getshortest_rr();
			if (fcfs->gettotal_time()< rr->gettotal_time() ) {
				fcfs->addprocesses(ll);
				fcfs->addtotal_time(proc->getcpu_time());
			}
			else {
				rr->addprocesses(*proc);
				rr->addtotal_time(proc->getcpu_time());
			}
			
		}

	}
	BLK* getblk() { return blk; }
	FCFS* getshortest_fcfs() {
		FCFS* fcfs_p = new_list->getfcfs();
		int num_fcfs = new_list->getnum_fcfs();
		FCFS* FCFS_min;
		int min = fcfs_p[0].gettotal_time();
		FCFS_min = &fcfs_p[0];
		for (int i = 0; i < num_fcfs; i++) {
			int time = fcfs_p[i].gettotal_time();
			if (time < min) {
				FCFS_min = &fcfs_p[i];
				min = time;
			}
		}
		return FCFS_min;
	} 
	RR* getshortest_rr() {
		RR* rr_p = new_list->getrr_p();
		int num_rr = new_list->getnum_rr();
		RR* RR_min;
		int min = rr_p[0].gettotal_time();
		RR_min = &rr_p[0];
		for (int i = 0; i < num_rr; i++) {
			int time = rr_p[i].gettotal_time();
			if (time < min) {
				RR_min = &rr_p[i];
				min = time;
			}
		}
		return RR_min;
	}
	SJF* getshortest()
	{
		/*SJF* SJF_p = new_list->getsjf_p();
		SJF* SJF_min;
		int min = SJF_p[0].getTotalTime();
		SJF_min = &SJF_p[0];
		int num_rr = new_list->getnum_rr();
		for (int i = 0; i < num_rr; i++) {
			int time = SJF_p[i].getTotalTime();
			if (time < min) {
				SJF_min = &SJF_p[i];
			}
		}
		return SJF_min;
		*/
		SJF* sjf_p = new_list->getsjf_p();
		SJF* SJF_min;
		int min = sjf_p[0].getTotalTime();
		SJF_min = &sjf_p[0];
		int num_sjf = new_list->getnum_sjf();
		for (int i = 0; i < num_sjf; i++) {
			int time = sjf_p[i].getTotalTime();
			if (time < min) {
				SJF_min = &sjf_p[i];
				min = time;
			}
		}
		return SJF_min;
	}

};