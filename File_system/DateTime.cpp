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
