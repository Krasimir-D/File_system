#pragma once
#include "Commands.h"

// some sort of validation of the input will be handled in an UI class, where the input string will be modified to be in low case to ensure case insensitivity
class CommandCreator
{
public:
	// defines the type of the command that will be created, based on the input from the console
	CommandCreator(const std::string& name); 
	virtual ~CommandCreator() = default;
	virtual CommandCreator* clone() const = 0;

	// checks whether the factory can handle creating the command on the console line
	virtual bool canHandle(const std::vector<std::string>& arguments) const;
	virtual Command* createCommand(const std::vector<std::string>& arguments) const = 0;

protected:
	const std::string name;
};


// this command does not really belong here but a single command does not justify making a class hierarchy of it's own
class ClearConsoleCreator : public CommandCreator
{
public:
	ClearConsoleCreator() : CommandCreator("clear") {}
	virtual ClearConsoleCreator* clone() const override;

	virtual ClearConsole* createCommand(const std::vector<std::string>& arguments) const override;
};

// this command does not really belong here but a single command does not justify making a class hierarchy of it's own
class HelpCreator : public CommandCreator
{
public:
	HelpCreator() : CommandCreator("help") {}
	virtual  HelpCreator* clone() const override;
	virtual Help* createCommand(const std::vector<std::string>& arguments) const override;
};


class PrintWorkingDirCreator : public CommandCreator
{
public:
	PrintWorkingDirCreator() : CommandCreator("pwd") {}
	virtual PrintWorkingDirCreator* clone() const override;
	
	virtual PrintWorkingDir* createCommand(const std::vector<std::string>& arguments) const override;
};

class ChangeDirCreator : public CommandCreator
{
public:
	ChangeDirCreator() : CommandCreator("cd") {}
	virtual ChangeDirCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual ChangeDir* createCommand(const std::vector<std::string>& arguments) const override;
};

class ListCreator : public CommandCreator
{
public:
	ListCreator() : CommandCreator("ls") {}
	virtual ListCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual List* createCommand(const std::vector<std::string>& arguments) const override;
};

class ConcatenateCreator : public CommandCreator
{
public:
	ConcatenateCreator() : CommandCreator("cat") {}
	virtual ConcatenateCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual Concatenate* createCommand(const std::vector<std::string>& arguments) const override;
};

class CopyCreator : public CommandCreator
{
public:
	CopyCreator() : CommandCreator("cp") {}
	virtual CopyCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual Copy* createCommand(const std::vector<std::string>& arguments) const override;
};

class RemoveCreator : public CommandCreator
{
public:
	RemoveCreator() : CommandCreator("rm") {}
	virtual RemoveCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual Remove* createCommand(const std::vector<std::string>& arguments) const override;
};

class MakeDirCreator : public CommandCreator
{
public:
	MakeDirCreator() : CommandCreator("mkdir") {}
	virtual MakeDirCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual MakeDirectory* createCommand(const std::vector<std::string>& arguments) const override;
};

class RemoveDirCreator : public CommandCreator
{
public:
	RemoveDirCreator() : CommandCreator("rmdir") {}
	virtual RemoveDirCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual RemoveDirectory* createCommand(const std::vector<std::string>& arguments) const override;
};

class ImportCreator : public CommandCreator
{
public:
	ImportCreator() : CommandCreator("import") {}
	virtual ImportCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual Import* createCommand(const std::vector<std::string>& arguments) const override;
};

class StatusCreator : public CommandCreator
{
public:
	StatusCreator() : CommandCreator("stat") {}
	virtual StatusCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual Status* createCommand(const std::vector<std::string>& arguments) const override;
};

class LocateCreator : public CommandCreator
{
public:
	LocateCreator() : CommandCreator("locate") {}
	virtual LocateCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual Locate* createCommand(const std::vector<std::string>& arguments) const override;
};

class PrintCreator : public CommandCreator
{
public:
	PrintCreator() : CommandCreator("print") {}
	virtual PrintCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual PrintContent* createCommand(const std::vector<std::string>& arguments) const override;
};

class ExitCreator : public CommandCreator
{
public:
	ExitCreator() : CommandCreator("exit") {}
	virtual ExitCreator* clone() const override;

	virtual bool canHandle(const std::vector<std::string>& arguments) const override;
	virtual Exit* createCommand(const std::vector<std::string>& arguments) const override;
};