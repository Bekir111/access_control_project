#include "gpio_driver.h"

void GPIO_pin_mode(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t mode){
	//Clear bits
	GPIOx->MODER &= ~(3 << (pin*2));

	//Set bits
	GPIOx->MODER |= (mode << (pin*2));
}
void GPIO_write_pin(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t state)
{
	if(state){
		GPIOx->BSRR =  (1 << pin);
	}
	else{
		GPIOx->BSRR = (1 << (16 + pin));
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
void GPIO_AF_selection_low(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t af_mode){
		//Clear bits
		GPIOx->AFRL &= ~(af_mode << (pin * 4));
		//Set bits
		GPIOx->AFRL |= (af_mode << (pin * 4));

}

void GPIO_output_type(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t o_type){
	//Clear bit
	GPIOx->OTYPER &= ~(o_type << pin);
	//Set bit
	GPIOx->OTYPER |= o_type << pin;
}
