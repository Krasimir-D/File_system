// File_system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Directory.h"
#include "FileSystem.h"
#include <fstream>
#include "Utils.h"
#include "UserInterface.h"
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
	// scenario 
	//FileSystem sys("MySystem");	
	//sys.printWorkingDir();
	//sys.list();
	//sys.importFile("to_imp.txt");
	//std::vector<std::string> dirs;
	//dirs.push_back("Dir1");
	//sys.makeDirectory(dirs);
	//sys.importFile("deep.txt");
	//sys.changeWorkingDir("..");
	//sys.list();
	//sys.changeWorkingDir("Dir1");
	//sys.list();	
	
	// AS FAR AS I KNOW EVERY COMMAND SHOULD WORK EXCEPT FOR "cat" and "locate"
	// IT WILL BE READY NEXT WEEK + ANY POSSIBLE ERROR SHOULD BE FIXED

	UserInterface::getInstance().run();
}


