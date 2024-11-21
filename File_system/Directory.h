#pragma once
#include "File.h"
#include "Symlink.h"
#include <vector>

class Directory : public ConcreteFile
{
public:
	Directory();

	const std::vector<File*>& getFiles() const;
	const std::vector<Symlink*>& getSymlinks() const;
	const std::vector<Directory*>& getDirectories() const;
	
	static ConcreteFile* copy(const Directory& obj);

	// imports a file
	void add(const ConcreteFile* newFile);
	void remove(const ConcreteFile* file);
	
	bool load(std::ifstream& input);
	bool save(std::ofstream& out) const;

private:
	std::vector<File*> files; // leafs
	std::vector<Symlink*> symlinks; // leafs
	std::vector<Directory*> directories; // children
};

