#pragma once
#include "Date.h"
#include "Time.h"

struct DateTime
{
	DateTime() = default;
	DateTime(Date date, Time time) : date(date), time(time) {}

	void toString(std::string& str) const;

	Date date;
	Time time;
};

