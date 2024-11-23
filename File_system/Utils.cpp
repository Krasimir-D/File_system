#include "Utils.h"

void Utils::splitUnixFilePath(const std::string& input, std::vector<std::string>& result)
{   
    std::string current;
    size_t length = input.length();
    for (size_t i = 0; i < length; ++i)
    {
        // covers the case for an absolute path
        if (input[i] == '/' && i == 0)
            result.push_back("/");

        if (input[i] == '/')
        {
            if (!current.empty()) 
            {
                result.push_back(current);
                current.clear();
            }
        }
        else
        {
            current += input[i];
        }
    }
    // Add the last component if it exists
    if (!current.empty()) {
        result.push_back(current);
    }
}

bool Utils::extractFileName(const std::string& filepath, std::string& filename)
{
	if (filepath.length() == 0)
		return false;

	int length = filepath.length();
	for (int i = length - 1; i >= 0; --i)
	{
		if (filepath[i] != '\\')
			filename += filepath[i];
	}

	// reverse the string because of the way the name was extracted 
	std::reverse(filename.begin(), filename.end());
	return true;
}


