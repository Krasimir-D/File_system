#include "ConcreteFile.h"
#include <fstream>



unsigned ConcreteFile::ID = 0;

const std::string& ConcreteFile::getPath() const
{
	return path;
}

const std::string& ConcreteFile::getName() const
{
	return name;
}

const char* ConcreteFile::getTypeStr() const
{
	switch (type)
	{
	case ConcreteFile::Type::File:
		return "File";

	case ConcreteFile::Type::Directory:
		return "Directory";

	case ConcreteFile::Type::Symlink:
		return "Symlink";
	}
}

unsigned ConcreteFile::getSize() const
{
	return size;
}

DateTime ConcreteFile::getTimeOfCreation() const
{
	return created;
}

DateTime ConcreteFile::getLastAccessed() const
{
	return lastAccessed;
}

DateTime ConcreteFile::getLastModified() const
{
	return lastModified;
}

void ConcreteFile::refreshLastAccessed() const
{
	lastAccessed = DateTime();
}

void ConcreteFile::refreshLastModified()
{
	lastModified = DateTime();
	lastAccessed = DateTime();
}

void ConcreteFile::stat() const
{
	refreshLastAccessed();
	std::cout << "Id: " << uniqueId << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Path: " << path << std::endl;
	std::cout << "Parent: " << parent.hardAddress << std::endl;
	std::cout << "Type: " << getTypeStr() << std::endl;
	std::cout << "Size: " << size << std::endl;
	std::cout << "Created: " << created.toString() << std::endl;
	std::cout << "Last acessed: " << lastAccessed.toString() << std::endl;
	std::cout << "Last modified: " << lastModified.toString() << std::endl;
}


bool ConcreteFile::load(std::ifstream& input)
{
	if (!input)
		return false;

	input.read(reinterpret_cast<char*>(&uniqueId), sizeof(uniqueId));
	ID = uniqueId;

	loadStrFromBinFile(input, parent.hardAddress); // reading the path to the parent file
	loadStrFromBinFile(input, path); // reading the path	
	loadStrFromBinFile(input, name); // reading the name

	input.read(reinterpret_cast<char*>(&size), sizeof(size));

	input.read(reinterpret_cast<char*>(&created), sizeof(created));
	input.read(reinterpret_cast<char*>(&lastAccessed), sizeof(lastAccessed));
	input.read(reinterpret_cast<char*>(&lastModified), sizeof(lastModified));

	return true;
}


bool ConcreteFile::save(std::ofstream& out) const
{
	if (!out)
		return false;

	out.write(reinterpret_cast<const char*>(&uniqueId), sizeof(uniqueId));

	writeStringToBinFile(out, parent.hardAddress); // writing path to the parent file
	writeStringToBinFile(out, path); // writing the path to the current file
	writeStringToBinFile(out, name); // writing the name of the current file

	out.write(reinterpret_cast<const char*>(&size), sizeof(size));

	out.write(reinterpret_cast<const char*>(&created), sizeof(created));
	out.write(reinterpret_cast<const char*>(&lastAccessed), sizeof(lastAccessed));
	out.write(reinterpret_cast<const char*>(&lastModified), sizeof(lastModified));

	return true;
}

ConcreteFile::Type ConcreteFile::getType() const
{
	return type;
}

ConcreteFile* ConcreteFile::getParentRamAddress() const
{
	return parent.ramAddress;
}

const std::string& ConcreteFile::getParentHardAddress() const
{
	return parent.hardAddress;
}

void ConcreteFile::setParentRamAddress(ConcreteFile* parent)
{
	if (parent == nullptr)
		return;

	this->parent.ramAddress = parent;
}

ConcreteFile::ConcreteFile(Type type)
	: uniqueId(ID++), parent(), path(""), name(""), type(type), size(0), created(),
	lastAccessed(), lastModified()
{
}



ConcreteFile::ConcreteFile(const FileLocationPair& parent, Type type, const std::string& path, const std::string& name, const std::string& directory)
	: uniqueId(ID++), parent(parent), path(path), name(name), type(type), size(), created(), lastAccessed(), lastModified() 
{
	if (path[path.length() - 1] != '/')
		this->path += "/";
}

ConcreteFile::ConcreteFile(Type type, const std::string& fileName, const std::string& directory)
	: uniqueId(ID++), type(type), size(0), created(), lastAccessed(), lastModified()
{
	this->parent.hardAddress = directory;
	name = fileName;
	path = directory + name;
}

ConcreteFile::ConcreteFile(const ConcreteFile& other)
	: uniqueId(ID++), type(other.type), created(), lastAccessed(), lastModified()
{
	this->parent = other.parent; // shallow copy of the address in memory is a desired implementation here
	this->path = other.path;
	this->name = other.name;
	this->size = other.size;
}

ConcreteFile& ConcreteFile::operator=(const ConcreteFile& other)
{
	if (this != &other)
	{
		this->parent = other.parent;
		this->path = other.path;
		this->name = other.name;
		this->size = other.size;
		this->created = other.created;
		this->lastAccessed = other.lastAccessed;
		this->lastModified = other.lastModified;
	}

	return *this;
}

ConcreteFile::ConcreteFile(ConcreteFile&& other) noexcept
	: uniqueId(ID++), type(other.type), size(0), created(), lastAccessed(), lastModified()
{
	std::swap(parent, other.parent);
	std::swap(path, other.path);
	std::swap(name, other.name);
	std::swap(size, other.size);
	std::swap(created, other.created);
	std::swap(lastAccessed, other.lastAccessed);
	std::swap(lastModified, other.lastModified);
}

ConcreteFile& ConcreteFile::operator=(ConcreteFile&& other) noexcept
{
	if (this != &other)
	{
		std::swap(parent, other.parent);
		std::swap(path, other.path);
		std::swap(name, other.name);
		std::swap(size, other.size);
		std::swap(created, other.created);
		std::swap(lastAccessed, other.lastAccessed);
		std::swap(lastModified, other.lastModified);
	}

	return *this;
}

unsigned ConcreteFile::getId() const
{
	return uniqueId;
}

void ConcreteFile::loadStrFromBinFile(std::ifstream& input, std::string& str)
{
	size_t length = 0;
	input.read(reinterpret_cast<char*>(&length), sizeof(length));
	str.resize(length, '\0');
	input.read(&str[0], length);
}

void ConcreteFile::writeStringToBinFile(std::ofstream& out, const std::string& str)
{
	size_t tempLen = str.length();
	out.write(reinterpret_cast<const char*>(&tempLen), sizeof(tempLen));
	out.write(str.data(), tempLen);
}



