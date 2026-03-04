
#include <stdint.h>
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "uart_driver.h"

static	QR_data_t	qr1_data;
static	QR_data_t	qr2_data;



int main(void)
{
	//Enable clock for GPIOA
	RCC_GPIOA_clock_enable();

	//Set pin 5 at GPIOA MODER register as output
	GPIO_pin_mode(GPIOA, GPIO_PIN_5, GPOM_MODE);
	GPIO_pin_mode(GPIOA, GPIO_PIN_12, GPOM_MODE);

	//USART2 initialization
	UART2_init();

	while(1){

		UART_recieve_handler(USART2);

		if(UART_string_ready()){
			UART_string_ready_clear();
			if(QR_data_parse(uart_rx_buffer, &qr1_data)){

				GPIO_write_pin(GPIOA, GPIO_PIN_5,HIGH);

			}
		}
		else{
			GPIO_write_pin(GPIOA, GPIO_PIN_5,LOW);
		}

	}
}
