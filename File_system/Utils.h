#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Utils
{
	// splits a string by delimeter '/' into a vector of string
	void splitUnixFilePath(const std::string& input, std::vector<std::string>& result);

	// splits a file path by path as a first argument and name- second
	void splitDirAndName(const std::string& filePath, std::string& dir, std::string& name);

	// extracts the file name from a specified path
	// works for unix paths that dont end with '/'
	bool extractFileName(const std::string& filepath, std::string& filename);
}
