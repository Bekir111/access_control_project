#include "i2c_driver.h"
#include "gpio_driver.h"
#include "rcc_driver.h"

#include <stdint.h>

void I2C_init(I2C_typeDef* i2c){

	//Enabling the clock for B peripheral
	RCC_GPIOB_clock_enable();
	//Enabling clock for the I2C1
	RCC_I2C1_clock_enable();

	//Setting GPIO's for Alternate function mode
	GPIO_pin_mode(GPIOB, GPIO_PIN_6, AF_MODE);
	GPIO_pin_mode(GPIOB, GPIO_PIN_7, AF_MODE);

	//Setting the output type for open-drain
	GPIO_output_type(GPIOB, GPIO_PIN_6, OTYPE_OD);
	GPIO_output_type(GPIOB, GPIO_PIN_7, OTYPE_OD);

	//Setting the pull up resistor by software. Will be added physical pull up on the PCB to ensure that
	//SCL and SDA lines will be pulled high and pulled low only via hardware that uses I2C lines
	GPIO_pull_up(GPIOB, GPIO_PIN_6);
	GPIO_pull_up(GPIOB, GPIO_PIN_7);

	//Selecting AF4 for the GPIO's
	//I2C1_SCL
	GPIO_AF_selection_low(GPIOB, GPIO_PIN_6, AF4);
	//I2C1_SDA
	GPIO_AF_selection_low(GPIOB, GPIO_PIN_7, AF4);


	//Reset the I2C
	i2c->CR1 |= I2C_CR1_SWRST;
	i2c->CR1 &= ~(I2C_CR1_SWRST);

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

	//Set TRISE value
	/*
	 * the formula from the datasheet for the value in TRIS register is:
	 * Trise(max)/Tpclk1 => for prototyping we use 16MHz so:
	 * 1000n/62,5n = 16 + 1 => 17 (0x11)
	 */
	i2c->TRISE = 17;

	//Peripheral enable
	i2c->CR1 |= I2C_CR1_PE;

	//ACK control bit
	i2c->CR1 &= ~(I2C_CR1_ACK);
	i2c->CR1 |= I2C_CR1_ACK;
}
