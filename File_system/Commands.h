#pragma once
#include "Directory.h"

class Command
{
public:
	Command(const std::string& name);
	virtual ~Command() = default;

	virtual Command* clone() const = 0;
	void operator()();
	const std::string& getName() const;

protected:
	const std::string name;

private:
	virtual void execute() const = 0;
};

// pwd command - lists the path to the working directory
class PrintWorkingDir : public Command
{
public:
	PrintWorkingDir(); // write some file system object logic first
	
	virtual PrintWorkingDir* clone() const override;

private:
	virtual void execute() const;

private:
	static constexpr char PWD_COMMAND[]  = "pwd";
};

class ChangeDir : public Command
{
public:
	ChangeDir(const std::string& newDir);

	virtual ChangeDir* clone() const override;

private:
	virtual void execute() const override;

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
	virtual void execute() const override;

private:
	std::string targerDir;
	static constexpr char LS_COMMAND[] = "ls";
};

class Concatenate : public Command
{
public:
	Concatenate(const std::vector<std::string>& files, const char* destination = nullptr);
	Concatenate(const std::vector<std::string>& files);
	Concatenate(const std::string& singleFile);

	virtual Concatenate* clone() const override;

private:
	virtual void execute() const override;

private:
	std::vector<std::string> files;
	std::string destinationFile;
	static constexpr char CAT_COMMAND[] = "cat";
};

class Copy : public Command
{
public:
	Copy(std::vector<std::string>& files, const std::string& destDirectory);

	virtual Copy* clone() const override;

private:
	virtual void execute() const override;

private:
	std::vector<std::string>& files;
	std::string& destDirectory;
	static constexpr char CP_COMMAND[] = "cp";
};

class Remove : public Command
{
public:
	Remove(const std::vector<std::string>& targetFiles);

	virtual Remove* clone() const override;

private:
	virtual void execute() const override;

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
	virtual void execute() const override;

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
	virtual void execute() const override;

private:
	std::vector<std::string> targetDirectories;
	static constexpr char RMDIR_COMMAND[] = "rmdir";
};

class Import : public Command
{
public:
	Import(const std::string& targetFile, const char* destinationDir = nullptr);

	virtual Import* clone() const override;

private:
	virtual void execute() const override;
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
	virtual void execute() const override;

private:
	std::vector<std::string> targetFiles;
	static constexpr char STAT_COMMAND[] = "stat";
};

// to do later on cause its time consuming 
class Locate : public Command
{

private:

	static constexpr char LOCATE_COMMAND[] = "locate";
};

class Exit : public Command
{
public:
	Exit();

	virtual Exit* clone() const override;

private:
	virtual void execute() const override;

private:
	static constexpr char EXIT_COMMAND[] = "exit";
};
