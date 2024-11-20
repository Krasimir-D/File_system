#pragma once
#include "DateTime.h"

// abstract base class
class ConcreteFile
{
public:
	enum class Type
	{
		File,
		Directory,
		Symlink
	};

public:
	const std::string& getPath() const;
	const std::string& getName() const;

	//const ConcreteFile::Type getType() const;

	DateTime getTimeOfCreation() const;
	DateTime getLastAccessed() const;
	DateTime getLastModified() const;

	bool load(std::ifstream& input);
	bool save(std::ofstream& out) const;

protected:
	ConcreteFile();
	/*ConcreteFile(const std::string& filename);
	ConcreteFile(const std::string& fileName, const std::string& directory);*/
	ConcreteFile(const ConcreteFile& other);
	ConcreteFile& operator=(const ConcreteFile& other);

	unsigned getId() const;
	

protected:
	static unsigned ID;


	std::string path;
	std::string name;
	
	// metadata
	unsigned size;
	DateTime created;
	DateTime lastAccessed;
	DateTime lastModified;

private:
	// is not declared as a constant but is treated as one. No one can access it and modify it
	unsigned uniqueId;
};

