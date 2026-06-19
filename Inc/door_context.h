#ifndef DOOR_CONTEXT_H_
#define DOOR_CONTEXT_H_

#include "f446re_basic_tim.h"
#include "f446re_gpio.h"
#include "f446re_uart.h"

typedef struct{

	uint8_t rx_buffer[32];
	uint8_t string_ready;
	USARTx_typeDef *uart;
	TIMx_typeDef *tim;
	GPIOx_typeDef *gpio_periph;
	uint8_t gpio_pin;

}DoorContext_t;

extern DoorContext_t doorA, doorB;

#endif /* DOOR_CONTEXT_H_ */
