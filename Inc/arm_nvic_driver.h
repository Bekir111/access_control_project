
#ifndef ARM_NVIC_DRIVER_H_
#define ARM_NVIC_DRIVER_H_

#include "arm_nvic.h"

void NVIC_EnableIRQ(uint8_t irq);
void NVIC_SetPriority(uint8_t irq, uint8_t priority);

#endif /* ARM_NVIC_DRIVER_H_ */
