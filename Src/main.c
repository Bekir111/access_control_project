
#include <stdint.h>
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "uart_driver.h"
#include "basic_tim_driver.h"
#include "i2c_driver.h"
#include "door_context.h"

static	QR_data_t	qr1_data;

DoorContext_t doorA = {
		.uart = UART4,
		.tim = TIM6,
		.string_ready = 0,
		.gpio_periph = GPIOC,
		.gpio_pin = GPIO_PIN_6
	};

DoorContext_t doorB = {
		.uart = UART5,
		.tim = TIM7,
		.string_ready = 0,
		.gpio_periph = GPIOC,
		.gpio_pin = GPIO_PIN_7
	};

int main(void)
{

	//GPIO's initialization
	GPIOs_init();

	//USART2 initialization
	UART2_init();
	//UART4 and UART5 initialization
	UART5_init();
	UART4_init();

	//TIM initialization
	TIM_Init_5sec();

	//I2C1 initialization
	I2C_init(I2C1);

	//Testing write method for I2C
	I2C_write(I2C1, 26, 5, 7, 14, 1);

	while(1){

		I2C_multiple_read(I2C1,7,rtc_buffer);

		if(UART_string_ready()){
			UART_string_ready_clear();
			if(QR_data_parse(uart_rx_buffer, &qr1_data)){
				GPIO_write_pin(GPIOA, GPIO_PIN_5,HIGH);
				TIMx_CNT_ENABLE(TIM6);
			}
		}

	}
}
