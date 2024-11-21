#include "Directory.h"

Directory::Directory()
	: ConcreteFile(Type::Directory)
{
}

const std::vector<File*>& Directory::getFiles() const
{
	return files;
}

const std::vector<Symlink*>& Directory::getSymlinks() const
{
	return symlinks;
}

const std::vector<Directory*>& Directory::getDirectories() const
{
	return directories;
}

ConcreteFile* Directory::copy(const Directory& obj)
{
	return new Directory(obj);
}

void Directory::add(const ConcreteFile* newFile)
{
	if (newFile->getType() == Type::File)
		files.push_back(reinterpret_cast<File*>(&newFile));

	else if (newFile->getType() == Type::Directory)
		directories.push_back(reinterpret_cast<Directory*>(&newFile));

	else
		symlinks.push_back(reinterpret_cast<Symlink*>(&newFile));

	size += newFile->getSize();
}

