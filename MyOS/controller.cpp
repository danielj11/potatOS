#include "controller.h"

controller::controller()
{
    userChoice = '0';
    userPCBChoice = 0;
    exitFlag = false;
}


void controller::printMenu()//prints menu of choices for user to choose from
{
    cout << "~~~MENU~~~" << endl;
    cout << "----------" << endl;
    cout << "1. Version" << endl;
    cout << "2. Date" << endl;
    cout << "3. Directory" << endl;
    cout << "4. Help" << endl;
    cout << "5. PCB Menu" << endl;
    cout << "6. Exit" << endl;
    cout << "----------" << endl;
    cout << "Enter the corresponding number for what you want to do: ";
    cin >> userChoice;
    cout << endl;

    return;
}


void controller::printPCBMenu()//prints menu of choices for user to choose from
{
    cout << "~~~PCB MENU~~~" << endl;
    cout << "--------------" << endl;
    cout << "1. Create PCB" << endl;
    cout << "2. Delete PCB" << endl;
    cout << "3. Block" << endl;
    cout << "4. Unblock" << endl;
    cout << "5. Suspend" << endl;
    cout << "6. Resume" << endl;
    cout << "7. Set priority" << endl;
    cout << "8. Show PCB" << endl;
    cout << "9. Show All" << endl;
    cout << "10. Show Ready" << endl;
    cout << "11. Show Blocked" << endl;
    cout << "--------------" << endl;
    cout << "Enter the corresponding number for what you want to do: ";
    cin >> userPCBChoice;
    cout << endl;

    return;
}


void controller::waitForInput() //waits for user input to continue
{
    string input;
    cout << "Enter C to continue: ";
    cin >> input;
    if (input == "c" || input == "C")
    {
        cout << endl;
        return;
    }
    else
    {
        waitForInput();
    }
}


void controller::runSim() //runs the simulation
{
    cout << "Welcome to the PotatOS!!!" << endl << endl;;

    while (!exitFlag)
    {
        printMenu();

        switch(userChoice)
        {
        case '1':
            {
            version myVersion;
            myVersion.displayVersion();
            waitForInput();
            break;
            }
        case '2':
            {
            date myDate;
            myDate.displayDate();
            waitForInput();
            break;
            }
        case '3':
            {
            directory myDirectory;
            myDirectory.showFiles();
            waitForInput();
            break;
            }
        case '4':
            {
            help myHelp;
            myHelp.showHelp();
            waitForInput();
            break;
            }
        case '5':
            {
            printPCBMenu();
            runPCBFunctions();
            waitForInput();
            break;
            }
        case '6':
            {
            exitSim myExit;
            exitFlag = myExit.escapeSim();
            waitForInput();
            break;
            }
        default:
            cout << "Please enter a valid input" << endl<< endl;
        }

    }
}

void controller::runPCBFunctions()
{
    switch (userPCBChoice)
    {
    case 1://CreatePCB
        {
            string nameOfProcess = "";
            int userPriority = -130;
            char userType = 'B';

            cout << "Name the process: ";
            cin >> nameOfProcess;
            cout << endl;

            while (userPriority > 128 || userPriority < -127)
            {
                cout << "Enter process priority: ";
                cin >> userPriority;
                cout << endl;
            }

            while (userType != 'A' && userType != 'S')
            {
                cout << "Enter type of process (A = application, S = system): ";
                cin >> userType;
            }

            insertPCB(setupPCB(nameOfProcess, userPriority, userType));
            break;
        }
    case 2://DeletePCB
        {
            string pcbToDelete;
            cout << "Enter the name of the PCB you want to delete: ";
            cin >> pcbToDelete;
            cout << endl;

            pcb* searchPCB = findPCB(pcbToDelete);
            if (searchPCB == NULL)
            {
                cout << "Process not found!" << endl;
            }
            else
            {
                removePCB(searchPCB);
                cout << "PCB Removed" << endl;
            }
            break;
        }
    case 3://Block
        {
            int position = 0;
            string pcbToBlock;
            bool readyFlag = true;
            bool foundFlag = false;

            cout << "Enter the name of the PCB you want to block: ";
            cin >> pcbToBlock;
            cout << endl;

            for (int i = 0; i < ready.queueSize; i++)
            {
                if (ready.heldItems[i] -> processName == pcbToBlock)
                {
                    position = i;
                    foundFlag = true;
                }
            }
            for (int i = 0; i < suspendedReady.queueSize; i++)
            {
                if (suspendedBlocked.heldItems[i] -> processName == pcbToBlock)
                {
                    position = i;
                    readyFlag = false;
                    foundFlag = true;
                }
            }

            if (foundFlag)
            {
                if (readyFlag)
                {
                    ready.heldItems[position] -> state1 = "blocked";
                    blocked.addPCB(ready.heldItems[position]);
                    ready.deletePCB(ready.heldItems[position]);
                }
                else
                {
                    suspendedReady.heldItems[position] -> state1 = "blocked";
                    suspendedBlocked.addPCB(suspendedReady.heldItems[position]);
                    suspendedReady.deletePCB(suspendedBlocked.heldItems[position]);
                }
            }
            else
            {
                cout << "Process not found" << endl;
            }

            break;
        }
    case 4://Unblock
        {
            int position = 0;
            string pcbToUnblock;
            bool blockFlag = true;
            bool foundFlag = false;

            cout << "Enter the name of the PCB you want to unblock: ";
            cin >> pcbToUnblock;
            cout << endl;

            for (int i = 0; i < blocked.queueSize; i++)
            {
                if (blocked.heldItems[i] -> processName == pcbToUnblock)
                {
                    position = i;
                    foundFlag = true;
                }
            }
            for (int i = 0; i < suspendedBlocked.queueSize; i++)
            {
                if (suspendedBlocked.heldItems[i] -> processName == pcbToUnblock)
                {
                    position = i;
                    blockFlag = false;
                    foundFlag = true;
                }
            }

            if (foundFlag)
            {
                if (blockFlag)
                {
                    blocked.heldItems[position] -> state1 = "ready";
                    ready.addPCB(blocked.heldItems[position]);
                    blocked.deletePCB(blocked.heldItems[position]);
                }
                else
                {
                    suspendedBlocked.heldItems[position] -> state1 = "ready";
                    suspendedReady.addPCB(suspendedBlocked.heldItems[position]);
                    suspendedBlocked.deletePCB(suspendedBlocked.heldItems[position]);
                }
            }
            else
            {
                cout << "Process not found" << endl;
            }

            break;
        }
    case 5://Suspend
        {
            int position = 0;
            string pcbToSuspend;
            bool readyFlag = true;
            bool foundFlag = false;

            cout << "Enter the name of the PCB you want to suspend: ";
            cin >> pcbToSuspend;
            cout << endl;

            for (int i = 0; i < ready.queueSize; i++)
            {
                if (ready.heldItems[i] -> processName == pcbToSuspend)
                {
                    position = i;
                    foundFlag = true;
                }
            }
            for (int i = 0; i < blocked.queueSize; i++)
            {
                if (blocked.heldItems[i] -> processName == pcbToSuspend)
                {
                    position = i;
                    readyFlag = false;
                    foundFlag = true;
                }
            }

            if (foundFlag)
            {
                if (readyFlag)
                {
                    ready.heldItems[position] -> state2 = "suspended";
                    suspendedReady.addPCB(ready.heldItems[position]);
                    ready.deletePCB(ready.heldItems[position]);

                }
                else
                {
                    blocked.heldItems[position] -> state2 = "suspended";
                    suspendedBlocked.addPCB(blocked.heldItems[position]);
                    blocked.deletePCB(blocked.heldItems[position]);
                }
            }
            else
            {
                cout << "Process not found" << endl;
            }

            break;
        }
    case 6://Resume
        {
            int position = 0;
            string pcbToResume;
            bool suspendedReadyFlag = true;
            bool foundFlag = false;

            cout << "Enter the name of the PCB you want to resume: ";
            cin >> pcbToResume;
            cout << endl;

            for (int i = 0; i < suspendedReady.queueSize; i++)
            {
                if (suspendedReady.heldItems[i] -> processName == pcbToResume)
                {
                    position = i;
                    foundFlag = true;
                }
            }
            for (int i = 0; i < suspendedBlocked.queueSize; i++)
            {
                if (suspendedBlocked.heldItems[i] -> processName == pcbToResume)
                {
                    position = i;
                    suspendedReadyFlag = false;
                    foundFlag = true;
                }
            }

            if (foundFlag)
            {
                if (suspendedReadyFlag)
                {
                    suspendedReady.heldItems[position] -> state2 = "not";
                    ready.addPCB(suspendedReady.heldItems[position]);
                    suspendedReady.deletePCB(suspendedReady.heldItems[position]);
                }
                else
                {
                    suspendedBlocked.heldItems[position] -> state2 = "not";
                    blocked.addPCB(suspendedBlocked.heldItems[position]);
                    suspendedBlocked.deletePCB(suspendedBlocked.heldItems[position]);
                }
            }
            else
            {
                cout << "Process not found" << endl;
            }

            break;
        }
    case 7://Set priority
        {
            string processToChange;
            int newPriority = 999;

            cout << "Enter the process name: ";
            cin >> processToChange;
            cout << endl;

            while (newPriority < -127 || newPriority > 128)
            {
                cout << "Enter the new priority: ";
                cin >> newPriority;
                cout << endl;
            }

            pcb* tempPCB = findPCB(processToChange); //checks if pcb with that name exists

            if (tempPCB == NULL) //if name doesn't exist
            {
                cout << "Process cannot be found!" << endl;
            }
            else //if it does, replace the old pcb of that name with tempPCB
            {
                tempPCB -> priority  = newPriority;

                if (tempPCB -> state1 == "ready" && tempPCB -> state2 == "not")
                {
                    for (int i = 0; i < ready.queueSize; i++)
                    {
                        if (ready.heldItems[i] -> processName == tempPCB -> processName)
                        {
                            ready.heldItems[i] = tempPCB;
                        }
                    }
                }
                if (tempPCB -> state1 == "blocked" && tempPCB -> state2 == "not")
                {
                    for (int i = 0; i < blocked.queueSize; i++)
                    {
                        if (blocked.heldItems[i] -> processName == tempPCB -> processName)
                        {
                            blocked.heldItems[i] = tempPCB;
                        }
                    }
                }
                if (tempPCB -> state1 == "ready" && tempPCB -> state2 == "suspended")
                {
                    for (int i = 0; i < suspendedReady.queueSize; i++)
                    {
                        if (suspendedReady.heldItems[i] -> processName == tempPCB -> processName)
                        {
                            suspendedReady.heldItems[i] = tempPCB;
                        }
                    }
                }
                if (tempPCB -> state1 == "blocked" && tempPCB -> state2 == "suspended")
                {
                    for (int i = 0; i < suspendedBlocked.queueSize; i++)
                    {
                        if (suspendedBlocked.heldItems[i] -> processName == tempPCB -> processName)
                        {
                            suspendedBlocked.heldItems[i] = tempPCB;
                        }
                    }
                }

            }

            break;
        }
    case 8://Show PCB
        {
            string showName;

            cout << "Enter the name of the PCB you want to show: ";
            cin >> showName;

            pcb* hold = findPCB(showName);
            if (hold == NULL)
            {
                cout << "PCB could not be found!" << endl;
            }
            else
            {
                cout << hold -> processName << " - " << hold -> state1 << " - ";
                if (hold -> state2 == "not")
                {
                    cout << "unsuspended" << " - ";
                }
                else
                {
                    cout << hold -> state2 << " - ";
                }
                cout << hold -> priority << endl;
            }
            break;
        }
    case 9://Show all
        {
            cout << "Ready queue contains: " << endl;
            for (int i = 0; i < ready.queueSize; i++)
            {
                if (ready.heldItems[i] == NULL)
                {
                    cout << "PCB could not be found!" << endl;
                }
                else
                {
                    cout << ready.heldItems[i] -> processName << " - " << ready.heldItems[i] -> state1 << " - ";
                    if (ready.heldItems[i] -> state2 == "not")
                    {
                        cout << "unsuspended" << " - ";
                    }
                    else
                    {
                        cout << ready.heldItems[i] -> state2 << " - ";
                    }
                    cout << ready.heldItems[i] -> priority << endl;
                }
            }
            waitForInput();
            cout << "Blocked queue contains: " << endl;
            for (int i = 0; i < blocked.queueSize; i++)
            {
                if (blocked.heldItems[i] == NULL)
                {
                    cout << "PCB could not be found!" << endl;
                }
                else
                {
                    cout << blocked.heldItems[i] -> processName << " - " << blocked.heldItems[i] -> state1 << " - ";
                    if (blocked.heldItems[i] -> state2 == "not")
                    {
                        cout << "unsuspended" << " - ";
                    }
                    else
                    {
                        cout << blocked.heldItems[i] -> state2 << " - ";
                    }
                    cout << blocked.heldItems[i] -> priority << endl;
                }
            }
            waitForInput();

            cout << "Suspended Ready queue contains: " << endl;
            for (int i = 0; i < suspendedReady.queueSize; i++)
            {
                if (suspendedReady.heldItems[i] == NULL)
                {
                    cout << "PCB could not be found!" << endl;
                }
                else
                {
                    cout << suspendedReady.heldItems[i] -> processName << " - " << suspendedReady.heldItems[i] -> state1 << " - ";
                    if (suspendedReady.heldItems[i] -> state2 == "not")
                    {
                        cout << "unsuspended" << " - ";
                    }
                    else
                    {
                        cout << suspendedReady.heldItems[i] -> state2 << " - ";
                    }
                    cout << suspendedReady.heldItems[i] -> priority << endl;
                }
            }
            waitForInput();

            cout << "Suspended Blocked queue contains: " << endl;
            for (int i = 0; i < suspendedBlocked.queueSize; i++)
            {
                if (suspendedBlocked.heldItems[i] == NULL)
                {
                    cout << "PCB could not be found!" << endl;
                }
                else
                {
                    cout << suspendedBlocked.heldItems[i] -> processName << " - " << suspendedBlocked.heldItems[i] -> state1 << " - ";
                    if (suspendedBlocked.heldItems[i] -> state2 == "not")
                    {
                        cout << "unsuspended" << " - ";
                    }
                    else
                    {
                        cout << suspendedBlocked.heldItems[i] -> state2 << " - ";
                    }
                    cout << suspendedBlocked.heldItems[i] -> priority << endl;
                }
            }
            break;
        }
    case 10://Show ready
        {
            cout << "Ready queue contains: " << endl;
            for (int i = 0; i < ready.queueSize; i++)
            {
                if (ready.heldItems[i] == NULL)
                {
                    cout << "PCB could not be found!" << endl;
                }
                else
                {
                    cout << ready.heldItems[i] -> processName << " - " << ready.heldItems[i] -> state1 << " - ";
                    if (ready.heldItems[i] -> state2 == "not")
                    {
                        cout << "unsuspended" << " - ";
                    }
                    else
                    {
                        cout << ready.heldItems[i] -> state2 << " - ";
                    }
                    cout << ready.heldItems[i] -> priority << endl;
                }
            }
            break;
        }
    case 11://Show blocked
        {
            cout << "Blocked queue contains: " << endl;
            for (int i = 0; i < blocked.queueSize; i++)
            {
                if (blocked.heldItems[i] == NULL)
                {
                    cout << "PCB could not be found!" << endl;
                }
                else
                {
                    cout << blocked.heldItems[i] -> processName << " - " << blocked.heldItems[i] -> state1 << " - ";
                    if (blocked.heldItems[i] -> state2 == "not")
                    {
                        cout << "unsuspended" << " - ";
                    }
                    else
                    {
                        cout << blocked.heldItems[i] -> state2 << " - ";
                    }
                    cout << blocked.heldItems[i] -> priority << endl;
                }
            }
            break;
        }
    default:
        {
            cout << "Not a valid input" << endl;
        }
    }

    return;
}


pcb* controller::allocatePCB() //allocates memory for a new PCB
{
    pcb* newPCB = new pcb;

    return newPCB;
}


pcb* controller::findPCB(string nameToFind) //looks for PCB with same name as input in all queues
{
    pcb* tempPCB = new pcb;

    if (ready.queueSize > 0)
    {
        for (int i = 0; i < ready.queueSize; i++)
        {
            if (ready.heldItems[i] -> processName == nameToFind)
            {
                tempPCB = ready.heldItems[i];
                return tempPCB;
            }
        }
    }

    if (blocked.queueSize > 0)
    {
        for (int i = 0; i < blocked.queueSize; i++)
        {
            if (blocked.heldItems[i] -> processName == nameToFind)
            {
                tempPCB = blocked.heldItems[i];
                return tempPCB;
            }
        }
    }

    if (suspendedReady.queueSize > 0)
    {
        for (int i = 0; i < suspendedReady.queueSize; i++)
        {
            if (suspendedReady.heldItems[i] -> processName == nameToFind)
            {
                tempPCB = suspendedReady.heldItems[i];
                return tempPCB;
            }
        }
    }

    if (suspendedBlocked.queueSize > 0)
    {
        for (int i = 0; i < suspendedBlocked.queueSize; i++)
        {
            if (suspendedBlocked.heldItems[i] -> processName == nameToFind)
            {
                tempPCB = suspendedBlocked.heldItems[i];
                return tempPCB;
            }
        }
    }

    return NULL;
}


pcb* controller::setupPCB(string name, int pcbPriority, char type) //set ups PCB information
{
    pcb* tempPCB;
    tempPCB = allocatePCB();
    tempPCB -> processName = name;
    tempPCB -> processType = type;
    tempPCB -> priority = pcbPriority;
    tempPCB -> state1 = "ready";
    tempPCB -> state2 = "not";//not suspended

    pcb* checkPCB = findPCB(tempPCB -> processName);//look to see if process with same name is in a queue

    if (checkPCB != NULL) //if pcb is a duplicate, return NULL
    {
        tempPCB = NULL;
        delete checkPCB;
        return tempPCB;
    }

    tempPCB -> state1 == "ready";//until further notice

    return tempPCB;
}


void controller::insertPCB(pcb* pcbToInsert) //adds PCB into queue
{
    if(pcbToInsert -> state1 == "ready" && pcbToInsert -> state2 == "not")
    {
        ready.addPCB(pcbToInsert);
        return;
    }

    if(pcbToInsert -> state1 == "blocked" && pcbToInsert -> state2 == "not")
    {
        blocked.addPCB(pcbToInsert);
        return;
    }

    if(pcbToInsert -> state1 == "blocked" && pcbToInsert -> state2 == "suspended")
    {
        suspendedBlocked.addPCB(pcbToInsert);
        return;
    }

    if(pcbToInsert -> state1 == "ready" && pcbToInsert -> state2 == "suspended")
    {
        cout << "Suspended Ready Here!" << endl;
        suspendedReady.addPCB(pcbToInsert);
        return;
    }

    else
    {
        cout << "WHAT DID YOU DO?" << endl;
        cout << pcbToInsert -> state1 << endl;
        cout << pcbToInsert -> state2 << endl;
    }

    return;

}


void controller::removePCB(pcb* pcbToRemove)//removes pcb from queue
{
    if (ready.queueSize > 0)
    {
        for (int i = 0; i < ready.queueSize; i++)
        {
            if (ready.heldItems[i] == pcbToRemove)
            {
                freePCB(ready.heldItems[i]);
                /*ready.heldItems.erase(ready.heldItems.begin()+i);
                ready.queueSize = ready.heldItems.size();*/
                ready.deletePCB(pcbToRemove);
                cout << "DELETE WORKED!!!" << endl;
                return;
            }
        }
    }

    if (blocked.queueSize > 0)
    {
        for (int i = 0; i < blocked.queueSize; i++)
        {
            if (blocked.heldItems[i] == pcbToRemove)
            {
                freePCB(blocked.heldItems[i]);
                /*blocked.heldItems.erase(blocked.heldItems.begin()+i);
                blocked.queueSize = blocked.heldItems.size();*/
                blocked.deletePCB(pcbToRemove);
                return;
            }
        }
    }

    if (suspendedReady.queueSize > 0)
    {
        for (int i = 0; i < suspendedReady.queueSize; i++)
        {
            if (suspendedReady.heldItems[i] == pcbToRemove)
            {
                freePCB(suspendedReady.heldItems[i]);
                /*suspendedReady.heldItems.erase(suspendedReady.heldItems.begin()+i);
                suspendedReady.queueSize = suspendedReady.heldItems.size();*/
                suspendedReady.deletePCB(pcbToRemove);
                return;
            }
        }
    }

    if (suspendedBlocked.queueSize > 0)
    {
        for (int i = 0; i < suspendedBlocked.queueSize; i++)
        {
            if (suspendedBlocked.heldItems[i] == pcbToRemove)
            {
                freePCB(suspendedBlocked.heldItems[i]);
                /*suspendedBlocked.heldItems.erase(suspendedBlocked.heldItems.begin()+i);
                suspendedBlocked.queueSize = suspendedBlocked.heldItems.size();*/
                suspendedBlocked.deletePCB(pcbToRemove);
                return;
            }
        }
    }

    cout << "Not Found, cannot delete" << endl;
    return;
}


void controller::freePCB(pcb* pcbToFree)//frees memory of pcb
{
    delete pcbToFree;
}


controller::~controller()
{
}
