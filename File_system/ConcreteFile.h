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

	const char* getTypeStr() const;

	unsigned getId() const;
	unsigned getSize() const;
	DateTime getTimeOfCreation() const;
	DateTime getLastAccessed() const;
	DateTime getLastModified() const;

	void refreshLastAccessed() const;
	void refreshLastModified();

	void stat() const;

	bool load(std::ifstream& input);
	bool save(std::ofstream& out) const;
	ConcreteFile::Type getType() const;
	ConcreteFile* getParentRamAddress() const; // the pointer will not be redirected, but the parent object could be manipulated
	const std::string& getParentHardAddress() const;

	// TO_DO: decide whether parent data-member is public or encapsulated
	// not being a ptr to a constant object is the desired behaviour here
	void setParentRamAddress(ConcreteFile* parent);

public:
	~ConcreteFile() = default;
	// costructors and inner-hierarchy logic
public:
	struct FileLocationPair
	{
		FileLocationPair() = default;
		FileLocationPair(ConcreteFile* ramAdd, const std::string& hardAdd)
			: ramAddress(ramAdd), hardAddress(hardAdd) {}

		ConcreteFile* ramAddress;
		std::string hardAddress;
	};

	ConcreteFile(Type type);
	//ConcreteFile(Type type, )
	ConcreteFile(const FileLocationPair& parent, Type type, const std::string& path, const std::string& name, const std::string& directory = "");
	ConcreteFile(Type type, const std::string& fileName, const std::string& directory = "");
	ConcreteFile(const ConcreteFile& other);
	ConcreteFile& operator=(const ConcreteFile& other);
	ConcreteFile(ConcreteFile&& other) noexcept;
	ConcreteFile& operator=(ConcreteFile&& other) noexcept;


	// helper functions designed to help serialize/ deserialize the file objects 
protected:
	static void loadStrFromBinFile(std::ifstream& input, std::string& str);
	static void writeStringToBinFile(std::ofstream& out, const std::string& str);

	// Class fields region
protected:
	FileLocationPair parent;
	static unsigned ID;

	std::string path;
	std::string name;
	const Type type;

	// metadata
	unsigned size;  // not entirely sure whether each file type should have this metadata. 
	DateTime created;
	mutable DateTime lastAccessed;
	DateTime lastModified;

private:
	// is not declared as a constant but is treated as one. No one can access it and modify it
	unsigned uniqueId;

};

