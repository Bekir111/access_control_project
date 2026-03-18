
#include <stdint.h>
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "uart_driver.h"
#include "basic_tim_driver.h"

static	QR_data_t	qr1_data;



int main(void)
{
	//Enable clock for GPIOA
	RCC_GPIOA_clock_enable();
	RCC_TIM6_clock_enable();

	//Set pin 5 at GPIOA MODER register as output
	GPIO_pin_mode(GPIOA, GPIO_PIN_5, GPOM_MODE);
	GPIO_pin_mode(GPIOA, GPIO_PIN_12, GPOM_MODE);

	//USART2 initialization
	UART2_init();
	//TIM6 initialization
	TIMx_Init_5sec(TIM6);

	while(1){

		if(UART_string_ready()){
			UART_string_ready_clear();
			if(QR_data_parse(uart_rx_buffer, &qr1_data)){
				GPIO_write_pin(GPIOA, GPIO_PIN_5,HIGH);
				TIMx_CNT_ENABLE(TIM6);
			}
		}

	}
}
