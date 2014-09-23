#include "controller.h"

void dateTestDriver();
void versionTestDriver();
void exitTestDriver();
void directoryTestDriver();
void PCBTestDriver();
void SJFTestDriver();
void FIFOTestDriver();

int main()
{
    /*dateTestDriver();
    versionTestDriver();
    directoryTestDriver();
    exitTestDriver();
    PCBTestDriver();*/

    /*controller myController;
    myController.runSim();*/

    //SJFTestDriver();
    FIFOTestDriver();

    return 0;
}

void dateTestDriver()
{
    date testDate;
    testDate.displayDate();
}

void versionTestDriver()
{
    version testVersion;
    testVersion.displayVersion();
}

void exitTestDriver()
{
    exitSim testExit;
    testExit.escapeSim();
}

void directoryTestDriver()
{
    directory testDirectory;
    testDirectory.showFiles();
}

void PCBTestDriver()
{
    controller testController;

    pcb* testPCB;
    testPCB = testController.setupPCB("bob", 17, 'S');
    pcb* testPCB2;
    testPCB2 = testController.setupPCB("joe", 52, 'S');

    testController.insertPCB(testPCB);
    testController.insertPCB(testPCB2);

    cout << testController.ready.queueSize << endl;

    testController.removePCB(testPCB2);

    cout << testController.ready.queueSize << endl;
}

void SJFTestDriver()
{
    controller testController;
    testController.shortestJobFirstFK();
}

void FIFOTestDriver()
{
    controller testController;
    testController.firstInFirstOut();
}
