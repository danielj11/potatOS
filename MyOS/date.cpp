#include "date.h"

date::date()//Constructor
{

}

void date::displayDate() //Outputs the current date and time
{
    char currentDate[0];
	_strdate(currentDate);
	cout << "Today's date is " << currentDate << "." << endl << endl;;
}

date::~date()//Destructor
{

}
