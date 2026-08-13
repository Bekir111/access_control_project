#ifndef DOOR_CONTEXT_H_
#define DOOR_CONTEXT_H_

#include "f446re_basic_tim.h"
#include "f446re_gpio.h"
#include "f446re_uart.h"
#include "ds3231.h"

typedef struct{

	uint8_t rx_buffer[32];
	uint8_t rx_index;
	uint8_t string_ready;
	USARTx_typeDef *uart;
	TIMx_typeDef *tim;
	GPIOx_typeDef *gpio_periph;
	uint8_t gpio_denied;
	uint8_t gpio_granted;

}DoorContext_t;

extern DoorContext_t doorA, doorB;

void Process_Door(DoorContext_t *door);
void Denied_Access(DoorContext_t *door);
void Granted_Access(DoorContext_t *door);
uint8_t QR_Validate(QR_data_t *qr, DS3231_data_t *time);
#endif /* DOOR_CONTEXT_H_ */
