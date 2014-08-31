#include "controller.h"

controller::controller()
{
    userChoice = '0';
}

void controller::printMenu()
{
    cout << "----------" << endl;
    cout << "1. Version" << endl;
    cout << "2. Date" << endl;
    cout << "3. Directory" << endl;
    cout << "4. Help" << endl;
    cout << "5. Exit" << endl;
    cout << "----------" << endl;
    cout << "Enter the corresponding number for what you want to do: ";
    cin >> userChoice;
    cout << endl;

    return;
}

void controller::runSim()
{
    cout << "Welcome to the PotatOS!!!" << endl;

    while (userChoice != '5')
    {
        printMenu();

        //add a switch statement for different choices

        switch(userChoice)
        {
        case '1':
            {
            version myVersion;
            myVersion.displayVersion();
            break;
            }
        case '2':
            {
            date myDate;
            myDate.displayDate();
            break;
            }
        case '3':
            {
            directory myDirectory;
            myDirectory.showFiles();
            break;
            }
        case '4':
            {
            help myHelp;
            myHelp.showHelp();
            break;
            }
        case '5':
            {
            exitSim myExit;
            myExit.escapeSim();
            break;
            }
        default:
            cout << "PLACEHOLDER DEFAULT" << endl;
        }

        if(userChoice == '5')
        {
            exitSim myExit;
            myExit.escapeSim();
        }

    }
}

controller::~controller()
{

}
