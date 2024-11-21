#pragma once
#include "Directory.h"

class FileSystem
{	
public:
	FileSystem();
	FileSystem(const FileSystem& other);
	FileSystem& operator=(const FileSystem& other);
	FileSystem(FileSystem&& other);
	FileSystem& operator=(FileSystem&& other);
	~FileSystem();

	void printWorkingDir() const;
	void changeDir(const std::string& newDir);
	void list(const std::string& targetDir);
	void concatenate(const std::vector<std::string>& files, const char* destination = nullptr);
	void copy(std::vector<std::string>& files, const std::string& destDirectory);
	void remove(const std::vector<std::string>& targetFiles);
	void makeDirectory(const std::vector<std::string>& directories);
	void removeDirectory(const std::vector<std::string>& targetDirectories);
	void importFile(const std::string& targetFile, const char* destinationDir = nullptr);
	void status(const std::vector<std::string>& targetFiles) const;
	void locate() const;  // TO_DO: filter logic 
	void exit() const;

	void save(const char* path = nullptr) const;
	void load(const std::string& filepath);

private:
	// file lookup func

private:
	Directory* root;
	Directory* toggledDir;
	bool isActive;
};

