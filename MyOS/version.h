#ifndef VERSION_H
#define VERSION_H

#include <iostream>
#include <string>

using namespace std;

class version
{
public:
    version();
    void displayVersion();
    ~version();
private:
    string versionNum;
};


#endif //VERSION_H
