#ifndef PCBQUEUE_H
#define PCBQUEUE_H

#include "pcb.h"
#include <vector>

using namespace std;

class pcbQueue
{
public:
    pcbQueue();
    void addPCB(pcb*);
    void deletePCB(pcb*);
    void coalesce();
    void compact();
    bool firstFit(pcb* newPCB);
    bool nextFit(pcb* newPCB);
    bool bestFit(pcb* newPCB);
    bool worstFit(pcb* newPCB);
    void addPCBFit(char whichFit, pcb* nPCB);
    void removePCB(); //removes pcb from running queue and sets its old position to empty
    void swapPCB(pcbQueue otherQueue);  //moves pcb from running into ready
    int findRunning();
    void printQueue();
    ~pcbQueue();

    int runningPosition;
    int queueSize;
    pcb* head;
    pcb* tail;
    vector<pcb*>heldItems;

};


#endif // PCBQUEUE_H
