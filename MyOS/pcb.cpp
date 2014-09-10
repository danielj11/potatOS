#include "pcb.h"

pcb::pcb()
{
    processName = "";
    priority = 0;
    state1 = "ready";
    state2 = "not";
    memory = 5;
}

pcb::~pcb()
{
}
