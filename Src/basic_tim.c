#include  "basic_tim_driver.h"
#include "arm_nvic_driver.h"

void TIMx_Init_5sec(TIMx_typeDef* timer){
	//Setting the prescaler
	timer->PSC = 16000 - 1; // System clock is 16Mhz for the prototyping. It will change for production code

	//Setting the auto reload register
	timer->ARR = 5000 - 1;

	//Clear bits for One-Pusle mode enable
	timer->CR1 &= ~(TIMx_CR1_OPM);
	//Set bits
	timer->CR1 |= TIMx_CR1_OPM;

	//Enabling Update interrupt
	//Clear bit
	timer->DIER &= ~(TIMx_DIER_UIE);
	//Set bit
	timer->DIER &= ~(TIMx_DIER_UIE);

	//NVIC enable interrupt for timer. For testing we will use only for TIM6
	NVIC_EnableIRQ(IRQ_TIM6);
	NVIC_SetPriority(IRQ_TIM6, 1);

}
uint8_t TIMx_UG_FLAG_CHECK(TIMx_typeDef* timer){
	return timer->SR & TIMx_SR_UIF;
}

