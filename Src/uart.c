
#include"uart_driver.h"
#include "rcc_driver.h"
#include "gpio_driver.h"

void

void UART2_init(void){
		//UART2 clock enable
		RCC_UART2_clock_enable();

		//Set PA2 as AF mode
		GPIO_pin_mode(GPIOA, GPIO_PIN_2, AF_MODE);
		//Set PA3 as AF mode
		GPIO_pin_mode(GPIOA, GPIO_PIN_3, AF_MODE);

		//AF selection for PA2
		GPIO_AF_selection_low(GPIOA, GPIO_PIN_2, AF7);

		//AF selection for PA3
		GPIO_AF_selection_low(GPIOA, GPIO_PIN_3, AF7);
		//Pull up on RX to prevent floating pin. UART RX idle is HIGH
		GPIO_pull_up(GPIOA, GPIO_PIN_3);


}

