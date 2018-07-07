#pragma once
#include <ctime>
typedef unsigned int uint;
class Date
{
public:
	Date() {}
	Date(uint year, uint month, uint day);
	Date operator+(uint day)const;
	bool operator>(Date date)const;
	const char* ToString()const;
	static Date Now();
	static uint DaysOfMonth(uint year, uint month);
	static bool IsLeapYear(uint year)
	{
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}
private:
	uint day, month, year;
	char str[11];
	void Normalize();
};

