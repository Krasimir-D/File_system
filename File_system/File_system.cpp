// File_system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Directory.h"
#include "FileSystem.h"
#include <fstream>
//enum class Type
//{
//	NAME, SIZE, CONTENT, CRDATE, MDATE
//};
//
//struct Filter
//{
//	Type type;
//	union Value
//	{
//		std::string name;
//		unsigned size;
//		std::vector<uint8_t> content;
//		DateTime date;
//	} value;
//
//};

int main()
{
	FileSystem sys("MySystem");
	sys.importFile("to_imp.txt");
	
}


