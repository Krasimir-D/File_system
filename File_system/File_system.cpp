// File_system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include "DateTime.h"
#include <fstream>
#include <string>
#include <vector>


enum class Type
{
	NAME, SIZE, CONTENT, CRDATE, MDATE
};

struct Filter
{
	Type type;
	union Value
	{
		std::string name;
		unsigned size;
		std::vector<uint8_t> content;
		DateTime date;
	} value;

};

int main()
{

}


