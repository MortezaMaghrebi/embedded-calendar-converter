#ifndef DATETIME_CONVERTER_H
#define DATETIME_CONVERTER_H

#include <stdint.h>


typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#define DAY_SECONDS 86400



typedef struct 
{
	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t hour;
	uint32_t minute;
	uint32_t second;
	uint32_t weekday;
}DateTimeGregorian;

bool isleap(int year);
uint32_t Convert_DateTimeGregorian_Int32(DateTimeGregorian date);
DateTimeGregorian Convert_Int32_DateTimeGregorian(uint32_t counter);

typedef struct 
{
	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t hour;
	uint32_t minute;
	uint32_t second;
	uint32_t weekday;
}DateTimeSolar;

bool iskabise(int year);
uint32_t Convert_DateTimeSolar_Int32(DateTimeSolar date);
DateTimeSolar Convert_Int32_DateTimeSolar(uint32_t counter);
#endif // DATETIME_CONVERTER_H
