
#ifndef DS3231_H_
#define DS3231_H_

#define			DS3231_ADDR			(0x68)


typedef struct{
	uint8_t 	day;
	uint8_t 	month;
	uint16_t 	year;
	uint8_t		hour;
	uint8_t		minute;
}DS3231_data_t;



#define BCD_TO_DEC(x)  (x - 6 * (x >> 4))
#define DEC_TO_BCD(x)  (((x / 10) << 4) | (x % 10))

#endif /* DS3231_H_ */
