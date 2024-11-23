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
	ConcreteFile::FileLocationPair parent(reinterpret_cast<const ConcreteFile*>(toggledDir), toggledDir->getName());
	for (size_t i = 0; i < dirCnt; i++)
	{
		std::string currentPath = toggledDir->getPath() + directories[i];
		current = new Directory(parent, currentPath, directories[i]);
		toggledDir->addDir(*current);
	}
}

bool FileSystem::importFile(const std::string& targetFile, const std::string& targetDir)
{
	// TO_DO: if targetDir = "", targetDir = toggledDir 
	File* file = nullptr;

	if (File::import(targetFile, file) == false)
		return false;

	root->addFile(*file);

	return true;
}

void FileSystem::status(const std::vector<std::string>& targetFiles) const
{
	if (targetFiles.size() == 0)
		return;

	size_t count = targetFiles.size();
	for (size_t i = 0; i < count; i++)
	{

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

bool FileSystem::changeDir(const std::string& newDir)
{
	if (newDir.length() == 0)
		return true;

	std::vector<std::string> arguments;
	Utils::splitUnixFilePath(newDir, arguments);
	// absolute path logic
	if (arguments[0] == "/")
		return root->lookUpDirectory(arguments, toggledDir);

	// relative path logic	
}

void FileSystem::list(const std::string& targetDir)
{
	// list current directory if no target is specified
	if (targetDir.length() == 0)
	{
		toggledDir->list();
		return;
	}

	// try to lookup by full path
	std::vector<std::string> arguments;
	Utils::splitUnixFilePath(targetDir, arguments);
	Directory* temp = root;
	if (arguments[0] == "/")
	{
		// print current folder
		if (root->lookUpDirectory(arguments, temp) == false)
			toggledDir->list();
		
		// print temp
		else
			temp->list(); 

		return;
	}

	// try to lookup by relative path
}
