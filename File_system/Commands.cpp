#include "Directory.h"
#include "Commands.h"

Command::Command(const std::string& name)
	: name(name)
{
}

void Command::operator()(FileSystem* sys)
{
	execute(sys);
}

const std::string& Command::getType() const
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
	sys->printWorkingDir();
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

void ChangeDir::execute(FileSystem* sys) const
{
	sys->changeWorkingDir(newDir);
}

List::List(const std::string& targetDir)
	: Command(LS_COMMAND), targerDir(targetDir)
{
}

List* List::clone() const
{
	return new List(*this);
}

void List::execute(FileSystem* sys) const
{
	sys->list(targerDir);
}

Concatenate::Concatenate(const std::vector<std::string>& files, const char* destination)
	: Command(CAT_COMMAND), files(files), destinationFile(destination)
{
}

Concatenate* Concatenate::clone() const
{
	return new Concatenate(*this);
}

void Concatenate::execute(FileSystem* sys) const
{
	sys->concatenate(files, destinationFile.c_str());
}

Copy::Copy(std::vector<std::string>& files, const std::string& destDirectory)
	: Command(CP_COMMAND), files(files), destDirectory(destDirectory)
{
}

Copy* Copy::clone() const
{
	return new Copy(*this);
}

void Copy::execute(FileSystem* sys) const
{
	sys->copy(files, destDirectory);
}

Remove::Remove(const std::vector<std::string>& targetFiles)
	: Command(RM_COMMAND), targetFiles(targetFiles)
{
}

Remove* Remove::clone() const
{
	return new Remove(*this);
}

void Remove::execute(FileSystem* sys) const
{
	sys->remove(targetFiles);
}

MakeDirectory::MakeDirectory(const std::vector<std::string>& directories)
	: Command(MKDIR_COMMAND), directories(directories)
{
}

MakeDirectory* MakeDirectory::clone() const
{
	return new MakeDirectory(*this);
}

void MakeDirectory::execute(FileSystem* sys) const
{
	sys->makeDirectory(directories);
}

RemoveDirectory::RemoveDirectory(const std::vector<std::string>& targetDirectories)
	: Command(RMDIR_COMMAND), targetDirectories(targetDirectories)
{
}

RemoveDirectory* RemoveDirectory::clone() const
{
	return new RemoveDirectory(*this);
}

void RemoveDirectory::execute(FileSystem* sys) const
{
	sys->removeDirectory(targetDirectories);
}

Import::Import(const std::string& targetFile, const char* destinationDir)
	: Command(IMPORT_COMMAND), targetFile(targetFile), destinationDir(destinationDir)
{
}

Import* Import::clone() const
{
	return new Import(*this);
}

void Import::execute(FileSystem* sys) const
{
	sys->importFile(targetFile, destinationDir);
}

Status::Status(const std::vector<std::string>& targetFiles)
	: Command(STAT_COMMAND), targetFiles(targetFiles)
{
}

Status* Status::clone() const
{
	return new Status(*this);
}

void Status::execute(FileSystem* sys) const
{
	sys->status(targetFiles);
}

Exit::Exit()
	: Command(EXIT_COMMAND)
{
}

Exit* Exit::clone() const
{
	return new Exit(*this);
}

void Exit::execute(FileSystem* sys) const
{
	sys->exit();
}
