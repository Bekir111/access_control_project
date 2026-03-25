#include "i2c_driver.h"
#include <stdint.h>

void I2C_init(I2C_typeDef* i2c){

	//Reset the I2C
	i2c->CR1 |= I2C_CR1_SWRST;
	i2c->CR1 &= ~(I2C_CR1_SWRST);

	//ACK control bit
	i2c->CR1 &= ~(I2C_CR1_ACK);
	i2c->CR1 |= I2C_CR1_ACK;

	//Set the FREQ value
	i2c->CR2 = I2C_CR2_FREQ_TEST;
	/*
	 * Now for the calculation of the CCR register for Sm, with 100KHz SCL clock frequency:
	 * Peripheral clock for testing is 16MHz, but for production will calculate for 45MHz
	 * Thigh + Tlow = 2 * CCR * Tpclk1
	 * CCR = (Thigh + Tlow)/(2 * Tpclk1) => 0,00001 / (0,0000000625 * 2)
	 * CCR = 80
	 * We have to write in CCR register the value 80 decimal 0x50
	 */
	i2c->CCR |= (0x50 & 0xFFF);
}
