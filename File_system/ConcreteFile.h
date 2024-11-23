#pragma once
#include "DateTime.h"

// abstract base class
class ConcreteFile
{
public:
	enum class Type
	{
		ConcreteFile,
		File,
		Directory,
		Symlink
	};

public:
	const std::string& getPath() const;
	const std::string& getName() const;

	unsigned getSize() const;
	DateTime getTimeOfCreation() const;
	DateTime getLastAccessed() const;
	DateTime getLastModified() const;

	bool load(std::ifstream& input);
	bool save(std::ofstream& out) const;
	ConcreteFile::Type getType() const;

public:
	~ConcreteFile() = default;
// costructors and inner-hierarchy logic
protected:
	struct FileLocationPair
	{
		ConcreteFile* ramAddress;
		std::string hardAddress;
	};

	ConcreteFile(Type type);
	//ConcreteFile(Type type, )
	ConcreteFile(const FileLocationPair& parent, Type type, const std::string& fileName, const std::string& directory = "");
	ConcreteFile(const ConcreteFile& other);
	ConcreteFile& operator=(const ConcreteFile& other);
	ConcreteFile(ConcreteFile&& other) noexcept;
	ConcreteFile& operator=(ConcreteFile&& other) noexcept;

	unsigned getId() const;

// helper functions designed to help serialize/ deserialize the file objects 
protected:
	static void loadStrFromBinFile(std::ifstream& input, std::string& str);
	static void writeStringToBinFile(std::ofstream& out, const std::string& str);
	
// Class fields region
protected:
	static unsigned ID;
	FileLocationPair parent;

	std::string path;
	std::string name;
	const Type type;
	
	// metadata
	unsigned size;  // not entirely sure whether each file type should have this metadata. 
	DateTime created;
	DateTime lastAccessed;
	DateTime lastModified;

private:
	// is not declared as a constant but is treated as one. No one can access it and modify it
	unsigned uniqueId;

};

