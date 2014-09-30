#include "pcbqueue.h"

pcbQueue::pcbQueue()
{
    head = NULL;
    tail = NULL;
    queueSize = 0;
}

void pcbQueue::addPCB(pcb* newItem)
{
    heldItems.push_back(newItem);

    queueSize = heldItems.size();

    if(heldItems.size() > 0)
    {
        head = heldItems[0];
        tail = heldItems[heldItems.size()-1];
    }
    else
    {
        head = NULL;
        tail = NULL;
    }
}

void pcbQueue::deletePCB(pcb* itemToDelete)
{
    for (int i = 0; i < queueSize; i++)
    {
        if (heldItems[i] == itemToDelete)
        {
            heldItems.erase(heldItems.begin()+i);
            queueSize = heldItems.size();
            if (queueSize > 0)
            {
                head = heldItems[0];
                tail = heldItems[heldItems.size()-1];
            }
        }
    }
}

pcbQueue::~pcbQueue()
{
}
