#include "UserInterface.h"
#include "CommandsFactory.h"
#include "Utils.h"
#include <iostream>
#include <string>

UserInterface& UserInterface::getInstance()
{
	static UserInterface instance;
	return instance;
}

void UserInterface::run()
{
	// try-catch for salting unexpected exceptions
	try
	{
		while (fileSystem)
		{
			std::cout << "> ";
			std::string commandLine;
			std::getline(std::cin, commandLine);
			std::vector<std::string> arguments = Utils::parseCommandLine(commandLine);
			Command* cmd = CommandsFactory::getFactory().createCommand(arguments);
			if (!cmd)
			{
				std::cout << "Command not recognized!" << std::endl;
				continue;
			}
			(*cmd)(&fileSystem);
			std::cout << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

UserInterface::UserInterface()
	: isRunning(true), fileSystem("fileSystem") {}