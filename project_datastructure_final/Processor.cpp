#include "Processor.h"
#include "BLK.h"
LinkedList<Processes>* Processors::Termination = nullptr; 
BLK* Processors::Blk = new BLK;

Processors::Processors() {
    settermination();
}

void Processors::settermination() {
    Termination = new LinkedList<Processes>;
}

void Processors::setblk()
{
    Blk = new BLK;
}

BLK*& Processors::getblk()
{
    return Blk;
}

LinkedList<Processes>*& Processors::gettermination() {
    return Termination;
}