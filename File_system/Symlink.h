#pragma once
#include "ConcreteFile.h"

class Symlink : public ConcreteFile
{
public:
	Symlink();
	Symlink(const FileLocationPair& target);

	const ConcreteFile::FileLocationPair& getTarget() const;
	//bool isBroken() const;

	bool load(std::ifstream& input);
	bool save(std::ofstream& output) const;

	static ConcreteFile* copy(const Symlink& obj);

private:
	FileLocationPair target;
};

