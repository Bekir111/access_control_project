
#ifndef F446RE_BASIC_TIM_H_
#define F446RE_BASIC_TIM_H_
#include <stdint.h>

#define 		APB1_BASE_ADDR			0x40000000UL
#define			TIM6_BASE_ADDR			(APB1_BASE_ADDR + 0x00001000UL)
#define			TIM7_BASE_ADDR			(APB1_BASE_ADDR + 0x00001400UL)


typedef struct{
	uint16_t volatile CR1;
	uint16_t volatile CR2;
	uint16_t volatile RESERVED0;
	uint16_t volatile DIER;
	uint16_t volatile SR;
	uint16_t volatile EGR;
	uint16_t volatile RESERVED1[3];
	uint16_t volatile CNT;
	uint16_t volatile PSC;
	uint16_t volatile ARR;
}TIMx_typeDef;


#define			TIM6					((TIMx_typeDef*)TIM6_BASE_ADDR)
#define			TIM7					((TIMx_typeDef*)TIM7_BASE_ADDR)

//CR1 bits
#define			TIMx_CR1_CEN			(0x1UL<<0)
#define			TIMx_CR1_UDIS			(0x1UL<<1)
#define			TIMx_CR1_URS			(0x1UL<<2)
#define			TIMx_CR1_OPM			(0x1UL<<3)
#define			TIMx_CR1_ARPE			(0x1UL<<7)

//DIER bits
#define			TIMx_DIER_UIE			(0x1UL<<0)

//SR bits
#define			TIMx_SR_UIF				(0x1UL<<0)

//EGR bits
#define			TIMx_EGR_UG				(0x1UL<<0)


#endif /* F446RE_BASIC_TIM_H_ */
