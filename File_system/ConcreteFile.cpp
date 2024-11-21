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


bool ConcreteFile::load(std::ifstream& input)
{
	if (!input)
		return false;

	input.read(reinterpret_cast<char*>(&uniqueId), sizeof(uniqueId));

	// reading the path
	loadStrFromBinFile(input, path);
	// reading the name
	loadStrFromBinFile(input, name);

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
	writeStringToBinFile(out, path);

	writeStringToBinFile(out, name);

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

ConcreteFile::ConcreteFile(Type type)
	: uniqueId(ID++), path(""), name(""), type(type), size(0), created(),
	lastAccessed(), lastModified()
{
}

ConcreteFile::ConcreteFile(const ConcreteFile& other)
	: uniqueId(ID++), type(other.type), created(), lastAccessed(), lastModified()
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

ConcreteFile::ConcreteFile(ConcreteFile&& other) noexcept
	: uniqueId(ID++), type(other.type), size(0), created(), lastAccessed(), lastModified()
{
	//std::swap(parent, other.parent);
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
		//std::swap(parent, other.parent);
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



