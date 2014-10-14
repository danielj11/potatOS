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
    ~pcbQueue();

    int queueSize;
    pcb* head;
    pcb* tail;
    vector<pcb*>heldItems;

};


#endif // PCBQUEUE_H
