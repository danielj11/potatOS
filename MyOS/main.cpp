#include "date.h"
#include "version.h"
#include "exit.h"
#include "directory.h"
#include "controller.h"

void dateTestDriver();
void versionTestDriver();
void exitTestDriver();
void directoryTestDriver();

int main()
{
    /*dateTestDriver();
    versionTestDriver();
    directoryTestDriver();
    exitTestDriver();*/

    controller myController;
    myController.runSim();

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
