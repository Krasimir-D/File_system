#pragma once
#include "ConcreteFile.h"

class File : public ConcreteFile
{
public:
	File(std::ifstream& input, const std::string& destDir);
	File(const File& other);
	File& operator=(const File& other);
	~File() noexcept;

	bool load(std::ifstream& input);
	bool save() const;

	const uint8_t* getContent() const;

private:
	uint8_t* content;
	const Type type = ConcreteFile::Type::File; 
};

