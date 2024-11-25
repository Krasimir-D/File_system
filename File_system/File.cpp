#include "File.h"
#include "Utils.h"
#include <fstream>

File::File()
	: ConcreteFile(Type::File)
{
}

File::File(const FileLocationPair& parent, const std::string& path, const std::string& name, std::vector<uint8_t>&& content)
	: ConcreteFile(parent, Type::File, path, name)
{
	this->size = content.size();
	this->content = std::vector<uint8_t>(std::move(content));
}

File::File(std::ifstream& input, const std::string& destDir)
	: ConcreteFile(Type::File), content()
{
	if (!input.is_open())
		throw std::runtime_error("Unable to load file");

	load(input);
	this->path = destDir;
}

bool File::import(const std::string & filepath, File*& file, const std::string& targetDir)
{
	if (filepath.length() == 0)
		return false;

	std::ifstream input(filepath, std::ios::binary | std::ios::ate);
	if (!input.is_open())
		return false;

	unsigned size = input.tellg();
	input.seekg(0, std::ios::beg);
	// the input filepath but split into substring by '\' in order to extract the file name

	
	file = new File;
	Utils::extractFileName(filepath, file->name);
	file->path = targetDir + file->name;
	// fix the way parent is being set
	file->parent.hardAddress = targetDir;
	file->size = size;

	file->content.resize(size);
	input.read(reinterpret_cast<char*>(file->content.data()), size);

	input.close();
	return true;
}

void File::addContent(const std::vector<uint8_t>& newContent)
{
	size_t newContSize = newContent.size();
	for (size_t i = 0; i < newContSize; i++)
	{
		content.push_back(newContent[i]);
	}
	this->size += newContent.size();
}

void File::printContent() const
{
	size_t size = content.size();
	for (size_t i = 0; i < size; i++)
	{
		std::cout << content[i] << " ";
	}
}

bool File::load(std::ifstream& input)
{
	// copy the metadata
	if (ConcreteFile::load(input) == false)
		return false;
	
	
	size_t contentSize = 0;
	input.read(reinterpret_cast<char*>(&contentSize), sizeof(contentSize));
	content.resize(contentSize);
	input.read(reinterpret_cast<char*>(content.data()), contentSize);

	return true;
}

bool File::save(std::ofstream& out) const
{
	// save the metadata
	if (!ConcreteFile::save(out))
		return false;

	size_t contentSize = content.size();
	out.write(reinterpret_cast<const char*>(&contentSize), sizeof(contentSize));
	out.write(reinterpret_cast<const char*>(content.data()), contentSize);

	return true;
}

ConcreteFile* File::copy(const File& obj) 
{
	return new File(obj);
}

const std::vector<uint8_t>& File::getContent() const
{
	return content;
}


