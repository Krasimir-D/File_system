#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Utils
{
	// splits a string by a specified delimeter into a vector of string
	void splitUnixFilePath(const std::string& input, std::vector<std::string>& result);

	// extracts the file name from a specified path
	bool extractFileName(const std::string& filepath, std::string& filename);
}
