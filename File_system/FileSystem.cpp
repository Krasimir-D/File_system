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
	root->refreshLastAccessed();
	isActive = true;

	input.close();
	return true;
}

void FileSystem::copy(const std::vector<std::string>& files, const std::string& destDirectory)
{
	Directory* targetDir = nullptr;
	if (findDirectory(destDirectory, targetDir) == false)
	{
		std::cout << "Could not find directory " << destDirectory << std::endl;
		return;
	}

	size_t filesCount = files.size();
	File* tempShallow = nullptr;
	File* tempDeep = nullptr;
	for (size_t i = 0; i < filesCount; i++)
	{
		if (findFile(files[i], tempShallow) == false) // this function retrieves a pointer to the original file
		{
			std::cout << "File " << files[i] << " not found" << std::endl;
			continue;
		}
		tempDeep = reinterpret_cast<File*>(File::copy(*tempShallow)); // making a deep copy of the object
		targetDir->addFile(*tempDeep);
	}
}

void FileSystem::remove(const std::vector<std::string>& targetFiles)
{
	size_t filesCount = targetFiles.size();
	for (size_t i = 0; i < filesCount; i++)
	{
		if (removeFile(targetFiles[i]) == false)
			std::cout << "Could not find and remove file: " << targetFiles[i] << std::endl;
	}
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

void FileSystem::removeDirectory(const std::vector<std::string>& targetDirectories)
{
	size_t targetsCount = targetDirectories.size();
	for (size_t i = 0; i < targetsCount; i++)
	{
		Directory* temp = nullptr;
		if (findDirectory(targetDirectories[i], temp) == false)
		{
			std::cout << "Such directory does not exist!: " << targetDirectories[i] << std::endl;
			continue;
		}

		if (temp == root)
		{
			std::cout << "The root of the file system will not be removed!" << std::endl;
			continue;
		}

		if (!temp->isEmpty())
		{
			std::cout << "Directory is not empty, therefore it will not be removed!: " << targetDirectories[i] << std::endl;
			continue;
		}		

		Directory* tempParent = reinterpret_cast<Directory*>(temp->getParentRamAddress());

		if (temp == toggledDir)
			toggledDir = root; // the default behaviour I desire

		tempParent->removeDir(temp);		
	}
}

bool FileSystem::importFile(const std::string& targetFile, const std::string& targetDir)
{
	Directory* temp = nullptr;
	if (targetDir.length() == 0)
		temp = toggledDir;
	
	else
		findDirectory(targetDir, temp);

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
	File* target = nullptr;
	for (size_t i = 0; i < count; i++)
	{
		if (findFile(targetFiles[i], target) == false)
		{
			std::cout << "File " << targetFiles[i] << " not found" << std::endl;
			continue;
		}
		target->stat();
		std::cout << std::endl;
	}
}

void FileSystem::printFileContent(const std::string& targetFile) const
{
	File* temp = nullptr;
	if (findFile(targetFile, temp) == false)
	{
		std::cout << "File " << targetFile << " could not be found!" << std::endl;
		return;
	}

	temp->printContent();
	std::cout << std::endl;
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

FileSystem::operator bool() const
{
	return isActive;
}

void FileSystem::printWorkingDir() const
{
	std::cout << "Working Directory: " << toggledDir->getPath() << std::endl;
	toggledDir->refreshLastAccessed();
}

bool FileSystem::removeFile(const std::string& path)
{
	std::vector<std::string> arguments;
	std::string targetName, targetDir;
	Utils::splitDirAndName(path, targetDir, targetName);
	Directory* temp = nullptr;
	if (findDirectory(targetDir, temp) == false)
		return false;

	return temp->removeFile(targetName); // if it returns true-> the file was found and removed
}

bool FileSystem::findFile(const std::string& path, File*& target) const
{
	if (path.length() == 0)
		return false;

	std::vector<std::string> arguments;
	Utils::splitUnixFilePath(path, arguments);
	size_t tempCnt = arguments.size();
	std::string fileName = arguments[tempCnt - 1];
	std::string directory = "";
	for (size_t i = 0; i < tempCnt - 1; i++)
	{
		directory += arguments[i];
	}
	
	Directory* targetDir = nullptr;
	if (findDirectory(directory, targetDir) == false)
		return false;

	tempCnt = targetDir->getFiles().size();
	for (size_t i = 0; i < tempCnt; i++)
	{
		if (targetDir->getFiles()[i]->getName() == fileName)
		{
			target = targetDir->getFiles()[i];
			return true;
		}
	}

	return false;
}

bool FileSystem::findDirectory(const std::string& targetDir, Directory*& result) const
{
	if (targetDir.length() == 0)
	{
		result = toggledDir;
		return true;
	}
	std::vector<std::string> arguments;
	Utils::splitUnixFilePath(targetDir, arguments);
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

	return findDirectory(newDir, toggledDir);
}

void FileSystem::list(const std::string& targetDir)
{
	// list current directory if no target is specified
	if (targetDir.length() == 0)
	{
		toggledDir->list();
		toggledDir->refreshLastAccessed();
		return;
	}

	Directory* temp = toggledDir;
	findDirectory(targetDir, temp); // if it successful then temp points to the desired directory
									// if it has failed then temp is the current working directory

	temp->list();
	temp->refreshLastAccessed();
}

void FileSystem::concatenate(const std::vector<std::string>& files, const std::string& destinationFile)
{
	// this edge case is covered in the command creators and such input will never reach this function
	// if (files.size() == 0 && destinationFile.length() == 0)

	File* destination = nullptr;
	findFile(destinationFile, destination);
	if (files.size() == 0)
	{
		if (destination == nullptr)
		{
			std::cout << "Destination file " << destinationFile << " could not be found and concatenation will not be performed!" << std::endl;
			return;
		}
		// data input from the console not ready
		/*std::vector<std::string> content;
		std::string currentLine = "";
		std::cout << "No files were provided, enter content to be added to " << destinationFile << " yourself from the console" << std::endl;
		std::cout << "To stop the proccess of data inputting enter a dot(.) on a line of its own" << std::endl;
		while (currentLine != ".")
		{
			std::getline(std::cin, currentLine);
			if (currentLine == ".")
				break;
			content.push_back(currentLine);
		}*/
	}
	
	size_t filesCount = files.size();
	File* temp = nullptr;

	if (destination == nullptr)
	{
		for (size_t i = 0; i < filesCount; i++)
		{
			if (findFile(files[i], temp) == false)
			{
				std::cout << "File " << files[i] << " could not be found and won't be concatenated!" << std::endl;
				continue;
			}

			temp->printContent();
		}
		return;
	}

	for (size_t i = 0; i < filesCount; i++)
	{
		if (findFile(files[i], temp) == false)
		{
			std::cout << "File " << files[i] << " could not be found and won't be concatenated!" << std::endl;
			continue;
		}

		destination->addContent(temp->getContent());
	}
}
