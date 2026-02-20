
#ifndef RCC_DRIVER_H_
#define RCC_DRIVER_H_

#include <stdint.h>
#include "f446re_rcc.h"

void RCC_GPIOA_clock_enable(void);
void RCC_GPIOB_clock_enable(void);
void RCC_GPIOC_clock_enable(void);

#endif /* RCC_DRIVER_H_ */
