#include "version.h"

version::version()
{
    versionNum = "1.3";
}

void version::displayVersion()
{
    cout << "This is version " << versionNum << " of potatOS." << endl << endl;
}

version::~version()
{

}
