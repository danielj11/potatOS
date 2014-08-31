#include "version.h"

version::version()
{
    versionNum = "1.0";
}

void version::displayVersion()
{
    cout << "This is version " << versionNum << "." << endl;
}

version::~version()
{

}
