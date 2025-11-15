#include "datetime_converter.h"

/* This is a library to convert Solar and Gregorian datetime to each other,
    this code is valid for datetime:
    from 2022/3/21 Gregorian (1401/01/01 Solar)
    to  2157/12/29 Gregorian (1536/10/08 Solar)
*/

/* Also this library is useful for those microcontrollers that has only one 32 bit counter register for the RTC*/

bool isleap(int year)
{
    if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0) return TRUE;
			else return FALSE;
		}
		else return TRUE;
	}
	else return FALSE;
}

DateTimeGregorian Convert_Int32_DateTimeGregorian(uint32_t _counter)
{
	static volatile DateTimeGregorian date;
	date.year=2022;
	date.month=1;
	date.day=1;
	const int MonthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	static volatile uint32_t counter; counter	= 6825600 + _counter;      //start from 2022/03/21 = 1401/01/01 rather than 2022/01/01
	static volatile uint32_t seconds;	seconds	= counter % DAY_SECONDS;
	static volatile uint32_t days;		days	= counter / DAY_SECONDS + 1;
	
	date.year = 2022;
	date.month = 1;
	date.day = 1;
	static volatile uint32_t yeardays;	yeardays = 365;
	static volatile uint32_t monthdays;	monthdays = 31;

	date.weekday =  ((days + 6) % 7 + 7) % 7;
	

	while (days > yeardays)
	{
		if (isleap(date.year)) days -= 366;
		else days -= 365;
		date.year++;
		if (isleap(date.year)) yeardays = 366;
		else yeardays = 365;
	}

	if (isleap(date.year))
	{
		int k = 0;
	}
	while (days > monthdays)
	{
		if (date.month == 2)
		{
			if (isleap(date.year)) days -= 29;
			else days -= 28;
		}
		else days -= MonthDays[date.month - 1];

		date.month++;
		if (date.month == 2)
		{
			if (isleap(date.year)) monthdays = 29;
			else monthdays = 28;
		}
		else monthdays = MonthDays[date.month - 1];
	}

	date.day = days;

	date.second = seconds % 60;
	date.minute = (seconds / 60) % 60;
	date.hour = (seconds / 3600);
	return date;
}

uint32_t Convert_DateTimeGregorian_Int32(DateTimeGregorian date)
{
	static volatile uint32_t time; time = 0;

	const int MonthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31};


	for (int i = 2022; i < date.year; i++)
	{
		if (isleap(i)) time += 31622400;
		else time += 31536000;
	}

	for (int i = 1; i <= 11 && i < date.month; i++)
	{
		if (i == 2)
		{
			if (isleap(date.year)) time += (29 * 86400);
			else time += (28 * 86400);
		}else time += (MonthDays[i-1]*86400);
	}

	time += (date.day - 1) * 86400;
	time += (date.hour) * 3600;
	time += (date.minute) * 60;
	time += date.second;

	time -= 6825600;

	return time;
}

bool iskabise(int year)
{
	const int kabises[] = { 1,5,9,13,17,22,26,30 };
	volatile bool kabise = FALSE;
	for (int j = 0; j < sizeof(kabises) / sizeof(int); j++)
	{
		if (year % 33 == kabises[j])kabise = TRUE;
	}
	return kabise;
}


uint32_t Convert_DateTimeSolar_Int32(DateTimeSolar date)
{
	static volatile uint32_t time;
	time = 0;
	
	//int kabises[] = { 1403,1408,1412,1416,1420,1424,1428,1432,1436,1441,1445,1449,1453,1457,1461,1465,1469,1474,1478,1482,1486,1490,1494,1498,1502,1507,1511,1515,1519,1523,1527,1531,1535,1540,1544,1548,1552,1556,1560,1564,1568,1573,1577,1581,1585,1589,1593,1597,1601,1606,1610,1614,1618,1622,1626,1630,1634,1639,1643,1647,1651,1655,1659,1663,1667,1672,1676,1680,1684,1688,1692,1696 };

	
	for (int i = 1401; i < date.year; i++)
	{
		if (iskabise(i)) time += 31622400;
		else time += 31536000;
	}

	for (int i = 1; i <= 6 && i < date.month; i++)
	{
		time += 2678400;
	}

	for (int i = 7; i <= 11 && i < date.month;i++)
	{
		time += 2592000;
	}

	time += (date.day - 1) * 86400;
	time += (date.hour ) * 3600;
	time += (date.minute) * 60;
	time += date.second;

	return time;

}


DateTimeSolar Convert_Int32_DateTimeSolar(uint32_t counter)
{
	static volatile DateTimeSolar date;
	date.year=1401;
	date.month=1;
	date.day=1;
	static volatile uint32_t seconds; 	seconds = counter % DAY_SECONDS;
	static volatile uint32_t days; 			days = counter / DAY_SECONDS +1;
	static volatile uint32_t yeardays;	yeardays = 365;
	static volatile uint32_t monthdays;	monthdays = 31;
	
	date.weekday = ((days + 1) % 7 + 7) % 7;
	

	while (days > yeardays)
	{
		if (iskabise(date.year)) days -= 366;
		else days -= 365;
		date.year++;
		if (iskabise(date.year)) yeardays = 366;
		else yeardays = 365;
	}

	if (iskabise(date.year))
	{
		int k = 0;
	}
	while (days > monthdays)
	{
		if (date.month <= 6) days -= 31;
		else if (date.month <= 11) days -= 30;
		else if (iskabise(date.year)) days -= 30;
		else days -= 29;
		date.month++;
		if (date.month <= 6) monthdays = 31;
		else if (date.month <= 11) monthdays = 30;
		else if (iskabise(date.year)) monthdays = 30;
		else monthdays = 29;
	}

	date.day = days;

	date.second = seconds % 60;
	date.minute = (seconds / 60) % 60;
	date.hour = (seconds / 3600);

	return date;

}

