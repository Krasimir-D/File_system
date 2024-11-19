// File_system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include "DateTime.h"

int main()
{
	Date d;
	Time t;
	DateTime dt(d, t);

	std::string str;
	dt.toString(str);
	std::cout << str;
}

