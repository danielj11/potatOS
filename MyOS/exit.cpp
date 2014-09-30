#include "exit.h"

exitSim::exitSim()
{

}

bool exitSim::escapeSim() //Exits simulator
{
    string exitChoice = "N";

    cout << "Are you sure you want to exit(Y/N)? ";
    cin >> exitChoice;
    cout << endl;

    if (exitChoice == "Y" || exitChoice == "y")
    {
        cout << "Good-bye!" << endl;
        exit(0);
        return true;
    }
    else
    {
        return false;
    }
}

exitSim::~exitSim()
{

}
