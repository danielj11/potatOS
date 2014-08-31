#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <stdio.h>

using namespace std;

class directory
{
public:
    directory();
    void showFiles();
    ~directory();
private:
    string holdStr;
};

#endif //DIRECTORY_H
