#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
//#include <algorithm>

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
    pcb* createProcess(string name, char pcbClass, int pcbPri,int mem, int timeR, int timeA, int percent);
    void printReady();
    char chooseFit();

    //Scheduler Functions
    bool readFile();
    void SJF(); //shortest job first scheduler - full knowledge
    void FIFO(); //First in first out scheduler
    void STCF(); //shortest time to completion first scheduler
    void FPPS();//fixed priority pre-emptive scheduler
    void RR(); //round robin scheduler
    void MLFQ(); //multi-leveled feedback queue scheduler
    void LS(); //lottery schedule
    void printScheduleMenu();
    void runScheduleFunctions();
    void resetSchedulers();
    void setRunning();

    pcbQueue running;
    pcbQueue ready;
    pcbQueue blocked;
    pcbQueue suspendedReady;
    pcbQueue suspendedBlocked;
    vector<pcb*> filepcbs;
private:
    char userChoice;
    int userPCBChoice;
    int userScheduleChoice;
    bool exitFlag;
};


#endif //CONTROLLER_H
