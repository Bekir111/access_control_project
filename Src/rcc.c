
#include "rcc_driver.h"

void RCC_GPIOA_clock_enable(void){
	RCC->AHB1ENR = RCC_AHB1ENR_GPIOA;
}
void RCC_GPIOB_clock_enable(void){
	RCC->AHB1ENR = RCC_AHB1ENR_GPIOB;
}
void RCC_GPIOC_clock_enable(void){
	RCC->AHB1ENR = RCC_AHB1ENR_GPIOC;
}


