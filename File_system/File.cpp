#include "File.h"
#include <fstream>

File::File(std::ifstream& input, const std::string& destDir)
	: ConcreteFile(Type::File), content(nullptr)
{
	if (!input.is_open())
		throw std::runtime_error("Unable to load file");

	load(input);
	this->path = destDir;
}

File::File(const File& other)
	: ConcreteFile(other)
{
	content = new uint8_t[other.contentSize];
	for (size_t i = 0; i < other.contentSize; i++)
	{
		content[i] = other.content[i];
	}
	contentSize = other.contentSize;
}

File& File::operator=(const File& other)
{
	if (this != &other)
	{
		uint8_t* tempContent = nullptr;
		try
		{
			tempContent = new uint8_t[other.contentSize];
			for (size_t i = 0; i < other.contentSize; i++)
			{
				tempContent[i] = other.content[i];
			}
			ConcreteFile::operator=(other);
			delete[] content;
			content = tempContent;
			contentSize = other.contentSize;
		}
		catch (const std::bad_alloc&)
		{
			delete[] tempContent;
			throw;
		}
	}
}

File::~File() noexcept
{
	delete[] content;
}

bool File::load(std::ifstream& input)
{
	// copy the metadata
	if (!ConcreteFile::load(input))
		return false;
	
	input.read(reinterpret_cast<char*>(&contentSize), sizeof(contentSize));
	content = new uint8_t[contentSize];
	input.read(reinterpret_cast<char*>(content), contentSize);

	return true;
}

bool File::save(std::ofstream& out) const
{
	// save the metadata
	if (!ConcreteFile::save(out))
		return false;

	out.write(reinterpret_cast<const char*>(&contentSize), sizeof(contentSize));
	out.write(reinterpret_cast<const char*>(content), sizeof(content));
}

ConcreteFile* File::copy(const File& obj) 
{
	return new File(obj);
}

const uint8_t* File::getContent() const
{
	return content;
}


