#include  "basic_tim_driver.h"

void TIM_counter_enable(TIMx_typeDef* timer){
	//Clear
	timer->CR1 &= ~(TIMx_CR1_CEN);
	//Set
	timer->CR1 |= TIMx_CR1_CEN;
}
