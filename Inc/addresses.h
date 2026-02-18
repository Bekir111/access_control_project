
#ifndef ADDRESSES_H_
#define ADDRESSES_H_

#include <stdint.h>

//Peripherals base and bus addresses
#define 	PERIPH_BASE				0x40000000UL
#define 	APB1_BASE				(PERIPH_BASE)
#define 	APB2_BASE				(PERIPH_BASE + 0x00010000UL)
#define 	AHB1_BASE				(PERIPH_BASE + 0x00020000UL)

//RCC base address and RCC registers
#define		RCC_BASE				(AHB1_BASE + 0x3800UL)
#define		RCC_AHB1ENR				(RCC_BASE + 0x30UL)
#define		RCC_APB1ENR				(RCC_BASE + 0x40UL)
#define		RCC_APB2ENR				(RCC_BASE + 0x44UL)

//GPIO base addresses
#define 	GPIOA_BASE				(AHB1_BASE)
#define 	GPIOB_BASE				(AHB1_BASE + 0x0400UL)
#define 	GPIOC_BASE				(AHB1_BASE + 0x0800UL)

//GPIO registers offsets
#define		GPIO_MODER_OFFSET		0x00UL
#define		GPIO_OTYPER_OFFSET		0x04UL
#define		GPIO_OSPEEDR_OFFSET		0x08UL
#define		GPIO_PUPDR_OFFSET		0x0CUL
#define		GPIO_IDR_OFFSET			0x10UL
#define		GPIO_ODR_OFFSET			0x14UL
#define		GPIO_BSRR_OFFSET		0x18UL
#define		GPIO_LCKR_OFFSET		0x1CUL
#define		GPIO_AFRL_OFFSET		0x20UL
#define		GPIO_AFRH_OFFSET		0x24UL


#endif /* ADDRESSES_H_ */
