#include <iostream>
#include <vector>
#include "fstream"
#include "Node.h"
#include"LinkedQueue.h"
#include "IO_REQUEST.h"
#include <string>
#include "Processes.h"
#include"NewList.h"
#include "Termination.h"
#include"Linkedlist.h"
#include "BLK.h"
#include "Schedular.h"
#include <sstream>
#include"Node.h"
#define NULL
using namespace std;
void extractIntegersFromTupleString(string tupleStr, int& firstNum, int& secondNum)
{
	tupleStr.erase(remove(tupleStr.begin(), tupleStr.end(), '('), tupleStr.end());
	tupleStr.erase(remove(tupleStr.begin(), tupleStr.end(), ')'), tupleStr.end());
	stringstream ss(tupleStr);
	string str;
	getline(ss, str, ',');
	firstNum = stoi(str);
	getline(ss, str, ',');
	secondNum = stoi(str);
}
NewList* inputfunction() {
	NewList* newlist;
	ifstream inputfile;
	inputfile.open("inputfile.txt");
	string ss;
	if (inputfile.is_open()) {
		inputfile >> ss;
		int no_fcfs = stoi(ss);                      /// number of fcfs processors
		inputfile >> ss;
		int no_sjf = stoi(ss);                        // number sjs processors
    	inputfile >> ss;
		int no_rr = stoi(ss);                           // number of rr processors
		inputfile >> ss;
		int time_slice = stoi(ss);                  // time slice for rr
		inputfile >> ss;
		int num_process = stoi(ss);                 // number of process
		newlist = new NewList(no_fcfs, no_rr, no_sjf, time_slice, num_process);                  // add processors to newlist
		for (int i = 1; i <= num_process; i++)
		{
			inputfile >> ss;
			int AT = stoi(ss);
			inputfile >> ss;
			int process_id = stoi(ss);
			inputfile >> ss;
			int cpu_time = stoi(ss);
			inputfile >> ss;
			int IO_NUM = stoi(ss);
			Processes process(process_id, AT, cpu_time, IO_NUM);
			for (int i = 1; i <= IO_NUM; i++) {
				inputfile >> ss;
				int IO_R, IO_D;
				extractIntegersFromTupleString(ss, IO_R, IO_D);
				process.addIO_Request(IO_R, IO_D);
			}
			//cout << "at " << AT << " " << "id " << process_id << " " << "cpu " << cpu_time << " " << "I0_num " << IO_NUM << endl;
			newlist->add_process(process);                // add processes
		}
	}
	inputfile.close();
	return newlist;
}
int main() {

	NewList* newlist = inputfunction();
	BLK* block = newlist->getsjf_p()->getblk();
	Schedular* newsch = new Schedular(newlist, block);
	char ch;
	int time_step = 1;
	int tt;
	int sch = 2;
	ch = getchar();
	int count;
	while (ch == 10) {
		cout << "CURRENT TIME STEP: " << time_step << endl;
		cout << "------------------       RDY PROCESSES      --------------------- " << endl;

		if (ch == 10) {
			if (newsch->getlist()->getnumprocees() != 0)
			{
				Node<Processes>* proces_ptr = newsch->getlist()->getlinked_process()->getfrontptr();
				while (proces_ptr) {
					FCFS* Tfcfs_p = newsch->getlist()->getshortest_FCFS();
					int f = Tfcfs_p->gettotal_time();
					int at = proces_ptr->getItem().getarrival_time();
					SJF* sjf_p = newsch->getlist()->getshortest_SJF();
					RR* rr_p = newsch->getlist()->getshortest_RR();
					int r = rr_p->gettotal_time();
					bool done = false;
					int s = sjf_p->getTotalTime();
					if (f <= s && time_step >= at && f <= r) {
						Processes p;
						newsch->getlist()->getlinked_process()->dequeue(p);
						Tfcfs_p->addprocesses(p);
						done = true;
					}
					else if (f >= s && time_step >= at && s <= r) {
						Processes p;
						newsch->getlist()->getlinked_process()->dequeue(p);
						sjf_p->addprocesses(p);
						done = true;
					}
					else if (r <= f && r <= s && time_step >= at) {
						Processes p;
						newsch->getlist()->getlinked_process()->dequeue(p);
						rr_p->addprocesses(p);
						done = true;
					}
					if (done == true) {
						proces_ptr = newsch->getlist()->getlinked_process()->getfrontptr();
						done = false;
					}
					else {
						proces_ptr = proces_ptr->getNext();
					}
				}

				cout << endl << "--------------------------- RDY LIST------------------------------" << endl;
				/// PRINT RDY LIST FOR FCFS PROCESSORS////
				FCFS* ff = newsch->getlist()->getfcfs();
				int nu_ff = newsch->getlist()->getnum_fcfs();
				for (int i = 0; i < nu_ff; i++) {
					ff[i].schuldingalgo(time_step);
					Node<Processes>* pttr = ff[i].getrdy_list()->getfrontptr();
					cout << "processor fcfs(" << i + 1 << "): ";
					int co = 0;
					vector<int> r;
					while (pttr != nullptr) {
						r.push_back(pttr->getItem().get_id());
						co++;
						pttr = pttr->getNext();
					}
					cout << "[" << co << "] " << "RYD  ";
					for (int i = 0; i < co; i++) {
						cout << r[i] << " ";
					}
					cout << endl;
				}
				/// PRINT RDY LIST FOR SJF PROCESSORS //////
				SJF* sjf = newsch->getlist()->getsjf_p();
				int nu_sjf = newsch->getlist()->getnum_sjf();
				for (int i = 0; i < nu_sjf; i++) {
					sjf[i].schuldingalgo(time_step);
					Node<Processes>* pttr = sjf[i].getrdy_list()->gethead();
					cout << "processor SJF(" << i + 1 << "): ";
					int co = 0;
					vector<int> r;
					while (pttr != nullptr) {
						r.push_back(pttr->getItem().get_id());
						co++;
						pttr = pttr->getNext();
					}
					cout << " [" << co << "] " << "RYD  ";
					for (int i = 0; i < co; i++) {
						cout << r[i] << " ";
					}
					cout << endl;
				}

				/// PRINT RDY LIST FOR RR PROCESSORS ////////
				RR* rr = newsch->getlist()->getrr_p();
				int nu_rr = newsch->getlist()->getnum_rr();
				for (int i = 0; i < nu_rr; i++) {
					rr[i].schuldingalgo(time_step);
					Node<Processes>* pttr = rr[i].getrdy_list()->gethead();
					cout << "processor RR(" << i + 1 << "): ";
					int co = 0;
					vector<int> r;
					while (pttr != nullptr) {
						r.push_back(pttr->getItem().get_id());
						co++;
						pttr = pttr->getNext();
					}
					cout << "  [" << co << "] " << "RYD  ";
					for (int i = 0; i < co; i++) {
						cout << r[i] << " ";
					}
					cout << endl;
				}

				cout << "------------------------------   RUN LIST -----------------------------" << endl; //*
				for (int i = 0; i < nu_ff; i++) {
					Node<Processes>* pttr = ff[i].getrun_list()->getfrontptr();
					cout << "processor fcfs(" << i + 1 << "): ";
					int co = 0;
					vector<int> r;
					while (pttr != nullptr) {
						r.push_back(pttr->getItem().get_id());
						co++;
						pttr = pttr->getNext();
					}
					cout << "[" << co << "] " << "RUN  ";
					for (int i = 0; i < co; i++) {
						cout << r[i] << " ";
					}
					cout << endl;
				}
				for (int i = 0; i < nu_sjf; i++) {
					Node<Processes>* pttr = sjf[i].getrun_list()->gethead();
					cout << "processor SJF(" << i + 1 << "): ";
					int co = 0;
					vector<int> r;
					while (pttr != nullptr) {
						r.push_back(pttr->getItem().get_id());
						co++;
						pttr = pttr->getNext();
					}
					cout << " [" << co << "] " << "RUN  ";
					for (int i = 0; i < co; i++) {
						cout << r[i] << " ";
					}
					cout << endl;
				}
				for (int i = 0; i < nu_rr; i++) {
					Node<Processes>* pttr = rr[i].getrun_list()->getfrontptr();
					cout << "processor RR(" << i + 1 << "): ";
					int co = 0;
					vector<int> r;
					while (pttr != nullptr) {
						r.push_back(pttr->getItem().get_id());
						co++;
						pttr = pttr->getNext();
					}
					cout << "  [" << co << "] " << "RUN  ";
					for (int i = 0; i < co; i++) {
						cout << r[i] << " ";
					}
					cout << endl;
				}

				cout << "----------------------- BLK LIST  ------------------" << endl;
				newsch->check_blk(time_step);
				Node<Processes>* proc_blk = block->getblk_process()->gethead();
				int count_blk = 0;
				vector<int> b;
				while (proc_blk != nullptr) {
					count_blk++;
					b.push_back(proc_blk->getItem().get_id());
					proc_blk = proc_blk->getNext();
				}
				//newsch->check_blk(time_step);
				cout << count_blk << " " << "BLK: ";
				for (int i = 0; i < count_blk; i++) {
					cout << b[i] << " , ";
				}
				cout << endl;
				cout << "--------------- TERMINATION LIST -------------------" << endl;
				Node<Processes>* proc_term = newsch->getlist()->getfcfs()->gettermination()->gethead();
				int count = 0;
				vector<int> aaa;
				while (proc_term != nullptr) {
					count++;
					aaa.push_back(proc_term->getItem().get_id());
					proc_term = proc_term->getNext();
				}
				cout << count << " " << "Termination: ";
				for (int i = 0; i < count; i++) {
					cout << aaa[i] << " , ";
				}
				cout << endl;

			}
			time_step++;
			ch = getchar();
		}
	}
}