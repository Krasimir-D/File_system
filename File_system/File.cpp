#include "File.h"
#include <fstream>

File::File(std::ifstream& input, const std::string& destDir)
	: ConcreteFile(), content(nullptr)
{
	if (!input.is_open())
		throw std::runtime_error("Unable to load file");

	load(input);
	this->path = destDir;
}

File::File(const File& other)
	: ConcreteFile(other)
{
	content = new uint8_t[size];
	for (size_t i = 0; i < size; i++)
	{
		content[i] = other.content[i];
	}
}

File& File::operator=(const File& other)
{
	if (this != &other)
	{
		uint8_t* tempContent = nullptr;
		try
		{
			tempContent = new uint8_t[other.size];
			for (size_t i = 0; i < other.size; i++)
			{
				tempContent[i] = other.content[i];
			}
			ConcreteFile::operator=(other);
			delete[] content;
			content = tempContent;
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
	input.seekg(0, std::ios::end);
	unsigned tempSize = input.tellg();
	input.seekg(0, std::ios::beg);

	content = new uint8_t[tempSize];
	input.read(reinterpret_cast<char*>(content), tempSize);
	this->size = tempSize;

	return true;
}

bool File::save() const
{
	std::ofstream out(path, std::ios::binary);
	if (!out.is_open())
		throw std::runtime_error("Unable to open file for writing!");

	
}

const uint8_t* File::getContent() const
{
	return content;
}


