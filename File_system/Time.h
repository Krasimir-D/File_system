#pragma once
#include <iostream>

// represents the time in the hh:mm:ss format in a 16-bit bitset. 12-hour format
class Time
{
public:
	Time();
	Time(uint8_t hour, uint8_t minutes, uint8_t seconds, bool isPm);

	void setTime(uint8_t hour, uint8_t minutes, uint8_t seconds, bool isPm);
	void toString(std::string& str) const;

private:
	uint8_t hour; // 1-12
	uint8_t minutes; // 0-59
	uint8_t seconds; // 0-59

	bool isPm; // true = PM; false = AM
};

