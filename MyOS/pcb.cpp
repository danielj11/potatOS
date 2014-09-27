#include "pcb.h"

pcb::pcb()
{
    processName = "";
    priority = 0;
    state1 = "ready";
    state2 = "not";
    memory = 5;
    timeRemaining = 0;
    timeOfArrival = 0;
    cpuPercent = 0;
    queueNum = 0;
    ticketAmount= 0;
}

pcb::~pcb()
{
}
