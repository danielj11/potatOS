#include "directory.h"

directory::directory()
{
    holdStr = "";
}

void directory::showFiles() //prints list of filenames in directory
{
    vector<string> fileNames;//holds file names
    char search_path[200];

    sprintf(search_path, "%s*.*", holdStr.c_str());
    WIN32_FIND_DATA dataFind; //finds file attributes
    HANDLE hFind = FindFirstFile(search_path, &dataFind); //::FindFirstFile

    if(hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if(!(dataFind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                fileNames.push_back(dataFind.cFileName); //add filename to vector
            }
        }while(FindNextFile(hFind, &dataFind));
        FindClose(hFind);
    }

    cout << "The files in the list are: " << endl;

    for (int i = 0; i < fileNames.size(); i++) //print filenames from vector
    {
        cout << fileNames[i] << endl;
    }

    int i = 0;

    /*while (i < fileNames.size())
    {
            if (i == fileNames.size())
            {
               cout << fileNames[i] <<endl;
            }
            else
            {
                for (int j = 0; j < 2; j++)
                {
                    cout << fileNames[i] << "    " << fileNames[i+1] <<  endl;
                    i = i + 2;
                }
            }
    }*/

    /*for (int i = 0; i < fileNames.size(); i++) //print filenames from vector
    {
        for (int j = 0; j < 2; j++)
        {
            cout << fileNames[i] << "    " << fileNames[i+1] <<  endl;
            i++;
        }
    }*/

    cout << endl;

    return;
}

directory::~directory()
{

}
