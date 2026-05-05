#include "i2c_driver.h"
#include "gpio_driver.h"
#include "rcc_driver.h"
#include "arm_nvic_driver.h"
#include "ds3231.h"

volatile uint8_t rtc_buffer[7];

#include <stdint.h>

void I2C_write(I2C_typeDef* i2c,
			   const uint8_t year,
			   const uint8_t month,
			   const uint8_t day,
			   const uint8_t hours,
			   const uint8_t minutes)
{
	volatile uint8_t i;
	//1. Set the START bit and ACK bit
	i2c->CR1 |= I2C_CR1_ACK;
	i2c->CR1 |= I2C_CR1_START;
	//Now have to wait for SB bit to be set as 1 (Start condition generated)
	while(!(i2c->SR1 & I2C_SR1_SB));

	//2. Have to read SR1 followed by writing the address of the slave in DR register
	(void)i2c->SR1;
	i2c->DR = (DS3231_ADDR << 1);

	//Waiting for ADDR flag to be set as 1
	while(!(i2c->SR1 & I2C_SR1_ADDR));

	//Clearing the SR1 register by reading SR1 followed by reading the SR2 register also
	(void)i2c->SR1;
	(void)i2c->SR2;
	//Checking transfer enable flag
	while(!(i2c->SR1 & I2C_SR1_TxE));
	//4. Writing the address where we want to set the internal pointer of the module
	i2c->DR = 0x01;

	//6. Writing the sequence of data by the length that is passed by the function
	for(i = 0; i < 6;i++){
		//Checking if the byte is received
		while(!(i2c->SR1 & I2C_SR1_TxE));
		switch(i){
			case 0:
				i2c->DR = (minutes);
			break;
			case 1:
				i2c->DR = DEC_TO_BCD(hours);
			break;
			case 2:
				i2c->DR = 0x00;
			break;
			case 3:
				i2c->DR = DEC_TO_BCD(day);
			break;
			case 4:
				i2c->DR = DEC_TO_BCD(month);
			break;
			case 5:
				i2c->DR = DEC_TO_BCD(year - 2000);
			break;

		}
	}

	while(!((i2c->SR1 & I2C_SR1_TxE) && (i2c->SR1 & I2C_SR1_BTF)));
	i2c->CR1 |= I2C_CR1_STOP;

}

void I2C_multiple_read(I2C_typeDef* i2c, uint8_t len, volatile uint8_t* buffer){
	volatile uint8_t i;
	//1. Set the START bit and ACK bit
	i2c->CR1 |= I2C_CR1_ACK;
	i2c->CR1 |= I2C_CR1_START;
	//Now have to wait for SB bit to be set as 1 (Start condition generated)
	while(!(i2c->SR1 & I2C_SR1_SB));

	//2. Have to read SR1 followed by writing the address of the slave in DR register
	(void)i2c->SR1;
	//This is write mode to set the internal pointer of the module to the 00
	i2c->DR = (DS3231_ADDR << 1);

	//Waiting for ADDR flag to be set as 1
	while(!(i2c->SR1 & I2C_SR1_ADDR));

	//Clearing the SR1 register by reading SR1 followed by reading the SR2 register also
	(void)i2c->SR1;
	(void)i2c->SR2;

	//4. Writing the address where we want to set the internal pointer of the module
	i2c->DR = 0x00;
	//Waiting for the byte to be successfully sent by checking for BTF flag
	while(!(i2c->SR1 & I2C_SR1_BTF));
	//Reading the SR1 and SR2 to clear the flag
	(void)i2c->SR1;
	(void)i2c->SR2;

	//5. Generating a repeated start to now read the data sequence
	i2c->CR1 |= I2C_CR1_START;
	//Writing the slave address with last bit to be 1 for reading
	i2c->DR = ((DS3231_ADDR << 1) | 0x01);
	//Waiting for ADDR flag to be set as 1
	while(!(i2c->SR1 & I2C_SR1_ADDR));
	//Clearing the ADDR bit by reading SR1 and SR2
	(void)i2c->SR1;
	(void)i2c->SR2;
	//6. Reading the sequence of data by the length that is passed by the function
	for(i = 0; i < len;i++){
		//Checking if the byte is received
		while(!(i2c->SR1 & I2C_SR1_RxNE));
		if(i < len - 1){
			//Reading until reaching the last byte of sequence
			buffer[i] = i2c->DR;
		}
		else{
			//When we receive the last byte of data we want to set NACK and generate Stop condition
			i2c->CR1 &= ~(I2C_CR1_ACK);
			i2c->CR1 |= I2C_CR1_STOP;
			buffer[i] = i2c->DR;
		}
	}

}


void I2C_init(I2C_typeDef* i2c){

	//Enabling the clock for B peripheral
	RCC_GPIOB_clock_enable();
	//Enabling clock for the I2C1
	RCC_I2C1_clock_enable();

	//Setting GPIO's for Alternate function mode
	GPIO_pin_mode(GPIOB, GPIO_PIN_8, AF_MODE);
	GPIO_pin_mode(GPIOB, GPIO_PIN_9, AF_MODE);

	//Setting the output type for open-drain
	GPIO_output_type(GPIOB, GPIO_PIN_8, OTYPE_OD);
	GPIO_output_type(GPIOB, GPIO_PIN_9, OTYPE_OD);

	//Setting the pull up resistor by software. Will be added physical pull up on the PCB to ensure that
	//SCL and SDA lines will be pulled high and pulled low only via hardware that uses I2C lines
	GPIO_pull_up(GPIOB, GPIO_PIN_8);
	GPIO_pull_up(GPIOB, GPIO_PIN_9);

	//Selecting AF4 for the GPIO's
	//I2C1_SCL
	GPIO_AF_selection_high(GPIOB, GPIO_PIN_8, AF4);
	//I2C1_SDA
	GPIO_AF_selection_high(GPIOB, GPIO_PIN_9, AF4);


	//Reset the I2C
	i2c->CR1 |= I2C_CR1_SWRST;
	i2c->CR1 &= ~(I2C_CR1_SWRST);

	//Set the FREQ value
	i2c->CR2 = I2C_CR2_FREQ_TEST;

	//Using I2C in Standart Mode
	i2c->CCR |= I2C_CCR_SM;
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

	/*
	 * This section is commented because first i will make the I2C work with polling. After testing
	 * and confirming that the data transfers are successful, then
	 */
	/*Enable interrupts
	i2c->CR2 &= ~(I2C_CR2_ITBUFEN);
	i2c->CR2 |= (I2C_CR2_ITBUFEN);
	i2c->CR2 &= ~(I2C_CR2_ITERREN);
	i2c->CR2 |= (I2C_CR2_ITERREN);
	i2c->CR2 &= ~(I2C_CR2_ITEVTEN);
	i2c->CR2 |= (I2C_CR2_ITEVTEN);*/

	//Peripheral enable
	i2c->CR1 |= I2C_CR1_PE;

	/*NVIC_EnableIRQ(IRQ_I2C1_EV);
	NVIC_EnableIRQ(IRQ_I2C1_ER);
	NVIC_SetPriority(IRQ_I2C1_EV, 2);
	NVIC_SetPriority(IRQ_I2C1_ER, 2);*/
}

void I2C1_EV_IRQHandler(void){
	;
}

void I2C1_ER_IRQHandler(void){
	;
}
