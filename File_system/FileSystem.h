#pragma once
#include "Directory.h"

class FileSystem
{	
public:
	FileSystem(const std::string& name);
	FileSystem(const FileSystem& other);
	FileSystem& operator=(const FileSystem& other);
	FileSystem(FileSystem&& other);
	FileSystem& operator=(FileSystem&& other);
	~FileSystem();

	// commands region. They will be invoked through the UI class via command objects
	void printWorkingDir() const;
	bool changeWorkingDir(const std::string& newDir); // false if it fails to find the specified dir
	void list(const std::string& targetDir = "");
	void concatenate(const std::vector<std::string>& files, const char* destination = nullptr);
	void copy(std::vector<std::string>& files, const std::string& destDirectory);
	void remove(const std::vector<std::string>& targetFiles);
	void makeDirectory(const std::vector<std::string>& directories);
	void removeDirectory(const std::vector<std::string>& targetDirectories);
	bool importFile(const std::string& targetFile, const std::string& targetDir = "");
	void status(const std::vector<std::string>& targetFiles) const;
	void locate() const;  // TO_DO: filter logic 
	void exit();

	// serialize/ deserialize functions
	bool save() const;
	bool load(const std::string& filepath);

private:
	bool removeFile(const std::string& path);
	bool findFile(const std::string& path, File* target);
	bool findDirectory(const std::string& newDir, Directory*& result);

private:
	std::string systemName;
	Directory* root;
	Directory* toggledDir;
	bool isActive;
};

