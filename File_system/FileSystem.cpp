#include "FileSystem.h"
#include <cassert>
#include "Utils.h"
#include <cstring>
#include <fstream>

bool FileSystem::save() const
{
	std::ofstream out(systemName+".bin", std::ios::binary);
	if (!out.is_open())
		return false;

	if (root->save(out) == false)
		return false;

	out.close();
	return true;
}

bool FileSystem::load(const std::string& filepath)
{
	if (filepath.length() == 0)
		return false;

	std::ifstream input(filepath , std::ios::binary);
	if (!input.is_open())
		return false;

	if (root->load(input) == false)
		return false;

	toggledDir = root;
	isActive = true;

	input.close();
	return true;
}

void FileSystem::makeDirectory(const std::vector<std::string>& directories)
{
	if (directories.size() == 0)
		return;

	size_t dirCnt = directories.size();
	Directory* current = nullptr;
	ConcreteFile::FileLocationPair parent(reinterpret_cast<ConcreteFile*>(toggledDir), toggledDir->getName());
	for (size_t i = 0; i < dirCnt; i++)
	{
		std::string currentPath = toggledDir->getPath() + directories[i];
		current = new Directory(parent, currentPath, directories[i]);
		toggledDir->addDir(*current);
	}
}

bool FileSystem::importFile(const std::string& targetFile, const std::string& targetDir)
{
	Directory* temp = nullptr;
	if (targetDir.length() == 0)
		temp = toggledDir;
	
	else
		changeDirectory(targetDir, temp);

	File* file = nullptr;
	if (File::import(targetFile, file, temp->getName()) == false)
		return false;

	temp->addFile(*file);

	return true;
}

void FileSystem::status(const std::vector<std::string>& targetFiles) const
{
	if (targetFiles.size() == 0)
		return;

	size_t count = targetFiles.size();
	for (size_t i = 0; i < count; i++)
	{
		// lookup files in directories and print metadata
	}
}

void FileSystem::exit()
{
	this->isActive = false;
}

FileSystem::FileSystem(const std::string& name)
	: systemName(""), root(nullptr), toggledDir(nullptr), isActive(true)
{	
	assert(name.length() != 0);
	// some error handling to do later on
	systemName = name;
	root = new Directory("/");
		
	// first try to load the file system if one exists
	if (load(name+".bin") == true)
		return;

	//  If it fails create a new file system
	toggledDir = root;
}

FileSystem::~FileSystem()
{
	save();
	delete root;
	toggledDir = nullptr;
}

void FileSystem::printWorkingDir() const
{
	std::cout << toggledDir->getPath() << std::endl;
}

bool FileSystem::changeDirectory(const std::string& newDir, Directory*& result)
{
	std::vector<std::string> arguments;
	Utils::splitUnixFilePath(newDir, arguments);
	// absolute path logic-> start from root
	if (arguments[0] == "/")
		return root->lookUpDirectory(arguments, result);

	// else start search within the current working directory
	return toggledDir->lookUpDirectory(arguments, result);
}

bool FileSystem::changeWorkingDir(const std::string& newDir)
{
	if (newDir.length() == 0)
		return true;

	return changeDirectory(newDir, toggledDir);
}

void FileSystem::list(const std::string& targetDir)
{
	// list current directory if no target is specified
	if (targetDir.length() == 0)
	{
		toggledDir->list();
		return;
	}

	Directory* temp = toggledDir;
	changeDirectory(targetDir, temp); // if it successful then temp points to the desired directory
									// if it has failed then temp is the current working directory

	temp->list();
}
