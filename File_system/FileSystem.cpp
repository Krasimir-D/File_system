#include "FileSystem.h"
#include <cstring>
#include <fstream>

bool FileSystem::save(const char* path) const
{
	std::string aggregatedPath;
	if (path == nullptr || strlen(path) == 0)
		aggregatedPath = systemName;

	aggregatedPath += ".bin";
	std::ofstream out(aggregatedPath, std::ios::binary);
	if (!out.is_open())
		return false;

	if (!root->save(out) == false)
		return false;

	out.close();
	return true;
}

bool FileSystem::load(const std::string& filepath)
{
	if (filepath.length() == 0)
		return false;

	std::ifstream input(filepath, std::ios::binary);
	if (!input.is_open())
		return false;

	if (root->load(input) == false)
		return false;

	input.close();
	return true;
}

bool FileSystem::importFile(const std::string& targetFile, const std::string& targetDir)
{
	// TO_DO: if targetDir = "", targetDir = toggledDir 
	File* file = nullptr;

	if (File::import(targetFile, file) == false)
		return false;

	root->add(file);

	return true;
}

FileSystem::FileSystem(const std::string& systemName)
	: systemName(systemName), root(nullptr), toggledDir(nullptr), isActive(true)
{	
	root = new Directory();
	toggledDir = root;
}

FileSystem::~FileSystem()
{
	save();
	delete root;
	toggledDir = nullptr;
}
