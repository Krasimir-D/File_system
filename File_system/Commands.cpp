#include "Commands.h"

Command::Command(const std::string& name)
	: name(name)
{
}

void Command::operator()(FileSystem* sys)
{
	execute(sys);
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

void PrintWorkingDir::execute(FileSystem* sys) const
{

}

ChangeDir::ChangeDir(const std::string& newDir)
	: Command(CD_COMMAND), newDir{}
{
	// write validation logic
}

ChangeDir* ChangeDir::clone() const
{
	return new ChangeDir(*this);
}

#include "Directory.h"
void ChangeDir::execute(FileSystem* sys) const
{
}

List* List::clone() const
{
	return new List(*this);
}

void List::execute(FileSystem* sys) const
{
}

Concatenate* Concatenate::clone() const
{
	return new Concatenate(*this);
}

void Concatenate::execute(FileSystem* sys) const
{
}

Copy* Copy::clone() const
{
	return new Copy(*this);
}

void Copy::execute(FileSystem* sys) const
{
}

Remove* Remove::clone() const
{
	return new Remove(*this);
}

void Remove::execute(FileSystem* sys) const
{
}

MakeDirectory* MakeDirectory::clone() const
{
	return new MakeDirectory(*this);
}

void MakeDirectory::execute(FileSystem* sys) const
{
}

RemoveDirectory* RemoveDirectory::clone() const
{
	return new RemoveDirectory(*this);
}

void RemoveDirectory::execute(FileSystem* sys) const
{
}

Import* Import::clone() const
{
	return new Import(*this);
}

void Import::execute(FileSystem* sys) const
{
}

Status* Status::clone() const
{
	return new Status(*this);
}

void Status::execute(FileSystem* sys) const
{
}

Exit* Exit::clone() const
{
	return new Exit(*this);
}

void Exit::execute(FileSystem* sys) const
{
}
