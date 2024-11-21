#include "Commands.h"

Command::Command(const std::string& name)
	: name(name)
{
}

void Command::operator()()
{
	execute();
}

const std::string& Command::getName() const
{
	return name;
}

PrintWorkingDir::PrintWorkingDir()
	: Command(PWD_COMMAND)
{
}

PrintWorkingDir* PrintWorkingDir::clone() const
{
	return new PrintWorkingDir(*this);
}

void PrintWorkingDir::execute() const
{

}

ChangeDir::ChangeDir(const std::string& newDir)
	: Command(CD_COMMAND), newDir{}
{
	// write validation logic
}

void ChangeDir::execute() const
{
}
