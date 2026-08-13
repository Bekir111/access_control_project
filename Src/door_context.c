#include "gpio_driver.h"
#include "door_context.h"
#include "i2c_driver.h"
#include "basic_tim_driver.h"
#include "uart_driver.h"
#include "ds3231.h"

QR_data_t qr_data;
DS3231_data_t time;

void Process_Door(DoorContext_t *door){
	if(door->string_ready){
		door->string_ready = 0;
		if(!(QR_data_parse_check(door->rx_buffer, &qr_data))){
			Denied_Access(door);
			return ;
		}

		DS3231_GetTime(&time);

		if(!(QR_Validate(&qr_data, &time))){
			Denied_Access(door);
			return ;
		}

		Granted_Access(door);
	}
}

void Denied_Access(DoorContext_t *door){
	TIMx_CNT_DISABLE(door->tim);
	GPIO_write_pin(door->gpio_periph, door->gpio_denied, LOW);
	GPIO_write_pin(door->gpio_periph, door->gpio_granted, LOW);

	GPIO_write_pin(door->gpio_periph, door->gpio_denied, HIGH);

	door->tim->SR &= ~(TIMx_SR_UIF);
	door->tim->CNT = 0;
	TIMx_CNT_ENABLE(door->tim);
}

void Granted_Access(DoorContext_t *door){
	TIMx_CNT_DISABLE(door->tim);
	GPIO_write_pin(door->gpio_periph, door->gpio_denied, LOW);
	GPIO_write_pin(door->gpio_periph, door->gpio_granted, LOW);

	GPIO_write_pin(door->gpio_periph, door->gpio_granted, HIGH);

	door->tim->SR &= ~(TIMx_SR_UIF);
	door->tim->CNT = 0;
	TIMx_CNT_ENABLE(door->tim);
}

uint8_t QR_Validate(QR_data_t *qr, DS3231_data_t *time){
	if (qr->day != time->day || qr->month != time->month || qr->year != time->year){
		return 0;
	}
	//qr->day != time->day
	return 1;
}




