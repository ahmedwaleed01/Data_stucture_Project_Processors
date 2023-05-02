#pragma once
#include "LinkedQueue.h"
#include "IO_REQUEST.h"
class Processes
{
private:
	int PID;
	int AT;  // Arrival Time 
	int RT;  // Response Time
	int CT;  // CPU Time
	int TT;  // Termination time
	int TRT; // Turnaround duration
	int WT;  // Waiting Time
	int no_reqs; // number of requests
	LinkedQueue<IO_REQUEST>* I0;
public:
	Processes(){};
	Processes(int PID,int AT,int CT,int no_reqs){
		this->PID = PID;
		this->AT=AT;
		this->CT = CT;
		this->TRT = TT - AT;
		this->WT = TRT - CT;
		this->no_reqs=no_reqs;
		I0 = new LinkedQueue<IO_REQUEST>;
	};
	void addIO_Request(int IO_R,int IO_D) {
		IO_REQUEST I(IO_R, IO_D);
		I0->enqueue(I);
	}
	LinkedQueue<IO_REQUEST>* getIO_REQ() {
		return I0;
	}
	void removeIO_Request(IO_REQUEST& I) {
		I0->dequeue(I);
	}
	bool operator==(const Processes& other) const {
		return (PID==other.PID);
	}
	void setarrival_time(int AT) { this->AT = AT; }
	void setresponse_time(int RT) { this->RT = RT; }
	void setcpu_time(int CT) { this->CT = CT; }
	void settermination_time(int TT) { this->TT = TT; }
	int getTRT() { return TRT; }
	int getcpu_time() { return CT; }
	int getarrival_time() { return AT; }
	int getresponse_time() { return RT; }
	int gettermination_time() { return TRT; }
	int get_id() { return PID; };
	int getio_r() { return no_reqs; }
	void setio_r(int no) { no_reqs = no; }
};