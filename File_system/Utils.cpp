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

void Utils::splitDirAndName(const std::string& filePath, std::string& dir, std::string& name)
{
    std::vector<std::string> args;
    splitUnixFilePath(filePath, args);
    size_t size = args.size();
    name = args[size - 1];

    for (size_t i = 0; i < size - 1; i++)
    {
        dir += args[i];
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

std::string Utils::stringToLower(const std::string& string)
{
    size_t length = string.length();
    std::string result = string;
    for (size_t i = 0; i < length; i++)
    {
        if (result[i] > 64 && result[i] < 91)
            result[i] += 32;
    }
    return result;
}

std::string Utils::removeExtraWhitespaces(const std::string& string)
{
    size_t length = string.length();
    std::string result = "";
    bool isPrevWhitespace = false;

    for (size_t i = 0; i < length; i++)
    {
        if (string[i] != ' ' && isPrevWhitespace)
        {
            result.push_back(string[i]);
            isPrevWhitespace = false;
            continue;
        }

        if (string[i] == ' ' && isPrevWhitespace)
            continue;

        if (string[i] == ' ' && !isPrevWhitespace)
        {
            result.push_back(string[i]);
            isPrevWhitespace = true;
            continue;
        }

        if (string[i] == ' ' && i == length - 1)
            break;

        result.push_back(string[i]);
    }

    return result;
}

void Utils::removeEmptyArguments(std::vector<std::string>& arguments)
{
    size_t size = arguments.size();
    for (size_t i = 0; i < size; i++)
    {
        if (arguments[i] == "")
        {
            arguments.erase(arguments.begin() + i);
            i--;
        }
    }
}

std::vector<std::string> Utils::parseCommandLine(const std::string& string)
{
    std::string result = Utils::removeExtraWhitespaces(string);
    std::string currentWord;
    size_t length = result.length();
    std::vector<std::string> arguments;

    for (size_t i = 0; i < length; i++)
    {
        if (result[i] == ' ')
        {
            arguments.push_back(currentWord);
            currentWord = "";
            continue;
        }

        if (result[i] != ' ' && i == length)
        {
            currentWord.push_back(result[i]);
            arguments.push_back(currentWord);
            currentWord = "";
        }

        else
            currentWord.push_back(result[i]);
    }
    arguments.push_back(currentWord);
    removeEmptyArguments(arguments);

    return arguments;
}


