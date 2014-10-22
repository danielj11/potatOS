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
    cout << "6. Scheduler Menu"  << endl;
    cout << "7. Exit" << endl;
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
    cout << "1. Suspend" << endl;
    cout << "2. Resume" << endl;
    cout << "3. Set priority" << endl;
    cout << "4. Show PCB" << endl;
    cout << "5. Show All" << endl;
    cout << "6. Show Ready" << endl;
    cout << "7. Show Blocked" << endl;
    cout << "--------------" << endl;
    cout << "Enter the corresponding number for what you want to do: ";
    cin >> userPCBChoice;
    cout << endl;

    return;
}


void controller::printScheduleMenu() //prints menu of choices for user to choose from
{
    cout << "~SCHEDULER MENU~" << endl;
    cout << "----------------" << endl;
    cout << "1. SJF" << endl;
    cout << "2. FIFO" << endl;
    cout << "3. STCF" << endl;
    cout << "4. FPPS" << endl;
    cout << "5. RR" << endl;
    cout << "6. MLFQ" << endl;
    cout << "7. LS" << endl;
    cout << "----------------" << endl;
    cout << "Enter the corresponding number for what you want to do: ";
    cin >> userScheduleChoice;
    cout << endl;
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
            printScheduleMenu();
            runScheduleFunctions();
            waitForInput();
            break;
            }
        case '7':
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


void controller::runPCBFunctions() //runs PCB functions
{
    switch (userPCBChoice)
    {
    case 1://Suspend
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
    case 2://Resume
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
    case 3://Set priority
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
    case 4://Show PCB
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
    case 5://Show all
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
    case 6://Show ready
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

            cout << endl;
            break;
        }
    case 7://Show blocked
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


void controller::runScheduleFunctions() //runs scheduling functions
{
    switch(userScheduleChoice)
    {
    case 1:
        {
            SJF();
            resetSchedulers();
            break;
        }
    case 2:
        {
            FIFO();
            resetSchedulers();
            break;
        }
    case 3:
        {
            STCF();
            resetSchedulers();
            break;
        }
    case 4:
        {
            FPPS();
            resetSchedulers();
            break;
        }
    case 5:
        {
            RR();
            resetSchedulers();
            break;
        }
    case 6:
        {
            MLFQ();
            resetSchedulers();
            break;
        }
    case 7:
        {
            LS();
            resetSchedulers();
            break;
        }
    default:
        {
            cout << "Not a valid input!" << endl;
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


//creates a pcb
pcb* controller::createProcess(string name, char pcbClass, int pcbPriority, int mem, int timeR, int timeA, int percent)
{
    pcb* tempPCB;
    tempPCB = allocatePCB();
    tempPCB -> processName = name;
    tempPCB -> processType = pcbClass;
    tempPCB -> priority = pcbPriority;
    tempPCB -> state1 = "ready";
    tempPCB -> state2 = "not";//not suspended
    tempPCB -> timeRemaining = timeR;
    tempPCB -> timeOfArrival = timeA;
    tempPCB -> cpuPercent = percent;
    tempPCB -> memory = mem;

    return tempPCB;
}


void controller::printReady() //prints ready queue for scheduler functions
{
    cout << "Ready queue contains: " << endl;
    cout << "Name - Time Remaining" << endl;
    for (int i = 0; i < ready.queueSize; i++)
    {
        if (ready.heldItems[i] == NULL)
        {
            cout << "PCB could not be found!" << endl;
        }
        else
        {
            cout << ready.heldItems[i] -> processName << " - " << ready.heldItems[i] -> timeRemaining << endl;
        }
    }

    cout << endl;

    return;
}


bool controller::readFile() //reads in file for use in schedulers
{
    string wordString;
    string userFile; //Stores user's file name
    int counter = 0; //Counts words in file
    pcb* tempPCB;

    //New PCB's contents
    string newName;
    char newClass;
    int newPriority;
    int newMemory;
    int remaining;
    int arrival;
    int newPercent;

    //cout << endl;
    cout << "Enter your filename: ";
    cin >> userFile;
    ifstream inputFile(userFile.c_str());

    if (!inputFile)
    {
        cout << endl;
        return false;
    }
    else
    {
        while(!inputFile.eof())
        {
            inputFile >> wordString;

            counter++;

            switch (counter)
            {
            case 1://name
                newName = wordString;
                break;
            case 2://class
                newClass = wordString[0];
                break;
            case 3://priority
                newPriority = atoi(wordString.c_str());
                break;
            case 4://memory
                newMemory = atoi(wordString.c_str());
                break;
            case 5://time remaining
                remaining = atoi(wordString.c_str());
                break;
            case 6://time of arrival
                //cout << wordString << endl;
                arrival = atoi(wordString.c_str());
                break;
            case 7://percentage of CPU
                newPercent = atoi(wordString.c_str());
                break;
            default:
                cout << "Error!!!" << endl;
            }

            if (counter == 7)//reset counter for next pcb's contents
            {
                counter = 0;
                tempPCB = createProcess(newName, newClass, newPriority, newMemory, remaining, arrival, newPercent);
                filepcbs.push_back(tempPCB);
            }
        }

    cout << endl;
    return true;

    }
}


void controller::resetSchedulers() //resets ready queue
{
    filepcbs.clear();
    ready.heldItems.clear();
    ready.head = NULL;
    ready.tail = NULL;
    blocked.heldItems.clear();
    blocked.head = NULL;
    blocked.tail = NULL;
}


//runs processes using shortest job first schedule with full knowledge of all processes
void controller::SJF()
{
    if(!readFile())//read in file
    {
        cout << "File not found!!!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("SJF.txt");

    char fit = chooseFit();
    setRunning();

    int turnaroundTime = 0; //turnaround time of process
    int shortestTimeRemaining = filepcbs[0] -> timeRemaining; //used to sort ready queue
    int position = 0;
    int numberOfPCBs = filepcbs.size();
    int completedPCBs= 0;
    int counter = 0;
    vector <int> storeTurnaround; //holds turnaround time of each process to calculate average
    bool done = false;

    while (ready.queueSize != numberOfPCBs)//while there are more pcbs in the file than are in ready queue
    {
        for (int i = 0; i < filepcbs.size(); i++)
        {
            //looks for shortest remaining time of all pcbs to put in ready queue
            if (filepcbs[i] -> timeRemaining < shortestTimeRemaining)
            {
                shortestTimeRemaining = filepcbs[i] -> timeRemaining;
                position = i;
            }
        }
        //cout << filepcbs[position] -> processName << " has entered the system!" << endl;
        outFile << filepcbs[position] -> processName << " has entered the system!" << endl;
        ready.addPCB(filepcbs[position]);
        filepcbs.erase(filepcbs.begin() + position);//delete same PCB from filepcbs
        position = 0;
        shortestTimeRemaining = filepcbs[0] -> timeRemaining;
    }
    printReady();
    cout << endl;
    while(completedPCBs != numberOfPCBs)
    {
        ///begin running queue stuff
        int runningPos = -1;
        //check to see if empty
        for (int i = 0;i < running.heldItems.size(); i++)
        {
            if (running.heldItems[i] -> processName != "empty")
            {
                //cout << "FOUND NOT EMPTY - " << running.heldItems[i] -> processName << endl;
                runningPos = i;
                break;
            }
        }

        if (runningPos == -1 && ready.heldItems.size() > 0)
        {
            running.addPCBFit(fit, ready.heldItems[0]);
            outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
            ready.deletePCB(ready.heldItems[0]);
        }
        else if (runningPos > -1) //if a process is in the running queue, decrement its time remaining
        {
            running.heldItems[runningPos] -> timeRemaining = running.heldItems[runningPos] -> timeRemaining - 1;

            if (running.heldItems[runningPos] -> timeRemaining == 0)
            {
                outFile <<running.heldItems[runningPos] -> processName << " has completed!" << endl;

                turnaroundTime = counter - running.heldItems[runningPos] -> timeOfArrival;
                storeTurnaround.push_back(turnaroundTime);
                running.removePCB();
                completedPCBs++;
                //if there is something in the ready queue, add it to the running queue
                if (ready.heldItems.size() > 0)
                {
                    running.addPCBFit(fit,ready.heldItems[0]);
                    outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
                    ready.deletePCB(ready.heldItems[0]);
                }
                //if there is nothing in the ready queue, you're done
                else
                {
                    done = true;
                }
            }
        }

        counter++;
    }

    cout << "All processes have completed!" << endl;
    cout << "Check file for details!" << endl << endl;

    turnaroundTime = 0;
    for (int i = 0; i < storeTurnaround.size(); i++)
    {
        turnaroundTime = turnaroundTime + storeTurnaround[i];
    }
    //Calculate and print average turnaround time
    turnaroundTime = turnaroundTime / storeTurnaround.size();
    outFile << endl << "Total time to completion: " << counter << endl;
    outFile << "Average Turnaround Time: " << turnaroundTime << endl;

    outFile.close();

    return;
}


//runs processes using first in first out scheduler
void controller::FIFO()
{
    if(!readFile())//read in file
    {
        cout << "File not found!!!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("FIFO.txt");

    char fit = chooseFit();
    setRunning();

    int turnaroundTime = 0; //turnaround time of process
    int counter = 0;
    bool done = false;
    int numberOfPCBs= filepcbs.size();
    vector <int> storeTurnaround; //holds turnaround time of each process to calculate average

    while (!done)
    {
        if (filepcbs.size() > 0)
        {
            if (filepcbs[0] -> timeOfArrival == counter)//if it's time for a process to arrive, add it to ready queue
            {
                ready.addPCB(filepcbs[0]);
                outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
                filepcbs.erase(filepcbs.begin()+0);

                if (ready.queueSize == numberOfPCBs) //if all pcbs are in ready queue, print its contents
                {
                    printReady();
                }
            }
        }


        ///begin running queue stuff
        int runningPos = -1;
        //check to see if empty
        for (int i = 0;i < running.heldItems.size(); i++)
        {
            if (running.heldItems[i] -> processName != "empty")
            {
                //cout << "FOUND NOT EMPTY - " << running.heldItems[i] -> processName << endl;
                runningPos = i;
            }
        }

        if (runningPos == -1 && ready.heldItems.size() > 0)
        {
            running.addPCBFit(fit, ready.heldItems[0]);
            outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
            ready.deletePCB(ready.heldItems[0]);
        }
        else if (runningPos > -1) //if a process is in the running queue, decrement its time remaining
        {
            running.heldItems[runningPos] -> timeRemaining = running.heldItems[runningPos] -> timeRemaining - 1;

            if (running.heldItems[runningPos] -> timeRemaining == 0)
            {
                outFile <<running.heldItems[runningPos] -> processName << " has completed!" << endl;

                turnaroundTime = counter - running.heldItems[runningPos] -> timeOfArrival;
                storeTurnaround.push_back(turnaroundTime);
                running.removePCB();
                //if there is something in the ready queue, add it to the running queue
                if (ready.heldItems.size() > 0)
                {
                    running.addPCBFit(fit,ready.heldItems[0]);
                    outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
                    ready.deletePCB(ready.heldItems[0]);
                }
                //if there is nothing in the ready queue, you're done
                else
                {
                    done = true;
                }
            }
        }

        counter++;

    }

    turnaroundTime = 0;

    for (int i = 0; i < storeTurnaround.size(); i++) //calculate average turnaround time
    {
        turnaroundTime += storeTurnaround[i];
    }

    turnaroundTime = turnaroundTime/storeTurnaround.size();

    cout << "All processes have completed!" << endl;
    cout << "Check file for details!" << endl << endl;
    outFile << endl << "Completion Time: " << counter << endl;
    outFile << "Average Turnaround Time: " << turnaroundTime << endl << endl;

    return;
}


//runs processes using shortest time to completion first scheduler
void controller::STCF()
{
    if(!readFile())//read in file
    {
        cout << "File not found!!!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("STCF.txt");

    char fit = chooseFit();
    setRunning();

    int turnaroundTime = 0; //turnaround time of process
    int position = 0; //used to find exact lpcations of pcbs
    int counter = 0; //timer
    bool done = false; //determines when scheduler is finished
    vector <int> storeTurnaround; //holds turnaround time of each process to calculate average

    while(!done) //while there are still processes that need to finish
    {
        if (filepcbs.size() != 0)
        {
            if (filepcbs[0] -> timeOfArrival == counter)//if it's time for a process to arrive, add it to ready queue
            {
                if (ready.queueSize == 0)//add pcb to beginning of ready queue
                {
                    ready.addPCB(filepcbs[0]);
                    outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
                    filepcbs.erase(filepcbs.begin()+0);
                }
                else  //find where to insert pcb
                {
                    if (filepcbs[0] -> timeRemaining > ready.heldItems[ready.queueSize-1] -> timeRemaining)
                    {
                        ready.addPCB(filepcbs[0]);
                        outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
                        filepcbs.erase(filepcbs.begin()+0);
                    }

                    else
                    {
                        bool inserted = false;

                        while (!inserted)
                        {
                            if (filepcbs[0] -> timeRemaining < ready.heldItems[position] -> timeRemaining)
                            {
                                ready.heldItems.insert(ready.heldItems.begin() + position, filepcbs[0]);
                                outFile << ready.heldItems[position] -> processName << " has entered the system!" << endl;
                                filepcbs.erase(filepcbs.begin()+0);
                                ready.queueSize = ready.heldItems.size();
                                inserted = true;
                                break;
                            }
                            position++;
                        }
                    }
                }
            }
        }

        ///begin running queue stuff
        int runningPos = -1;
        //check to see if empty
        for (int i = 0;i < running.heldItems.size(); i++)
        {
            if (running.heldItems[i] -> processName != "empty")
            {
                //cout << "FOUND NOT EMPTY - " << running.heldItems[i] -> processName << endl;
                runningPos = i;
            }
        }

        if (runningPos == -1 && ready.heldItems.size() > 0)
        {
            running.addPCBFit(fit, ready.heldItems[0]);
            outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
            ready.deletePCB(ready.heldItems[0]);
        }
        else if (runningPos > -1) //if a process is in the running queue, decrement its time remaining
        {
            running.heldItems[runningPos] -> timeRemaining = running.heldItems[runningPos] -> timeRemaining - 1;

            if (running.heldItems[runningPos] -> timeRemaining == 0)
            {
                outFile <<running.heldItems[runningPos] -> processName << " has completed!" << endl;

                turnaroundTime = counter - running.heldItems[runningPos] -> timeOfArrival;
                storeTurnaround.push_back(turnaroundTime);
                running.removePCB();
                if (ready.heldItems.size() > 0)
                {
                    running.addPCBFit(fit,ready.heldItems[0]);
                    outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
                    ready.deletePCB(ready.heldItems[0]);
                }
                else
                {
                    done = true;
                }
            }
        }

        counter++;

    }

    turnaroundTime = 0;

    for (int i = 0; i < storeTurnaround.size(); i++) //calculate average turnaround time
    {
        turnaroundTime += storeTurnaround[i];
    }

    turnaroundTime = turnaroundTime/storeTurnaround.size();

    cout << "All processes have completed!" << endl;
    cout << "Check file for details!" << endl << endl;
    outFile << endl << "Completion Time: " << counter << endl;
    outFile << "Average Turnaround Time: " << turnaroundTime << endl << endl;

    return;
}


//runs processes using Fixed Priority Pre-Emptive Scheduling
void controller::FPPS()
{
    if(!readFile())//read in file
    {
        cout << "File not found!!!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("FPPS.txt");

    char fit = chooseFit();
    setRunning();

    int turnaroundTime = 0; //turnaround time of process
    int position = 0; //used to find exact lpcations of pcbs
    int numberOfPCBs = filepcbs.size();
    int counter = 0; //timer
    bool done = false; //determines when scheduler is finished
    vector <int> storeTurnaround; //holds turnaround time of each process to calculate average

    while(!done) //while there are still processes that need to finish
    {
        if (filepcbs.size() != 0)
        {
            if (filepcbs[0] -> timeOfArrival == counter)//if it's time for a process to arrive, add it to ready queue
            {
                if (ready.queueSize == 0)
                {
                    ready.addPCB(filepcbs[0]);
                    outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
                    filepcbs.erase(filepcbs.begin()+0);
                }
                else
                {
                    if (filepcbs[0] -> priority < ready.heldItems[ready.queueSize-1] -> priority)
                    {
                        ready.addPCB(filepcbs[0]);
                        outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
                        filepcbs.erase(filepcbs.begin()+0);
                    }

                    else
                    {
                        bool inserted = false;

                        while (!inserted)
                        {
                            if (filepcbs[0] -> priority > ready.heldItems[position] -> priority)
                            {
                                ready.heldItems.insert(ready.heldItems.begin() + position, filepcbs[0]);
                                outFile << ready.heldItems[position] -> processName << " has entered the system!" << endl;
                                filepcbs.erase(filepcbs.begin()+0);
                                ready.queueSize = ready.heldItems.size();
                                inserted = true;
                                break;
                            }
                            position++;
                        }
                    }
                }

                if (ready.queueSize == numberOfPCBs)
                {
                    printReady();
                }
            }
        }

        ///begin running queue stuff
        int runningPos = -1;
        //check to see if empty
        for (int i = 0;i < running.heldItems.size(); i++)
        {
            if (running.heldItems[i] -> processName != "empty")
            {
                //cout << "FOUND NOT EMPTY - " << running.heldItems[i] -> processName << endl;
                runningPos = i;
            }
        }

        if (runningPos == -1 && ready.heldItems.size() > 0)
        {
            running.addPCBFit(fit, ready.heldItems[0]);
            outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
            ready.deletePCB(ready.heldItems[0]);
        }
        else if (runningPos > -1) //if a process is in the running queue, decrement its time remaining
        {
            running.heldItems[runningPos] -> timeRemaining = running.heldItems[runningPos] -> timeRemaining - 1;

            if (running.heldItems[runningPos] -> timeRemaining == 0)
            {
                outFile <<running.heldItems[runningPos] -> processName << " has completed!" << endl;

                turnaroundTime = counter - running.heldItems[runningPos] -> timeOfArrival;
                storeTurnaround.push_back(turnaroundTime);
                running.removePCB();
                if (ready.heldItems.size() > 0)
                {
                    running.addPCBFit(fit,ready.heldItems[0]);
                    outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
                    ready.deletePCB(ready.heldItems[0]);
                }
                else
                {
                    done = true;
                }
            }
        }

        counter++;

    }

    turnaroundTime = 0;

    for (int i = 0; i < storeTurnaround.size(); i++) //calculate average turnaround time
    {
        turnaroundTime += storeTurnaround[i];
    }

    turnaroundTime = turnaroundTime/storeTurnaround.size();

    cout << "All processes have completed!" << endl;
    cout << "Check file for details!" << endl << endl;
    outFile << endl << "Completion Time: " << counter << endl;
    outFile << "Average Turnaround Time: " << turnaroundTime << endl << endl;

    return;
}


//runs processes using round robin scheduling
void controller::RR()
{
    if(!readFile())//read in file
    {
        cout << "File not found!!!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("RR.txt");

    int turnaroundTime = 0; //turnaround time of process
    int numberOfPCBs = filepcbs.size();
    int counter = 0; //timer
    bool done = false; //determines when scheduler is finished
    vector <int> storeTurnaround; //holds turnaround time of each process to calculate average
    int timeQuantum = 0;
    int quantumRemaining = 0;
    pcb* tempPCB = new pcb;

    cout << "Enter a time quantum: ";
    cin >> timeQuantum;
    cout << endl;

    quantumRemaining = timeQuantum;

    while (!done) //while there arte still processes to run
    {
        if (ready.queueSize == 0 && filepcbs.size() == 0)
        {
            cout << "All processes have completed!" << endl;
            cout << "Check file for details!" << endl << endl;
            done = true;
        }

        if (filepcbs.size() > 0)
        {
            if (filepcbs[0] -> timeOfArrival == counter)
            {
                ready.addPCB(filepcbs[0]);
                outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
                filepcbs.erase(filepcbs.begin()+0);

                if (ready.queueSize == numberOfPCBs)
                {
                    printReady();
                }
            }
        }

        if (counter == 0)
        {
            outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
        }

        if (ready.queueSize != 0)
        {
            if (quantumRemaining > 0)
            {
                ready.heldItems[0] -> timeRemaining = ready.heldItems[0] -> timeRemaining - 1;
                quantumRemaining--;
            }

            if (ready.heldItems[0] -> timeRemaining == 0) //remove process if finished
            {
                outFile << ready.heldItems[0] -> processName << " has completed!" << endl;
                turnaroundTime = counter - ready.heldItems[0] -> timeOfArrival;
                storeTurnaround.push_back(turnaroundTime);
                ready.deletePCB(ready.heldItems[0]);
                quantumRemaining = timeQuantum;
            }

            if (quantumRemaining == 0)
            {
                tempPCB = ready.heldItems[0];
                ready.deletePCB(tempPCB);
                ready.addPCB(tempPCB);
                outFile << ready.heldItems[0] -> processName << " is now running!" << endl;
                quantumRemaining = timeQuantum;
            }
        }

        counter++;
    }

    //calculate and print total completion time and average turnaround time
    turnaroundTime = 0;
    for (int i = 0; i < storeTurnaround.size(); i++)
    {
        turnaroundTime = turnaroundTime + storeTurnaround[i];
    }
    turnaroundTime = turnaroundTime / storeTurnaround.size();

    outFile << endl << "Total completion time: " << counter << endl;
    outFile << "Average turnaround time: " << turnaroundTime << endl << endl;

    outFile.close();

    delete tempPCB;

    return;
}


//runs processes using Multilevel Feedback Queue scheduling
void controller::MLFQ()
{
    if(!readFile())//read in file
    {
        cout << "File not found!!!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("MLFQ.txt");

    int turnaroundTime = 0; //turnaround time of process
    int numberOfPCBs = filepcbs.size();
    int counter = 0; //timer
    bool done = false; //determines when scheduler is finished
    vector <int> storeTurnaround; //holds turnaround time of each process to calculate average
    int timeQuantum = 0; //time quantum for current queue
    int quantumRemaining = 0; //hoe long until current time quantum is over
    pcb* tempPCB = new pcb; //temporary pcb
    int position = -1; //used to find location of processes in ready queue
    int queueCount = 0;//how many queues there are
    int currentQueue = 0; //what queue is active
    int queueNum = 0; //used to store numbers in storeAllot
    vector <int> storeAllot;//stores time allotment for each queue
    int remainingCycles = 0; //how many cycles are left until round robin begins

    cout << "How many queues do you want?: ";
    cin >> queueCount;
    cout << endl;
    currentQueue = queueCount;

    while (queueNum < queueCount)
    {
        cout << "Enter time allotment for queue " << queueNum + 1 << ": ";
        cin >> timeQuantum;
        storeAllot.push_back(timeQuantum);
        queueNum++;
    }
    cout << endl;

    cout << "How many cycles before round robin?: ";
    cin >> remainingCycles;
    cout << endl;

    for (int i = 0; i < filepcbs.size();i++)
    {
        filepcbs[i] -> priority = queueCount;
    }

    quantumRemaining = storeAllot[currentQueue - 1];
    while (!done)
    {
        if (ready.queueSize == 0 && filepcbs.size() == 0)
        {
            cout << "All processes have completed!" << endl;
            cout << "Check file for details!" << endl << endl;
            done = true;
        }

        if (filepcbs[0] -> timeOfArrival == counter)
        {
            ready.addPCB(filepcbs[0]);
            outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
            filepcbs.erase(filepcbs.begin()+0);

            if (ready.queueSize == numberOfPCBs)
            {
                printReady();
            }
        }

        if (ready.queueSize != 0)
        {
            while (remainingCycles > 0)
            {
                while (position == -1)
                {
                    for (int i = 0; i < ready.queueSize; i++) //look for a PCB that's in current queue
                    {
                        if (ready.heldItems[i] -> priority == currentQueue)
                        {
                            //cout << "New Position is " << i << endl;
                            position = i;
                        }
                    }

                    if (position == -1) //change queues if current one has no processes
                    {
                        currentQueue = currentQueue - 1;
                        if (currentQueue == 0)
                        {
                            currentQueue = queueCount;
                            //cout << "CYCLE CHANGE" << endl;
                            remainingCycles--;
                        }
                        quantumRemaining = storeAllot[currentQueue - 1];
                    }
                }

                while (quantumRemaining > 0)
                {
                    if (filepcbs[0] -> timeOfArrival == counter)
                    {
                        ready.addPCB(filepcbs[0]);
                        outFile << filepcbs[0] -> processName << " has entered the system!" << endl;
                        filepcbs.erase(filepcbs.begin()+0);

                        if (ready.queueSize == numberOfPCBs)
                        {
                            printReady();
                        }
                    }

                    ready.heldItems[position] -> timeRemaining = ready.heldItems[position] -> timeRemaining - 1;
                    if (ready.heldItems[position] -> timeRemaining == 0)
                    {
                        outFile << ready.heldItems[position] -> processName << "has completed!" << endl;
                        turnaroundTime = counter - ready.heldItems[position] -> timeOfArrival;
                        storeTurnaround.push_back(turnaroundTime);
                        ready.deletePCB(ready.heldItems[position]);
                    }
                    counter++;
                    quantumRemaining--;
                }

                //reduce priority of current process and move it to bottom of queue
                ready.heldItems[position] -> priority = ready.heldItems[position] -> priority - 1;

                if (ready.heldItems[position] -> priority < 0)
                {
                    ready.heldItems[position] -> priority = 0;
                }

                tempPCB = ready.heldItems[position];
                ready.deletePCB(tempPCB);
                ready.addPCB(tempPCB);

                currentQueue--; //change queue
                if (currentQueue == 0)
                {
                    currentQueue = queueCount;
                    remainingCycles--;
                }
                quantumRemaining = storeAllot[currentQueue - 1];

                position = -1;

            } //cycles are completed

            ///since cycles are completed, use standard round robin on all remaining processes
            if (ready.queueSize != 0)
            {
                if (quantumRemaining > 0)
                {
                    ready.heldItems[0] -> timeRemaining = ready.heldItems[0] -> timeRemaining - 1;
                    quantumRemaining--;
                }

                if (ready.heldItems[0] -> timeRemaining == 0) //remove process if finished
                {
                    outFile << ready.heldItems[0] -> processName << " has completed!" << endl;

                    turnaroundTime = counter - ready.heldItems[0] -> timeOfArrival;
                    storeTurnaround.push_back(turnaroundTime);
                    ready.deletePCB(ready.heldItems[0]);
                    quantumRemaining = storeAllot[storeAllot.size()-1];
                }

                if (quantumRemaining == 0)
                {
                    tempPCB = ready.heldItems[0];
                    ready.deletePCB(tempPCB);
                    ready.addPCB(tempPCB);
                    quantumRemaining = timeQuantum;
                }

                counter++;
            }
        } //end queue size if statement
    }

    //calculate and print total completion time and average turnaround time
    turnaroundTime = 0;
    for (int i = 0; i < storeTurnaround.size(); i++)
    {
        turnaroundTime = turnaroundTime + storeTurnaround[i];
    }
    turnaroundTime = turnaroundTime / storeTurnaround.size();

    outFile << endl << "Total completion time: " << counter << endl;
    outFile << "Average turnaround time: " << turnaroundTime << endl << endl;

    outFile.close();

    return;

}


//runs processes using lottery scheduling
void controller::LS()
{
    if(!readFile())//read in file
    {
        cout << "File not found!!!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("LS.txt");

    int turnaroundTime = 0; //turnaround time of process
    int counter = 0; //timer
    bool done = false; //determines when scheduler is finished
    vector <int> storeTurnaround; //holds turnaround time of each process to calculate average
    int userTickets = 0; //used to store number of tickets the user wants
    int totalTickets = 0; //how many tickets the current processes have
    int timeQuantum = 50; //how long the time quantum lasts
    int quantumRemaining = timeQuantum; //how long until time quantum is over
    int currentTicket = 0; //used to find process in ready queue
    int position = 0; //position of process in ready queue

    cout << "Enter the number of tickets: ";
    cin >> userTickets;
    cout << endl;

    while (!done)
    {
        if (filepcbs[0] -> timeOfArrival == counter)
        {
            filepcbs[0] -> ticketAmount = ((filepcbs[0] -> cpuPercent) * userTickets) / 100; //calculate tickets

            //cout << filepcbs[0] -> processName << " has entered the system!" << endl;
            outFile << filepcbs[0] -> processName << " has entered the system!" << endl;

            //if there are not enough tickets left, add process to blocked queue
            if (filepcbs[0] -> ticketAmount + totalTickets > userTickets)
            {
                filepcbs[0] -> state1 = "blocked";
                outFile << filepcbs[0] -> processName << " is blocked!" << endl;
                blocked.addPCB(filepcbs[0]);
                filepcbs.erase(filepcbs.begin()+0);
            }

            //if there are, add it to ready queue
            else
            {
                ready.addPCB(filepcbs[0]);
                totalTickets = totalTickets + filepcbs[0] -> ticketAmount;
                filepcbs.erase(filepcbs.begin()+0);
            }
        }

        int ticketChoice = rand() % totalTickets;

        //find position of process in ready queue
        currentTicket = 0;
        for (int i = 0; i < ready.queueSize; i++)
        {
            currentTicket = currentTicket + ready.heldItems[0] -> ticketAmount;
            if (currentTicket >= ticketChoice)
            {
                position = i;
                outFile << "The lottery has chosen the process " << ready.heldItems[i] -> processName << " to run."<< endl;
                break;
            }
        }

        //outFile << ready.heldItems[position] -> processName << " is now running." << endl;

        quantumRemaining = timeQuantum;

        while (quantumRemaining > 0)
        {
            //check to see if anything in blocked queue can be added to ready
            if (blocked.queueSize > 0 && totalTickets < userTickets)
            {
                for (int i = 0; i < blocked.queueSize; i++)
                {
                    if (blocked.heldItems[i] -> ticketAmount + totalTickets <= userTickets)
                    {
                        blocked.heldItems[i] -> state1 = "unblocked";
                        outFile << blocked.heldItems[i] -> processName <<  "is unblocked!";
                        ready.addPCB(blocked.heldItems[i]);
                        totalTickets = totalTickets + blocked.heldItems[i] -> ticketAmount;
                        blocked.deletePCB(blocked.heldItems[i]);
                        break;
                    }
                }
            }

            ready.heldItems[position] -> timeRemaining = ready.heldItems[position] -> timeRemaining - 1;
            counter++;

            if (filepcbs[0] -> timeOfArrival == counter)
            {
                filepcbs[0] -> ticketAmount = ((filepcbs[0] -> cpuPercent) * userTickets) / 100; //calculate tickets

                //cout << filepcbs[0] -> processName << " has entered the system!" << endl;
                outFile << filepcbs[0] -> processName << " has entered the system!" << endl;

                //if there are not enough tickets left, add process to blocked queue
                if (filepcbs[0] -> ticketAmount + totalTickets > userTickets)
                {
                    filepcbs[0] -> state1 = "blocked";
                    //cout << filepcbs[0] -> processName << " is blocked!" << endl;
                    outFile << filepcbs[0] -> processName << " is blocked!" << endl;
                    blocked.addPCB(filepcbs[0]);
                    filepcbs.erase(filepcbs.begin()+0);
                }
                //if there are enough, add it to ready queue
                else
                {
                    ready.addPCB(filepcbs[0]);
                    totalTickets = totalTickets + filepcbs[0] -> ticketAmount;
                    filepcbs.erase(filepcbs.begin()+0);
                }
            }

            ready.heldItems[position] -> timeRemaining = ready.heldItems[position] -> timeRemaining - 1;

            //if current process has finished
            if (ready.heldItems[position] -> timeRemaining == 0)
            {
                //cout << ready.heldItems[position] -> processName << " has completed!" << endl;
                outFile << ready.heldItems[position] -> processName << " has completed!" << endl;
                turnaroundTime = counter - ready.heldItems[position] -> timeOfArrival;
                storeTurnaround.push_back(turnaroundTime);
                totalTickets = totalTickets - ready.heldItems[position] -> ticketAmount;
                ready.deletePCB(ready.heldItems[position]);
                quantumRemaining = 0;
            }

            quantumRemaining--;
        }

        if (ready.queueSize == 0 && blocked.queueSize == 0 && filepcbs.size() == 0)
        {
            cout << "All processes have completed!" << endl;
            cout << "Check file for details!" << endl << endl;
            outFile << endl << "Total time to completion: " << counter << endl;
            turnaroundTime = 0;

            for (int i = 0; i < storeTurnaround.size(); i++)
            {
                turnaroundTime = turnaroundTime + storeTurnaround[i];
            }

            turnaroundTime = turnaroundTime / storeTurnaround.size();
            //cout << "Average turnaround time: " << turnaroundTime << endl;
            outFile << endl << "Average turnaround time: " << turnaroundTime << endl;
            outFile.close();
            done = true;
        }
    }

    return;
}


//user chooses which memory management algorithm to use
char controller::chooseFit()
{
    int userChoice;

    cout << "----------" << endl;
    cout << "1. First Fit" << endl;
    cout << "2. Next Fit" << endl;
    cout << "3. Best Fit" << endl;
    cout << "4. Worst Fit" << endl;
    cout << "----------" << endl;
    cout << "Enter the corresponding number for what you want to do: ";
    cin >> userChoice;
    cout << endl;

    switch (userChoice)
    {
    case 1:
        {
            return 'F';
        }
        break;
    case 2:
        {
            return 'N';
        }
        break;
    case 3:
        {
            return 'B';
        }
        break;
    case 4:
        {
            return 'W';
        }
        break;
    default:
        {
            return 'F';
        }
    }

    cout << endl;
}


//resets running queue for next scheduler that is used
void controller::setRunning()
{
    pcb* tempPCB = new pcb;
    tempPCB -> processName = "empty";
    tempPCB -> memory = 1024;
    running.heldItems.clear();
    running.addPCB(tempPCB);
}


controller::~controller()
{
}
