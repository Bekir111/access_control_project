
#ifndef BASIC_TIM_DRIVER_H_
#define BASIC_TIM_DRIVER_H_

#include "f446re_basic_tim.h"


void TIM6_Init_5sec();
void TIM7_Init_5sec();
uint8_t TIMx_UG_FLAG_CHECK(TIMx_typeDef* timer);


#endif /* BASIC_TIM_DRIVER_H_ */
