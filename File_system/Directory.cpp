#include "Directory.h"
#include <fstream>

Directory::Directory()
	:ConcreteFile(Type::Directory)
{
}

Directory::Directory(const std::string& filename)
	: ConcreteFile(Type::Directory, filename, "")
{
}

Directory::Directory(const FileLocationPair& parent, const std::string& path, const std::string& name)
	: ConcreteFile(parent, Type::Directory, path, name)
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

void Directory::addFile(File& newFile, const std::string& targetDir)
{
	newFile.setParentRamAddress(this);
	files.push_back(&newFile);
	size += newFile.getSize();
}

void Directory::addDir(Directory& newDir, const std::string& targetDir)
{
	directories.push_back(&newDir);
	size += newDir.getSize();
}

void Directory::addSym(Symlink& newSym, const std::string& targetDir)
{
	symlinks.push_back(&newSym);
	size += newSym.getSize();
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

void Directory::list() const
{
	size_t temp = files.size();
	std::cout << "FILES:" << std::endl;
	for (size_t i = 0; i < temp; i++)
	{
		std::cout << files[i]->getName() << std::endl;
	}

	temp = directories.size();
	std::cout << "DIRECTORIES:" << std::endl;
	for (size_t i = 0; i < temp; i++)
	{
		std::cout << directories[i]->getName() << std::endl;
	}

	temp = symlinks.size();
	std::cout << "SYMBOLIC LINKS:" << std::endl;
	for (size_t i = 0; i < temp; i++)
	{
		std::cout << symlinks[i]->getName() << std::endl;
	}
}



template<typename T>
bool Directory::loadChildFiles(std::vector<T*>& fileContainer, std::ifstream& input)
{
	size_t size = 0;
	input.read(reinterpret_cast<char*>(&size), sizeof(size));
	fileContainer.resize(size);

	for (size_t i = 0; i < size; i++)
	{
		fileContainer[i] = new T();
		if (fileContainer[i]->load(input) == false)
		{
			delete fileContainer[i];
			return false;
		}
		fileContainer[i]->setParentRamAddress(this);
	}

	return true;
}


bool Directory::lookUpDirHelper(std::vector<std::string>& arguments, Directory*& result) 
{	
	// if a directory is looked up by an absolute path this block will be entered due to the first predicate
	// if a directory is looked up by a relative path the block will be entered due to the second predicate
	if ( (arguments.size() == 1 && arguments.back() == this->name) || arguments.size() == 0)
	{
		result = this;
		return true;
	}

	if (arguments.back() == ".")
	{
		arguments.pop_back();
		return this->lookUpDirHelper(arguments, result);
	}
	
	if (arguments.back() == ".." && this->parent.ramAddress != nullptr)
	{
		arguments.pop_back();
		Directory* parentDir = reinterpret_cast<Directory*>(parent.ramAddress);
		return parentDir->lookUpDirHelper(arguments, result);
	}

	size_t dirCnt = directories.size();
	for (size_t i = 0; i < dirCnt; i++)
	{
		// this if covers search by absolute path
		if (this->name == arguments.back())
		{
			arguments.pop_back();
			return directories[i]->lookUpDirHelper(arguments, result);
		}

		// this case covers the search by relative path
		else if (directories[i]->name == arguments.back())
		{			
			return directories[i]->lookUpDirHelper(arguments, result);
		}
	}

	return false;
}

bool Directory::lookUpDirectory(std::vector<std::string>& arguments, Directory*& result) 
{
	std::reverse(arguments.begin(), arguments.end());
	return lookUpDirHelper(arguments, result);
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