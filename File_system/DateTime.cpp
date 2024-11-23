#include "DateTime.h"

void DateTime::toString(std::string& str) const
{
	str.clear();
	date.toString(str);
	str += " ";
	std::string strTime = "";
	time.toString(strTime);

	str += strTime;
}

std::string DateTime::toString() const
{
	std::string result;
	date.toString(result);
	result += " ";
	std::string strTime = "";
	time.toString(strTime);

	result += strTime;

	return result;
}
