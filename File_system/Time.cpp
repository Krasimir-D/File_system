#include "Time.h"
#include <string>
#include <sstream>
#include <iomanip> 
#pragma warning (disable : 4996)

Time::Time()
	: hour(0), minutes(0), seconds(0), isPm(false)
{
	time_t timestamp = time(NULL);
	struct tm dateTime = *localtime(&timestamp);

	uint8_t hour = dateTime.tm_hour;
	bool isPm = false;
	if (hour >= 12)
	{
		isPm = true;
		hour %= 12;
	}

	uint8_t minutes = dateTime.tm_min; 
	uint8_t seconds = dateTime.tm_sec % 60; 

	setTime(hour, minutes, seconds, isPm);
}

Time::Time(uint8_t hour, uint8_t minutes, uint8_t seconds, bool isPm)
	: hour(0), minutes(0), seconds(0), isPm(false)
{
	setTime(hour, minutes, seconds, isPm);
}

void Time::setTime(uint8_t hour, uint8_t minutes, uint8_t seconds, bool isPm)
{
	if (hour < 1 || hour > 12 || minutes > 59 || seconds > 59)
		throw std::invalid_argument("Invalid time arguments!");

	this->hour = hour;
	this->minutes = minutes;
	this->seconds = seconds;
	this->isPm = isPm;
}

void Time::toString(std::string& str) const
{
	std::ostringstream oss;
	oss << std::setfill('0')
		<< std::setw(2) << static_cast<int>(hour) << ":" // Ensure hour is 2 digits
		<< std::setw(2) << static_cast<int>(minutes) << ":" // Ensure minutes is 2 digits
		<< std::setw(2) << static_cast<int>(seconds) << " " // Ensure seconds is 2 digits
		<< (isPm ? "PM" : "AM"); // Append AM/PM based on isPm flag

	str = oss.str();
}
