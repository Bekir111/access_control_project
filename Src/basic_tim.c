#include  "basic_tim_driver.h"

void TIM6_Init_5sec(){
	//Setting the prescaler
	TIM6->PSC = 16000 - 1; // System clock is 16Mhz for the prototyping. It will change for production code

	//Setting the auto reload register
	TIM6->ARR = 5000 - 1;

	//Clear bits for One-Pusle mode enable
	TIM6->CR1 &= ~(TIMx_CR1_OPM);
	//Set bits
	TIM6->CR1 |= TIMx_CR1_OPM;

	//Enabling Update interrupt
	//Clear bit
	TIM6->DIER &= ~(TIMx_DIER_UIE);
	//Set bit
	TIM6->DIER &= ~(TIMx_DIER_UIE);

}
void TIM7_Init_5sec(){
	;
}
uint8_t TIMx_UG_FLAG_CHECK(TIMx_typeDef* timer){
	return timer->SR & TIMx_SR_UIF;
}

