#include "help.h"

help::help()
{
}

void help::showHelp()
{
    cout << "~~~~~~~~~~" << endl;
    cout << "1. Version - Displays version number" << endl;
    cout << "2. Date - Displays current date" << endl;
    cout << "3. Directory - Show all files in the OS's directory" << endl;
    cout << "4. Help - Displays help messages" << endl;
    cout << "5. PCB Menu - displays menu for PCBs" << endl;
    cout << "6. Scheduler Menu - displays menu for schedulers" << endl;
    cout << "7. Exit - Exits operating system simulator" << endl;
    cout << "~~~~~~~~~~" << endl;
}

help::~help()
{
}
