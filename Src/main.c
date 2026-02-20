
#include <stdint.h>
#include "f446re_gpio.h"
#include "f446re_rcc.h"

int main(void)
{
	//Enable clock for GPIOA
	RCC->AHB1ENR = RCC_AHB1ENR_GPIOA;

	//Set pin 5 at GPIOA MODER register as output
	GPIOA->MODER |= (GPOM_MODE << 10);

	while(1){
		//Setting pin5 as high
		GPIOA->ODR |= (1 << 5);

		//Set low pin5
		GPIOA->ODR |= (1 << 5);

	}
}
