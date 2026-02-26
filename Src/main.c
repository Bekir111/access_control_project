
#include <stdint.h>
#include "f446re_gpio.h"
#include "f446re_rcc.h"
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "f446re_uart.h"
#include "uart_driver.h"

int main(void)
{



	//Enable clock for GPIOA
	RCC_GPIOA_clock_enable();

	//Set pin 5 at GPIOA MODER register as output
	GPIO_pin_mode(GPIOA, GPIO_PIN_5, GPOM_MODE);
	GPIO_pin_mode(GPIOA, GPIO_PIN_12, GPOM_MODE);

	//UART INIT PROTOTYPE

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

	//UART INIT PROTOTYPE

	UART_enable(USART2);

	while(1){
		//Setting pin5 as high
		GPIO_write_pin(GPIOA, GPIO_PIN_5, HIGH);
		GPIO_write_pin(GPIOA, GPIO_PIN_12, HIGH);

		//Set low pin5
		GPIO_write_pin(GPIOA, GPIO_PIN_5, LOW);

	}
}
