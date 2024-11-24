#pragma once
#include "CommandCreators.h"

class CommandsFactory
{
public:
	static CommandsFactory& getFactory();

	void registerCommandCreator(const CommandCreator* newCreator);
	Command* createCommand(const std::vector<std::string>& arguments);
	
private:
	const CommandCreator* getCommandCreator(const std::vector<std::string>& arguments) const;

private:
	CommandsFactory() = default;
	CommandsFactory(const CommandsFactory&) = delete;
	CommandsFactory& operator=(const CommandsFactory&) = delete;

private:
	std::vector<const CommandCreator*> commandCreators;
};

