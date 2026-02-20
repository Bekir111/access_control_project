//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//-NEED TO WRITE FUNCTIONS PROTOTYPES
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#ifndef F446RE_RCC_H_
#define F446RE_RCC_H_

#include <stdint.h>

//Macros for addresses
#define			RCC_BASE_ADDR			(0x40023800UL)

//RCC registers
typedef struct{

	uint32_t volatile CR;
	uint32_t volatile PLLCFGR;
	uint32_t volatile CFGR;
	uint32_t volatile CIR;
	uint32_t volatile AHB1RSTR;
	uint32_t volatile AHB2RSTR;
	uint32_t volatile AHB3RSTR;
	uint32_t RESERVED0;
	uint32_t volatile APB1RSTR;
	uint32_t volatile APB2RSTR;
	uint32_t RESERVED1[2];
	uint32_t volatile AHB1ENR;
	uint32_t volatile AHB2ENR;
	uint32_t volatile AHB3ENR;
	uint32_t RESERVED2;
	uint32_t volatile APB1ENR;
	uint32_t volatile APB2ENR;
	uint32_t RESERVED3[2];
	uint32_t volatile AHB1LPENR;
	uint32_t volatile AHB2LPENR;
	uint32_t volatile AHB3LPENR;
	uint32_t RESERVED4;
	uint32_t volatile APB1LPENR;
	uint32_t volatile APB2LPENR;
	uint32_t RESERVED5[2];
	uint32_t volatile BDCR;
	uint32_t volatile CSR;
	uint32_t RESERVED6[2];
	uint32_t volatile SSCGR;
	uint32_t volatile PLLI2SCFGR;
	uint32_t volatile PLLSAICFGR;
	uint32_t volatile DCKCFGR;
	uint32_t volatile CKGATENR;
	uint32_t volatile DCKCFGR2;
}RCC_typeDef;


//Macros for enabling GPIO's Clocks
#define			RCC						((RCC_typeDef*) RCC_BASE_ADDR)
#define			RCC_AHB1ENR_GPIOA		(1 << 0)
#define			RCC_AHB1ENR_GPIOB		(1 << 1)
#define			RCC_AHB1ENR_GPIOC		(1 << 2)

#endif /* F446RE_RCC_H_ */
