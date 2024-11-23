#include "Utils.h"

bool Utils::splitStringByDelimiter(const std::string& input, std::vector<std::string>& result, char delim)
{
	if (input.length() == 0)
		return false; // operation failed. This result has to be processed in some other class. Possibly UI class to inform the user of the invalid input

	size_t length = input.length();
	std::string temp = "";
	for (size_t i = 0; i < length; i++)
	{
		while (input[i] != delim)
		{
			temp += input[i];
		}
		result.push_back(temp);
		temp.clear();
	}

	return true;
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


