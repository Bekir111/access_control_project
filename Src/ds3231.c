#include "ds3231.h"
#include "i2c_driver.h"

volatile uint8_t rtc_buffer[7];

void DS3231_GetTime(DS3231_data_t *time)
{
	I2C_multiple_read(I2C1, 7, rtc_buffer);
	time->minute = BCD_TO_DEC(rtc_buffer[0]);
	time->hour   = BCD_TO_DEC(rtc_buffer[1]);
	time->day    = BCD_TO_DEC(rtc_buffer[3]);
	time->month  = BCD_TO_DEC(rtc_buffer[4]);
	time->year   = (2000 + BCD_TO_DEC(rtc_buffer[5]));
}
