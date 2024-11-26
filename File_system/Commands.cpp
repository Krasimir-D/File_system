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
	: Command(CD_COMMAND), newDir(newDir)
{
}

ChangeDir* ChangeDir::clone() const
{
	return new ChangeDir(*this);
}

void ChangeDir::execute(FileSystem* sys) const
{
	if (sys->changeWorkingDir(newDir) == false)
		std::cout << "Could not find such directory " << newDir << std::endl;
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

Concatenate::Concatenate(const std::vector<std::string>& files, const std::string& destFile)
	: Command(CAT_COMMAND), files(files), destinationFile(destFile)
{
}

Concatenate* Concatenate::clone() const
{
	return new Concatenate(*this);
}

void Concatenate::execute(FileSystem* sys) const
{
	sys->concatenate(files, destinationFile);
}

Copy::Copy(const std::vector<std::string>& files, const std::string& destDirectory)
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

Import::Import(const std::string& targetFile, const std::string& destinationDir)
	: Command(IMPORT_COMMAND), targetFile(targetFile), destinationDir(destinationDir)
{
}

Import* Import::clone() const
{
	return new Import(*this);
}

void Import::execute(FileSystem* sys) const
{
	if (sys->importFile(targetFile, destinationDir) == false)
		std::cout << "Could not import file " << targetFile << std::endl;
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

Locate::Locate()
	: Command(LOCATE_COMMAND)
{
}

Locate* Locate::clone() const
{
	return new Locate(*this);
}

void Locate::execute(FileSystem* sys) const
{

}

ClearConsole::ClearConsole()
	: Command(CLEAR_COMMAND)
{
}

ClearConsole* ClearConsole::clone() const
{
	return new ClearConsole(*this);
}

void ClearConsole::execute(FileSystem* sys) const
{
	system("cls");
}

PrintContent::PrintContent(const std::string& targetFile)
	: Command(PRINT_COMMAND), targetFile(targetFile)
{
}

PrintContent* PrintContent::clone() const
{
	return new PrintContent(*this);
}

void PrintContent::execute(FileSystem* sys) const
{
	sys->printFileContent(targetFile);
}
