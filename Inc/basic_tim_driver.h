
#ifndef BASIC_TIM_DRIVER_H_
#define BASIC_TIM_DRIVER_H_

#include "f446re_basic_tim.h"


void TIMx_Init_5sec(TIMx_typeDef* timer);
uint8_t TIMx_UG_FLAG_CHECK(TIMx_typeDef* timer);
void TIMx_CNT_ENABLE(TIMx_typeDef* timer);


#endif /* BASIC_TIM_DRIVER_H_ */
