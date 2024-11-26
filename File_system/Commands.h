#pragma once
#include "FileSystem.h"

class Command
{
public:
	Command(const std::string& name);
	virtual ~Command() = default;

	virtual Command* clone() const = 0;
	void operator()(FileSystem* sys = nullptr);
	const std::string& getType() const;

protected:
	const std::string name;

private:
	virtual void execute(FileSystem* sys) const = 0;
};

class Help : public Command
{
public:
	Help();
	virtual Help* clone() const override;

private:
	virtual void execute(FileSystem* sys = nullptr) const override;
private:
	static constexpr char HELP_COMMAND[] = "help";
};

// this command does not really belong here, because it does not modify the system in any way
// despite that, making a separate hierarchy for a single command would not be justified
// this command serves on purpose only - to help the user
class ClearConsole : public Command
{
public:
	ClearConsole();

	virtual ClearConsole* clone() const override;

private:
	virtual void execute(FileSystem* sys = nullptr) const override;
private:
	static constexpr char CLEAR_COMMAND[] = "clear";
};

// pwd command - lists the path to the working directory
class PrintWorkingDir : public Command
{
public:
	PrintWorkingDir(); // write some file system object logic first
	
	virtual PrintWorkingDir* clone() const override;

private:
	virtual void execute(FileSystem* sys) const;

private:
	static constexpr char PWD_COMMAND[]  = "pwd";
};

class ChangeDir : public Command
{
public:
	ChangeDir(const std::string& newDir);

	virtual ChangeDir* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::string newDir;
	static constexpr char CD_COMMAND[] = "cd";
};

class List : public Command
{
public:
	List(const std::string& targetDir);

	virtual List* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::string targerDir;
	static constexpr char LS_COMMAND[] = "ls";
};

class Concatenate : public Command
{
public:
	// one ctor covers the 3 possible cases
	Concatenate(const std::vector<std::string>& files, const std::string& destFile = "");

	virtual Concatenate* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::vector<std::string> files;
	std::string destinationFile;
	static constexpr char CAT_COMMAND[] = "cat";
};

class Copy : public Command
{
public:
	Copy(const std::vector<std::string>& files, const std::string& destDirectory);

	virtual Copy* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::vector<std::string> files;
	std::string destDirectory;
	static constexpr char CP_COMMAND[] = "cp";
};

class Remove : public Command
{
public:
	Remove(const std::vector<std::string>& targetFiles);

	virtual Remove* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::vector<std::string> targetFiles;
	static constexpr char RM_COMMAND[] = "rm";
};

class MakeDirectory : public Command
{
public:
	MakeDirectory(const std::vector<std::string>& directories);

	virtual MakeDirectory* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::vector<std::string> directories;
	static constexpr char MKDIR_COMMAND[] = "mkdir";
};



class RemoveDirectory : public Command
{
public:
	RemoveDirectory(const std::vector<std::string>& targetDirectories);

	virtual RemoveDirectory* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::vector<std::string> targetDirectories;
	static constexpr char RMDIR_COMMAND[] = "rmdir";
};

class Import : public Command
{
public:
	Import(const std::string& targetFile, const std::string& = "");

	virtual Import* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;
private:
	std::string targetFile;
	std::string destinationDir;
	static constexpr char IMPORT_COMMAND[] = "import";
};

class Status : public Command
{
public:
	Status(const std::vector<std::string>& targetFiles);

	virtual Status* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::vector<std::string> targetFiles;
	static constexpr char STAT_COMMAND[] = "stat";
};

// to do later on cause its time consuming 
class Locate : public Command
{
public:
	Locate(const std::vector<std::string>& arguments);
	virtual Locate* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::vector<std::string> arguments;
	static constexpr char LOCATE_COMMAND[] = "locate";
};

// this command prints the content of a file on the console
class PrintContent : public Command
{
public:
	PrintContent(const std::string& targetFile);
	virtual PrintContent* clone() const override;
	
private:
	virtual void execute(FileSystem* sys) const override;

private:
	std::string targetFile;
	static constexpr char PRINT_COMMAND[] = "print";
};

class Exit : public Command
{
public:
	Exit();

	virtual Exit* clone() const override;

private:
	virtual void execute(FileSystem* sys) const override;

private:
	static constexpr char EXIT_COMMAND[] = "exit";
};
