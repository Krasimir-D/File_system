#pragma once
#include "File.h"
#include "Symlink.h"
#include <vector>

class Directory : public ConcreteFile
{
public:
	Directory();
	Directory(const std::string& filename);
	Directory(const FileLocationPair& parent, const std::string& path, const std::string& name); 

	const std::vector<File*>& getFiles() const;
	const std::vector<Symlink*>& getSymlinks() const;
	const std::vector<Directory*>& getDirectories() const;
	
	static ConcreteFile* copy(const Directory& obj);

	// imports a file
	void addFile(File& newFile, const std::string& targetDir = "");
	void addDir(Directory& newDir, const std::string& targetDir = "");
	void addSym(Symlink& newSym, const std::string& targetDir = "");
	void remove(const ConcreteFile* file);
	
	// searches for a subdirectory recursively. If a match is found the result pointer is redirected to the desired directory
	// the vector is used as a stack, being traversed from right to left
	bool lookUpDirectory(std::vector<std::string>& arguments, Directory*& result);

	bool load(std::ifstream& input);
	bool save(std::ofstream& out) const;
	void list() const;

private:
	// helper for the lookUpDirectory
	bool lookUpDirHelper(std::vector<std::string>& arguments, Directory*& result);

	template<typename T>
	bool saveChildFiles(const std::vector<T*>& fileContainer, std::ofstream& out) const;

	template<typename T>
	bool loadChildFiles(std::vector<T*>& fileContainer, std::ifstream& input);

private:
	std::vector<File*> files; // leafs
	std::vector<Symlink*> symlinks; // leafs
	std::vector<Directory*> directories; // children
};

