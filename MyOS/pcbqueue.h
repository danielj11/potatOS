#ifndef PCBQUEUE_H
#define PCBQUEUE_H

#include "pcb.h"
#include <vector>

using namespace std;

class pcbQueue
{
public:
    pcbQueue();
    void addPCB(pcb* newItem);
    void deletePCB(pcb* itemToDelete);
    void coalesce();
    void compact();
    bool firstFit(pcb* newPCB);
    bool nextFit(pcb* newPCB);
    bool bestFit(pcb* newPCB);
    bool worstFit(pcb* newPCB);
    void addPCBFit(char whichFit, pcb* nPCB);
    void removePCB();
    void swapPCB(pcbQueue otherQueue);
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
