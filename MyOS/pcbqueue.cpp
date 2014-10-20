#include "pcbqueue.h"

pcbQueue::pcbQueue()
{
    head = NULL;
    tail = NULL;
    queueSize = 0;
    runningPosition = 0;
}

//adds a pcb to the end of a queue
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

//deletespcbfrom queue
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

//performs coalescing on the queue
void pcbQueue::coalesce()
{

    cout << "-BEFORE COALESCING-" << endl;
    printQueue();
    int limit = 0;

    if (queueSize % 2 == 0)
    {
        limit = 1;
    }
    else
    {
        limit = 2;
    }

    for (int i = 0; i < heldItems.size() - limit; i++)
    {
        heldItems[i] -> memory = heldItems[i] -> memory + heldItems[i+1] -> memory;
        heldItems.erase(heldItems.begin()+i+1);
    }

    cout << "-AFTER COALESCING-" << endl;
    printQueue();

    queueSize = heldItems.size();

    cout << endl;
}

//performs compaction on the queue
void pcbQueue::compact()
{
    cout << "-BEFORE COMPACTION-" << endl;
    printQueue();

    pcb* tempPCB = new pcb;
    tempPCB -> processName = "empty";
    tempPCB -> memory = 0;

    for (int i = 0; i < queueSize; i++)
    {
        tempPCB -> memory = tempPCB -> memory + heldItems[i] -> memory;
    }

    heldItems.clear();
    addPCB(tempPCB);

    cout << "-AFTER COMPACTION-" << endl;
    printQueue();

    queueSize = heldItems.size();

    cout << endl;
}

//inserts a new PCB using First Fit memory management
bool pcbQueue::firstFit(pcb* newPCB)
{
    for (int i = 0; i < heldItems.size(); i++)
    {
        if (heldItems[i] -> memory >= newPCB -> memory)
        {
            heldItems[i] -> memory -= newPCB -> memory;

            //if the memory of the found pcb is reduced to zero, just replace it with the new one
            if (heldItems[i] -> memory == 0)
            {
                heldItems[i] = newPCB;
                return true;
            }
            //if not, insert the new pcb into found spot
            else
            {
                heldItems.insert(heldItems.begin()+i, newPCB);
                return true;
            }
        }
    }

    return false; //no available slot was found
}

//inserts a new PCB using Next Fit memory management
bool pcbQueue::nextFit(pcb* newPCB)
{
    int firstPos = -9999;

    for (int i = 0; i < heldItems.size(); i++)
    {
        //saves location of first available slot
        if (heldItems[i] -> memory >= newPCB -> memory && firstPos < 0)
        {
            firstPos = i;
        }

        //puts new pcb into queue, but only if another available area was found first
        if (heldItems[i] -> memory >= newPCB -> memory && firstPos > 0 && i != firstPos)
        {
            heldItems[i] -> memory -= newPCB -> memory;

            //if the memory of the found pcb is reduced to zero, just replace it with the new one
            if (heldItems[i] -> memory == 0)
            {
                heldItems[i] = newPCB;
                return true;
            }
            //if not, insert the new pcb into found spot
            else
            {
                heldItems.insert(heldItems.begin()+i, newPCB);
                return true;
            }
        }
    }

    //if only one position was found, insert new pcb there
    if (firstPos >= 0)
    {
        heldItems[firstPos] -> memory -= newPCB -> memory;
        if (heldItems[firstPos] -> memory == 0)
        {
            heldItems[firstPos] == newPCB;
        }
        else
        {
            heldItems.insert(heldItems.begin()+firstPos, newPCB);
        }

        return true;
    }

    return false; //no available slot was found
}

//inserts a new PCB using Best Fit memory management
bool pcbQueue::bestFit(pcb* newPCB)
{
    int difference = 9999;
    int position = -9999;
    int tempDiff = 0;

    for (int i = 0; i < heldItems.size(); i++)
    {
        if (heldItems[i] -> memory >= newPCB -> memory)
        {
            tempDiff = heldItems[i] -> memory - newPCB -> memory;
            if (tempDiff < difference)
            {
                difference = tempDiff;
                position = i;
            }
        }
    }

    if (difference != 9999 && position >= 0)
    {
        heldItems[position] -> memory -= newPCB -> memory;
        heldItems.insert(heldItems.begin()+position, newPCB);
        return true;
    }
    else
    {
        return false;
    }
}

//inserts a new PCB using Worst Fit memory management
bool pcbQueue::worstFit(pcb* newPCB)
{
    int difference = -9999;
    int position = -9999;
    int tempDiff = 0;

    for (int i = 0; i < heldItems.size(); i++)
    {
        if (heldItems[i] -> memory >= newPCB -> memory)
        {
            tempDiff = heldItems[i] -> memory - newPCB -> memory;
            if (tempDiff > difference)
            {
                difference = tempDiff;
                position = i;
            }
        }
    }

    if (difference != -9999 && position >= 0)
    {
        heldItems[position] -> memory -= newPCB -> memory;
        heldItems.insert(heldItems.begin()+position, newPCB);
        return true;
    }
    else
    {
        return false;
    }
}

//adds a PCB to running queue using memory management
void pcbQueue::addPCBFit(char whichFit, pcb* nPCB)
{
    switch(whichFit)
    {
    case 'F':
        {
            bool done = false;
            done = firstFit(nPCB);
            if (!done)
            {
                coalesce();
                done = firstFit(nPCB);
            }
            else
            {
                return;
            }
            if (!done)
            {
                compact();
                done = firstFit(nPCB);
            }
        }
        break;
    case 'N':
        {
            bool done = false;
            done = nextFit(nPCB);
            if (!done)
            {
                coalesce();
                done = nextFit(nPCB);
            }
            if (!done)
            {
                compact();
                done = nextFit(nPCB);
            }
        }
        break;
    case 'B':
        {
            bool done = false;
            done = bestFit(nPCB);
            if (!done)
            {
                coalesce();
                done = bestFit(nPCB);
            }
            if (!done)
            {
                compact();
                done = bestFit(nPCB);
            }
        }
        break;
    case 'W':
        {
            bool done = false;
            done = worstFit(nPCB);
            if (!done)
            {
                coalesce();
                done = worstFit(nPCB);
            }
            if (!done)
            {
                compact();
                done = worstFit(nPCB);
            }
        }
        break;
    default:
        {
            bool done = false;
            done = firstFit(nPCB);
            if (!done)
            {
                coalesce();
                done = firstFit(nPCB);
            }
            if (!done)
            {
                compact();
                done = firstFit(nPCB);
            }
        }
    }

    queueSize = heldItems.size();
}

//removes a PCB from the running queue
void pcbQueue::removePCB()
{
    for (int i = 0; i < heldItems.size(); i++)
    {
        if (heldItems[i] -> processName != "empty")
        {
            heldItems[i] -> processName = "empty";
        }
    }

    queueSize = heldItems.size();

    return;
}

//puts running pcb into ready queue and adds new pcb from ready to running
void pcbQueue::swapPCB(pcbQueue otherQueue)
{
    int pos = findRunning();

    pcb* tempPCB = heldItems[pos];
    otherQueue.addPCB(tempPCB);
    heldItems[pos] -> processName = "empty";

    otherQueue.queueSize = otherQueue.heldItems.size();

    queueSize = heldItems.size();

    return;
}

//looks for position of running pcb in a queue and returns it
int pcbQueue::findRunning()
{
    for (int  i = 0; i < heldItems.size(); i++)
    {
        if (heldItems[i] -> processName != "empty")
        {
            return i;
        }
    }

    return -9999;
}

//prints the contents of a queue
void pcbQueue::printQueue()
{
    for (int i = 0; i < heldItems.size();i++)
    {
        cout << heldItems[i] -> processName << " --- " << heldItems[i] -> memory << endl;;
    }
}

pcbQueue::~pcbQueue()
{
}
