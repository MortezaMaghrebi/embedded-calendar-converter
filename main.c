#include <stdio.h>
#include <stdint.h>
#include "datetime_converter.h"

char *weekdays[7] = {
	"saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
};

int main()
{
	DateTimeGregorian dtg;
    dtg.year=2157;
    dtg.month=12;
    dtg.day=29;
    dtg.hour=12;
    dtg.minute=0;
    dtg.second=0;
    
    uint32_t seconds = Convert_DateTimeGregorian_Int32(dtg);  //convert Gregorian datetime to seconds
    DateTimeSolar dts = Convert_Int32_DateTimeSolar(seconds); //convert seconds to Solar datetime
    DateTimeGregorian dtgn = Convert_Int32_DateTimeGregorian(seconds); //convert seconds to Gregorian datetime to verify it
    
	printf("Gregorian DateTime:  %d/%d/%d - %d:%d:%d - %s\n",
		dtgn.year, dtgn.month, dtgn.day,
		dtgn.hour, dtgn.minute, dtgn.second,
		weekdays[dtgn.weekday]);

	printf("Solar DateTime:  %d/%d/%d - %d:%d:%d - %s\n",
		dts.year, dts.month, dts.day,
		dts.hour, dts.minute, dts.second,
		weekdays[dts.weekday]);

	return 0;
}
