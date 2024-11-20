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

bool ConcreteFile::load(std::ifstream& input)
{
	if (!input)
		return false;

	input.read(reinterpret_cast<char*>(&uniqueId), sizeof(uniqueId));
	
	// reading the path
	size_t tempLen = 0;
	input.read(reinterpret_cast<char*>(&tempLen), sizeof(tempLen));
	path.resize(tempLen, '\0');
	input.read(&path[0], tempLen);

	// reading the name
	input.read(reinterpret_cast<char*>(&tempLen), sizeof(tempLen));
	name.resize(tempLen, '\0');
	input.read(&name[0], tempLen);

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

	out.write(reinterpret_cast<const char*>(uniqueId), sizeof(uniqueId));
	size_t tempLen = path.length();
	out.write(reinterpret_cast<const char*>(&tempLen), sizeof(tempLen));
	out.write(path.data(), tempLen);
		
	tempLen = name.length();
	out.write(reinterpret_cast<const char*>(&tempLen), sizeof(tempLen));
	out.write(name.data(), tempLen);

	out.write(reinterpret_cast<const char*>(&size), sizeof(size));

	out.write(reinterpret_cast<const char*>(&created), sizeof(created));
	out.write(reinterpret_cast<const char*>(&lastAccessed), sizeof(lastAccessed));
	out.write(reinterpret_cast<const char*>(&lastModified), sizeof(lastModified));

	return true;
}

ConcreteFile::ConcreteFile()
	: uniqueId(ID++), path(""), name(""), size(0), created(),
		lastAccessed(), lastModified()
{
}

ConcreteFile::ConcreteFile(const ConcreteFile& other)
	: uniqueId(ID++), created(), lastAccessed(), lastModified()
{	
	this->path = other.path;
	this->name = other.name;
	this->size = other.size;	
}

ConcreteFile& ConcreteFile::operator=(const ConcreteFile& other)
{
	if (this != &other)
	{
		this->path = other.path;
		this->name = other.name;
		this->size = other.size;
		this->created = other.created;
		this->lastAccessed = other.lastAccessed;
		this->lastModified = other.lastModified;
	}

	return *this;
}

unsigned ConcreteFile::getId() const
{
	return uniqueId;
}



