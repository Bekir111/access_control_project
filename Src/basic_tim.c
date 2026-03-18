#include  "basic_tim_driver.h"
#include "arm_nvic_driver.h"
#include "gpio_driver.h"

void TIMx_Init_5sec(TIMx_typeDef* timer){

	    timer->PSC = 16000 - 1;
	    timer->ARR = 5000 - 1;

	    timer->CR1 |= TIMx_CR1_OPM;

	    timer->DIER |= TIMx_DIER_UIE;

	    timer->CR1 |= TIMx_CR1_URS;

	    timer->EGR = TIMx_EGR_UG;
	    timer->SR &= ~(TIMx_SR_UIF);

	    NVIC_EnableIRQ(IRQ_TIM6);
	    NVIC_SetPriority(IRQ_TIM6, 1);

}

uint8_t TIMx_UG_FLAG_CHECK(TIMx_typeDef* timer){
	return timer->SR & TIMx_SR_UIF;
}

void TIM6_CNT_ENABLE(){
	    TIM6->CR1 |= TIMx_CR1_CEN;
}

void TIM6_DAC_IRQHandler(void){
	if(TIMx_UG_FLAG_CHECK(TIM6)){
		TIM6->SR &= ~(TIMx_SR_UIF);
		GPIO_write_pin(GPIOA, GPIO_PIN_5,LOW);
	}
}

