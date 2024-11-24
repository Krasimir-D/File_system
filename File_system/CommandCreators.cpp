#include "CommandCreators.h"
#include "CommandsFactory.h"

// ensures that creators for each command have been registered compile-time
static PrintWorkingDirCreator _1;
static ChangeDirCreator _2;
static ListCreator _3;
static ConcatenateCreator _4;
static CopyCreator _5;
static RemoveCreator _6;
static MakeDirCreator _7;
static RemoveDirCreator _8;
static ImportCreator _9;
static StatusCreator _10;
static LocateCreator _11;
static ExitCreator _12;

CommandCreator::CommandCreator(const std::string& name)
	: name(name)
{
	CommandsFactory::getFactory().registerCommandCreator(this);
}

bool CommandCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return arguments[0] == name;
}

PrintWorkingDirCreator* PrintWorkingDirCreator::clone() const
{
	return new PrintWorkingDirCreator(*this);
}

PrintWorkingDir* PrintWorkingDirCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new PrintWorkingDir();
}

ChangeDirCreator* ChangeDirCreator::clone() const
{
	return new ChangeDirCreator(*this);
}

bool ChangeDirCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && (arguments.size() == 2));
}

ChangeDir* ChangeDirCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new ChangeDir(arguments[1]);
}

ListCreator* ListCreator::clone() const
{
	return new ListCreator(*this);
}

bool ListCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && (arguments.size() < 3));
}

List* ListCreator::createCommand(const std::vector<std::string>& arguments) const
{
	std::string temp = "";
	if (arguments.size() == 2)
		temp = arguments[1];

	return new List(temp);
}

ConcatenateCreator* ConcatenateCreator::clone() const
{
	return new ConcatenateCreator(*this);
}

bool ConcatenateCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && (arguments.size() > 1));
}

Concatenate* ConcatenateCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Concatenate(std::vector<std::string>(arguments.begin() + 1, arguments.end()));
}

CopyCreator* CopyCreator::clone() const
{
	return new CopyCreator(*this);
}

bool CopyCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && (arguments.size() > 2));
}

Copy* CopyCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Copy(std::vector<std::string>(arguments.begin() + 1, arguments.end() - 1), arguments[arguments.size() - 1]);
}

MakeDirCreator* MakeDirCreator::clone() const
{
	return new MakeDirCreator(*this);
}

bool MakeDirCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && arguments.size() > 1);
}

MakeDirectory* MakeDirCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new MakeDirectory(std::vector<std::string>(arguments.begin() + 1, arguments.end()));
}

RemoveDirCreator* RemoveDirCreator::clone() const
{
	return new RemoveDirCreator(*this);
}

bool RemoveDirCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && arguments.size() > 1);
}

RemoveDirectory* RemoveDirCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new RemoveDirectory(std::vector<std::string>(arguments.begin() + 1, arguments.end()));
}

ImportCreator* ImportCreator::clone() const
{
	return new ImportCreator(*this);
}

bool ImportCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && arguments.size() == 2);
}

Import* ImportCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Import(arguments[1].c_str());
}

StatusCreator* StatusCreator::clone() const
{
	return new StatusCreator(*this);
}

bool StatusCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && arguments.size() > 1);
}

Status* StatusCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Status(std::vector<std::string>(arguments.begin() + 1, arguments.end()));
}

LocateCreator* LocateCreator::clone() const
{
	return new LocateCreator(*this);
}

bool LocateCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && (arguments.size() == 3));
}

Locate* LocateCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return nullptr;
}

ExitCreator* ExitCreator::clone() const
{
	return new ExitCreator(*this);
}

bool ExitCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return arguments[0] == name;
}

Exit* ExitCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Exit();
}

RemoveCreator* RemoveCreator::clone() const
{
	return new RemoveCreator(*this);
}

bool RemoveCreator::canHandle(const std::vector<std::string>& arguments) const
{
	return ((arguments[0] == name) && arguments.size() > 1);
}

Remove* RemoveCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Remove(std::vector<std::string>(arguments.begin() + 1, arguments.end()));
}
