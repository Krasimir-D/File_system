#pragma once
#include "DateTime.h"

class File
{
public:
	File();
	File(const File& other);
	File& operator=(const File& other);
	File(File&& other) noexcept;
	File& operator=(File&& other) noexcept;
	virtual ~File() = 0;

private:
	static unsigned uniqueId;

	std::string filename;
	unsigned size;
	std::string type;
	DateTime lastAccessed;
	DateTime lastModified;
};

