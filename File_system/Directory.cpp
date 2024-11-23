#include "Directory.h"
#include <fstream>

Directory::Directory()
	: ConcreteFile(Type::Directory)
{
}

Directory::Directory(const FileLocationPair& parent, Type type, const std::string& fileName, const std::string& directory)
	: ConcreteFile(parent, type, fileName)
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

template<typename T>
bool Directory::saveChildFiles(const std::vector<T*>& fileContainer, std::ofstream& out) const
{
	size_t size = fileContainer.size();
	out.write(reinterpret_cast<const char*>(&size), sizeof(size)); // write the size of the vector

	for (size_t i = 0; i < size; i++) // then write the vector content
	{
		if (fileContainer[i]->save(out) == false) // if some of the save opeartions fail the whole function fails
		return false;
	}
	
	return true;
}


bool Directory::save(std::ofstream& out) const
{	
	if (ConcreteFile::save(out) == false) // the validation whether the stream is open is done in this method
		return false;

	if (saveChildFiles(directories, out) == false) // save subtrees of the node(file)
		return false;

	if (saveChildFiles(files, out) == false || saveChildFiles(symlinks, out) == false) // save leaves of the node(file)
		return false;

	return true;
}


template<typename T>
bool Directory::loadChildFiles(std::vector<T>& fileContainer, std::ifstream& input)
{
	size_t size = 0;
	input.read(reinterpret_cast<char*>(&size), sizeof(size));
	fileContainer.resize(size);
	
	for (size_t i = 0; i < size; i++)
	{
		if (fileContainer[i]->load(input) == false)
			return false;
	}

	return false;
}


bool Directory::load(std::ifstream& input)
{
	if (ConcreteFile::load(input) == false) // the validation whether the stream is open is done in this method
		return false;
		
	if (loadChildFiles(directories, input) == false)
		return false;

	if (loadChildFiles(files, input) == false || loadChildFiles(symlinks, input) == false)
		return false;

	return true;
}