
#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include "f446re_i2c.h"

extern volatile uint8_t rtc_buffer[7];

void I2C_write(I2C_typeDef* i2c,
			   const uint8_t year, const uint8_t day,
			   const uint8_t month, const uint8_t hours,
			   const uint8_t minutes);
void I2C_multiple_read(I2C_typeDef* i2c, uint8_t len, volatile uint8_t* buffer);
void I2C_init(I2C_typeDef* i2c);

#endif /* I2C_DRIVER_H_ */
