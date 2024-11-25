#pragma once
#include "ConcreteFile.h"
#include <vector>

class File : public ConcreteFile
{
public:
	File();
	File(const FileLocationPair& parent, const std::string& path, const std::string& name, std::vector<uint8_t>&& content);
	File(std::ifstream& input, const std::string& destDir);

	// designed to import files external for the file system
	static bool import(const std::string& filepath, File*& file, const std::string& targetDir = "");
	void addContent(const std::vector<uint8_t>& newContent);
	void printContent() const;

	// I/O functions designed for files that have been serialized from the filesystem in the desired format 
	bool load(std::ifstream& input);
	bool save(std::ofstream& out) const;	
	static ConcreteFile* copy(const File& obj);

	const std::vector<uint8_t>& getContent() const;

private:
	std::vector<uint8_t> content;	
};

