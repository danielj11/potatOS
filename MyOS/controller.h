#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include "date.h"
#include "version.h"
#include "exit.h"
#include "directory.h"
#include "help.h"
#include "pcbqueue.h"

using namespace std;

class controller
{
public:
    controller();
    void printMenu();
    void printPCBMenu();
    void runPCBFunctions();
    void runSim();
    void waitForInput();
    ~controller();

    //PCB Functions
    pcb* allocatePCB();
    pcb* findPCB(string nameToFind);
    void insertPCB(pcb* pcbToInsert);
    pcb* setupPCB(string name, int pcbPriority, char type); //return pcb*
    void removePCB(pcb* pcbToRemove);
    void freePCB(pcb* pcbToFree);

    pcbQueue ready;
    pcbQueue blocked;
    pcbQueue suspendedReady;
    pcbQueue suspendedBlocked;
private:
    char userChoice;
    int userPCBChoice;
    bool exitFlag;
};


#endif //CONTROLLER_H
