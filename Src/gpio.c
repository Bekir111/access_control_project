#include "gpio_driver.h"

void GPIO_pin_mode(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t mode){
	//Clear bits
	GPIOx->MODER &= ~(3 << (pin*2));

	//Set bits
	GPIOx->MODER |= (mode << (pin*2));
}
void GPIO_write_pin(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t state){
	if(state){
		GPIOx->BSRR = pin;
	}
	else{
		GPIOx->BSRR = (pin << 16);
	}
}
void GPIO_pull_up(GPIOx_typeDef* GPIOx, uint8_t pin)
{
	//Clear bits
	GPIOx->PUPDR &= ~(3 << (pin*2));

	//Set bits
	GPIOx->PUPDR |= (PUPD_PULLUP << (pin*2));
}
void GPIO_pull_down(GPIOx_typeDef* GPIOx, uint8_t pin)
{
	//Clear bits
	GPIOx->PUPDR &= ~(3 << (pin*2));

	//Set bits
	GPIOx->PUPDR |= (PUPD_PULLDOWN << (pin*2));
}

