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
    ~pcbQueue();

    int queueSize;
    pcb* head;
    pcb* tail;
    vector<pcb*>heldItems;

};


#endif // PCBQUEUE_H
