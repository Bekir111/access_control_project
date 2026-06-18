
#include "rcc_driver.h"

void RCC_GPIOA_clock_enable(void){
	RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOA);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOA;
}
void RCC_GPIOB_clock_enable(void){
	RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOB);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOB;
}
void RCC_GPIOC_clock_enable(void){
	RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOC);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOC;
}
void RCC_UART2_clock_enable(void){
	RCC->APB1ENR &= ~(RCC_APB1ENR_UART2);
	RCC->APB1ENR |= RCC_APB1ENR_UART2;
}

void RCC_UART4_clock_enable(void){
	RCC->APB1ENR &= ~(RCC_APB1ENR_UART4);
	RCC->APB1ENR |= RCC_APB1ENR_UART4;
}

void RCC_UART5_clock_enable(void){
	RCC->APB1ENR &= ~(RCC_APB1ENR_UART5);
	RCC->APB1ENR |= RCC_APB1ENR_UART5;
}

void RCC_TIM6_clock_enable(void){
	RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6);
	RCC->APB1ENR |= RCC_APB1ENR_TIM6;
}
void RCC_TIM7_clock_enable(void){
	RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7);
	RCC->APB1ENR |= RCC_APB1ENR_TIM7;
}

void RCC_I2C1_clock_enable(void){
	RCC->APB1ENR &= ~(RCC_APB1ENR_I2C1);
		RCC->APB1ENR |= RCC_APB1ENR_I2C1;
}
