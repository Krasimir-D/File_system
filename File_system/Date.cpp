#include "Date.h"
#include <string>
#include <sstream>
#include <iomanip> 
#pragma warning (disable : 4996)

Date::Date()
	: date(0)
{
	time_t timestamp = time(NULL);
	struct tm dateTime = *localtime(&timestamp);

	uint8_t day = dateTime.tm_mday;
	uint8_t month = dateTime.tm_mon + 1; // tm_mon is 0-based
	uint16_t year = dateTime.tm_year + 1900; // tm_year is years since 1900

	setDate(day, month, year);
}

Date::Date(uint16_t day, uint16_t month, uint16_t year)
	: date(0)
{
	setDate(day, month, year);
}

void Date::toString(std::string& str) const
{
	uint16_t day = date & DAY_MASK;
	uint16_t month = (date & MONTH_MASK) >> MONTH_SHIFT;
	uint16_t year = ((date & YEAR_MASK) >> YEAR_SHIFT) + EPOCH_START;

	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(2) << day << "/"
		<< std::setw(2) << month << "/"
		<< std::setw(4) << year;

	str = oss.str();
}

void Date::setDate(uint16_t day, uint16_t month, uint16_t year)
{
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < EPOCH_START || year > 2033)
		throw std::invalid_argument("Invalid date argument!");

	if (day == 31 && DAYS_IN_MONTH[month - 1] != 31)
		throw std::invalid_argument("Invalid date argument!");

	if (day == 29 && month == 2 && !isLeapYear(year))
		throw std::invalid_argument("Invalid date argument!");

	year -= EPOCH_START;

	date = date | day | (month << MONTH_SHIFT) | (year << YEAR_SHIFT);
}

bool Date::isLeapYear(uint16_t year)
{
	if (year % 4 != 0)
		return false;

	if (year % 100 != 0)
		return true;

	if (year % 400 != 0)
		return false;

	return true;
}
