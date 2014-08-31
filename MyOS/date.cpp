#include "date.h"

date::date()//Constructor
{

}

void date::displayDate() //Outputs the current date and time
{
    char currentDate[0];
	_strdate(currentDate);
	cout << currentDate << endl;
}

date::~date()//Destructor
{

}
