
#ifndef RCC_DRIVER_H_
#define RCC_DRIVER_H_

#include <stdint.h>
#include "f446re_rcc.h"

void RCC_GPIOA_clock_enable(void);
void RCC_GPIOB_clock_enable(void);
void RCC_GPIOC_clock_enable(void);
void RCC_GPIOD_clock_enable(void);
void RCC_UART2_clock_enable(void);
void RCC_UART4_clock_enable(void);
void RCC_UART5_clock_enable(void);
void RCC_TIM6_clock_enable(void);
void RCC_TIM7_clock_enable(void);
void RCC_I2C1_clock_enable(void);

#endif /* RCC_DRIVER_H_ */
