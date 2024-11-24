#include "CommandsFactory.h"

CommandsFactory& CommandsFactory::getFactory()
{
	static CommandsFactory theFactory;
	return theFactory;
}

void CommandsFactory::registerCommandCreator(const CommandCreator* newCreator)
{
	commandCreators.push_back(newCreator);
}

Command* CommandsFactory::createCommand(const std::vector<std::string>& arguments)
{
	const CommandCreator* creator = getCommandCreator(arguments);
	if (creator == nullptr)
		return nullptr;

	return creator->createCommand(arguments);
}

const CommandCreator* CommandsFactory::getCommandCreator(const std::vector<std::string>& arguments) const
{
	size_t creatorsCount = commandCreators.size();
	for (size_t i = 0; i < creatorsCount; i++)
	{
		if (commandCreators[i]->canHandle(arguments))
			return commandCreators[i];
	}

	return nullptr;
}
