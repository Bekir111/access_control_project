
#ifndef ARM_NVIC_H_
#define ARM_NVIC_H_
#include <stdint.h>

#define			NVIC_BASE_ISER_ADDR		0xE000E100UL
#define			NVIC_BASE_IPR_ADDR		0xE000E400UL
#define			IPR0_ADDR				NVIC_BASE_IPR_ADDR


//Address for Interrupt priority register

#define			NVIC_IPR_BASE_ADDR		0xE000E400UL

//Macros for positions in vector table for the peripherals
#define			IRQ_USART2				38
#define			IRQ_UART4				52
#define			IRQ_UART5				53
#define			IRQ_TIM6				54
#define			IRQ_TIM7				55

#endif /* ARM_NVIC_H_ */
