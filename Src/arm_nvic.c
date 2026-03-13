#include "arm_nvic_driver.h"
#include <stdint.h>
#include "arm_nvic.h"
void NVIC_EnableIRQ(uint8_t irq){
	volatile uint32_t* iser;
	if(irq < 32){
		iser = (uint32_t*)NVIC_BASE_ISER_ADDR;
		*iser = (1 << irq);
	}
	else if(irq < 64){
		iser = (uint32_t*)(NVIC_BASE_ISER_ADDR + 0x04);
		*iser = (1 << (irq - 32));
	}
}
void NVIC_SetPriority(uint8_t irq, uint8_t priority){
	uint8_t* ipr = (uint8_t*) (NVIC_BASE_IPR_ADDR + irq);
	*ipr = (priority << 4);
}


