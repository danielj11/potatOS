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

using namespace std;

class controller
{
public:
    controller();
    void printMenu();
    void runSim();
    ~controller();
private:
    char userChoice;
};


#endif //CONTROLLER_H
