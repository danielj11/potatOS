#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <string>

using namespace std;

class pcb
{
public:
    pcb();
    ~pcb();
    string processName;
    char processType; //A(application) or S(system)
    int priority; //-127 to 128
    string state1; //running, ready, or blocked
    string state2; //suspended or not  "not" = not suspended, "suspended" means suspended
    int memory; //how much memory the process needs
    int timeRemaining;
    int timeOfArrival;
    int cpuPercent;
    int ticketAmount;
private:

};

#endif //PCB_H
