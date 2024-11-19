#pragma once
#include <iostream>
#include <ctime>


// represents the date in the dd/mm/yy format compressed into a bitset of 16 bits
class Date
{
public:
	Date();
	Date(uint16_t day, uint16_t month, uint16_t year);

	void toString(std::string& str) const; // returns a string in a dd/mm/yy format
	void setDate(uint16_t day, uint16_t month, uint16_t year);

	static bool isLeapYear(uint16_t year);

private:
	uint16_t date;

	static constexpr  uint16_t EPOCH_START = 1970;

	// masks
	static constexpr uint16_t DAY_MASK = 0x1f; 
	static constexpr uint16_t MONTH_MASK = 0x1E0;
	static constexpr uint16_t YEAR_MASK = 0x7E00;

	// days in months of a non-leap year
	static constexpr int DAYS_IN_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// shifts required to encode the date in a 16-bit unsigned integer
	static constexpr uint8_t MONTH_SHIFT = 5;
	static constexpr uint8_t YEAR_SHIFT = 9;
};

