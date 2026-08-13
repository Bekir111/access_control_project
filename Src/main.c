
#include <stdint.h>
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "uart_driver.h"
#include "basic_tim_driver.h"
#include "i2c_driver.h"
#include "door_context.h"



DoorContext_t doorA = {
		.uart = UART4,
		.tim = TIM6,
		.string_ready = 0,
		.gpio_periph = GPIOC,
		.gpio_granted = GPIO_PIN_6,
		.gpio_denied = GPIO_PIN_7
	};

DoorContext_t doorB = {
		.uart = UART5,
		.tim = TIM7,
		.string_ready = 0,
		.gpio_periph = GPIOC,
		.gpio_granted = GPIO_PIN_8,
		.gpio_denied = GPIO_PIN_9

	};

int main(void)
{
	//GPIO's initialization
	GPIOs_init();

	//UART4 and UART5 initialization
	UART5_init();
	UART4_init();

	//TIM initialization
	TIM_Init_5sec();

	//I2C1 initialization
	I2C_init(I2C1);

	//Testing write method for I2C
	I2C_write(I2C1, 26, 7, 22, 10, 12);

	while(1){

		Process_Door(&doorA);
		Process_Door(&doorB);

	}

}
