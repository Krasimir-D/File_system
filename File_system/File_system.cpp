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
	/*std::vector<std::string> content;
	std::string lineInput = "";
	while (lineInput != ".")
	{
		std::getline(std::cin, lineInput);
		if (lineInput == ".")
			break;
		content.push_back(lineInput.c_str());
	}

	std::ofstream out("cat.txt", std::ios::binary);
	if (!out)
		std::cerr << "Could not open file for writing!\n";

	size_t contentSize = 0;
	for (size_t i = 0; i < content.size(); i++)
	{
		contentSize += content[i].length();
	}
	out.write(reinterpret_cast<const char*>(&contentSize), sizeof(contentSize));
	out.write(reinterpret_cast<const char*>(content.data()), contentSize);
	out.close();

	std::ifstream in("cat.txt", std::ios::binary);
	if (!in)
		std::cerr << "Could not open file for reading!\n";

	std::vector<uint8_t> contentRes;
	in.read(reinterpret_cast<char*>(&contentSize), sizeof(contentSize));
	contentRes.resize(contentSize);
	in.read(reinterpret_cast<char*>(contentRes.data()), contentSize);
	in.close();
	for (size_t i = 0; i < contentSize; i++)
	{
		std::cout << contentRes[i];
	}*/
}


