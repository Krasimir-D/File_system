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
	while (fileSystem)
	{
		std::cout << "> ";
		std::string commandLine;
		std::getline(std::cin, commandLine);
		std::vector<std::string> arguments = Utils::parseCommandLine(commandLine);
		Command* cmd = CommandsFactory::getFactory().createCommand(arguments);

	}
}

UserInterface::UserInterface()
	: isRunning(true), fileSystem("fileSystem") {}