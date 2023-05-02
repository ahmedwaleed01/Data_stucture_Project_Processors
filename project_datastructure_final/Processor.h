
#pragma once
#include "LinkedList.h"
#include "Processes.h"
#include "BLK.h"
class Processors {
private:
	static LinkedList<Processes>* Termination;
	static BLK* Blk;
public:
	Processors();
	virtual void schuldingalgo(int time_step) = 0;
	static void settermination();
	static void setblk();
	static BLK*& getblk();
	static LinkedList<Processes>*& gettermination();
};