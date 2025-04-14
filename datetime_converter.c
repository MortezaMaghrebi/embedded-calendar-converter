#include "datetime_converter.h"

bool isleap(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0) return true;
			else return false;
		}
		else return true;
	}
	else return false;
}

DateTimeGregorian Convert_Int32_DateTimeGregorian(uint32_t _counter)
{
	static volatile DateTimeGregorian date;
	date.year = 2022;
	date.month = 1;
	date.day = 1;
	const int MonthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	static volatile uint32_t counter = 6825600 + _counter;
	static volatile uint32_t seconds = counter % DAY_SECONDS;
	static volatile uint32_t days = counter / DAY_SECONDS + 1;

	static volatile uint32_t yeardays = 365;
	static volatile uint32_t monthdays = 31;

	date.week = days % 7 - 1;
	if (date.week < 0) date.week += 7;
	if (date.week > 6) date.week -= 7;

	while (days > yeardays)
	{
		days -= isleap(date.year) ? 366 : 365;
		date.year++;
		yeardays = isleap(date.year) ? 366 : 365;
	}

	while (days > monthdays)
	{
		if (date.month == 2)
		{
			days -= isleap(date.year) ? 29 : 28;
		}
		else
		{
			days -= MonthDays[date.month - 1];
		}
		date.month++;
		monthdays = (date.month == 2) ? (isleap(date.year) ? 29 : 28) : MonthDays[date.month - 1];
	}

	date.day = days;
	date.second = seconds % 60;
	date.minute = (seconds / 60) % 60;
	date.hour = seconds / 3600;

	return date;
}

uint32_t Convert_DateTimeGregorian_Int32(DateTimeGregorian date)
{
	static volatile uint32_t time = 0;
	const int MonthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	for (int i = 2022; i < date.year; i++)
		time += isleap(i) ? 31622400 : 31536000;

	for (int i = 1; i <= 11 && i < date.month; i++)
	{
		if (i == 2)
			time += (isleap(date.year) ? 29 : 28) * 86400;
		else
			time += MonthDays[i - 1] * 86400;
	}

	time += (date.day - 1) * 86400;
	time += date.hour * 3600;
	time += date.minute * 60;
	time += date.second;

	time -= 6825600;

	return time;
}

bool iskabise(int year)
{
	const int kabises[] = { 1,5,9,13,17,22,26,30 };
	for (int j = 0; j < sizeof(kabises) / sizeof(int); j++)
	{
		if (year % 33 == kabises[j]) return true;
	}
	return false;
}

uint32_t Convert_DateTimeSolar_Int32(DateTimeSolar date)
{
	static volatile uint32_t time = 0;

	for (int i = 1401; i < date.year; i++)
		time += iskabise(i) ? 31622400 : 31536000;

	for (int i = 1; i <= 6 && i < date.month; i++)
		time += 2678400;

	for (int i = 7; i <= 11 && i < date.month; i++)
		time += 2592000;

	time += (date.day - 1) * 86400;
	time += date.hour * 3600;
	time += date.minute * 60;
	time += date.second;

	return time;
}

DateTimeSolar Convert_Int32_DateTimeSolar(uint32_t counter)
{
	static volatile DateTimeSolar date;
	date.year = 1401;
	date.month = 1;
	date.day = 1;

	static volatile uint32_t seconds = counter % DAY_SECONDS;
	static volatile uint32_t days = counter / DAY_SECONDS + 1;
	static volatile uint32_t yeardays = 365;
	static volatile uint32_t monthdays = 31;

	date.week = days % 7 + 1;
	if (date.week > 6) date.week -= 7;

	while (days > yeardays)
	{
		days -= iskabise(date.year) ? 366 : 365;
		date.year++;
		yeardays = iskabise(date.year) ? 366 : 365;
	}

	while (days > monthdays)
	{
		if (date.month <= 6) days -= 31;
		else if (date.month <= 11) days -= 30;
		else days -= iskabise(date.year) ? 30 : 29;

		date.month++;

		if (date.month <= 6) monthdays = 31;
		else if (date.month <= 11) monthdays = 30;
		else monthdays = iskabise(date.year) ? 30 : 29;
	}

	date.day = days;
	date.second = seconds % 60;
	date.minute = (seconds / 60) % 60;
	date.hour = seconds / 3600;

	return date;
}
