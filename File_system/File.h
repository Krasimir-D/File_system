#pragma once
#include "DateTime.h"

// abstract base class
template<typename T>
class File
{
public:
	File();
	File(const std::string);
	File(const std::string& fileName, const std::string& directory);
	File(const File& other);
	File& operator=(const File& other);
	File(File&& other) noexcept;
	File& operator=(File&& other) noexcept;
	virtual ~File() = 0;

	virtual File* clone() const = 0;

	virtual void save(std::ofstream& out) const = 0;
	void load(std::ifstream& in);

	const std::string& getPath() const;
	const std::string& getName() const;
	const std::string& getType() const;

	DateTime getLastAccessed() const;
	DateTime getLastModified() const;

protected:
	struct Metadata
	{
		unsigned size;
		std::string type;
		DateTime lastAccessed;
		DateTime lastModified;
	};

protected:
	const unsigned uniqueId;

	std::string path;
	std::string name;
	
	Metadata metadata;
};

