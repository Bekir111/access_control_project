#include  "basic_tim_driver.h"
#include "arm_nvic_driver.h"
#include "gpio_driver.h"
#include "rcc_driver.h"

void TIM_Init_5sec(){
	//Enabling clock for TIM6 and TIM7
	RCC_TIM6_clock_enable();
	RCC_TIM7_clock_enable();

	//Setting the PSC and ARR register for 16Mhz to count for 5 seconds
	/*
	 * PSC = 16,000,000/(PSC + 1) => PSC = 16,000,000/16000 = 1KHz
	 * ARR is the register where you write how many ticks the counter should count
	 * If the PSC value is 1Khz that means the counter will count 1000 ticks for 1 second
	 * in that case for 5 seconds, the value of ARR would be 5000
	 * ARR = 5000
	 * That math will change for the PSC after production CPU clock for 45MHz. It will be
	 * PSC = 45,000,000/45000 = 1KHz
	 */
	//Setting the PSC and ARR registers value
	TIM7->PSC = 16000 - 1;
	TIM7->ARR = 5000 - 1;

	TIM6->PSC = 16000 - 1;
	TIM6->ARR = 5000 - 1;

	//Turning One-Pulse Mode. When Counts to 5000 the counter resets CNT bit to 0
	TIM6->CR1 |= TIMx_CR1_OPM;
	TIM7->CR1 |= TIMx_CR1_OPM;

	//Enabling an Update interrupt Event
	TIM6->DIER |= TIMx_DIER_UIE;
	TIM7->DIER |= TIMx_DIER_UIE;
	//Enabling just for hardware interrupt
	TIM6->CR1 |= TIMx_CR1_URS;
	TIM7->CR1 |= TIMx_CR1_URS;

	//Generating software update to load the waiting PSC value (16000-1) to the actual register
	TIM6->EGR = TIMx_EGR_UG;
	TIM7->EGR = TIMx_EGR_UG;

	//Enabling IRQ and setting priority
	NVIC_EnableIRQ(IRQ_TIM6);
	NVIC_SetPriority(IRQ_TIM6, 1);

	NVIC_EnableIRQ(IRQ_TIM7);
	NVIC_SetPriority(IRQ_TIM7, 1);


}

uint8_t TIMx_UG_FLAG_CHECK(TIMx_typeDef* timer){
	return timer->SR & TIMx_SR_UIF;
}

void TIMx_CNT_ENABLE(TIMx_typeDef* timer){
	    timer->CR1 |= TIMx_CR1_CEN;
}

void TIM6_DAC_IRQHandler(void){
	if(TIMx_UG_FLAG_CHECK(TIM6)){
		TIM6->SR &= ~(TIMx_SR_UIF);
		GPIO_write_pin(GPIOA, GPIO_PIN_5,LOW);
	}
}

void TIM7_IRQHandler(void){
	if(TIMx_UG_FLAG_CHECK(TIM7)){
			TIM7->SR &= ~(TIMx_SR_UIF);
			GPIO_write_pin(GPIOA, GPIO_PIN_5,LOW);
	}
}

