
#ifndef F446RE_GPIO_H_
#define F446RE_GPIO_H_

#include	<stdint.h>

//Base addresses
#define		AHB1_PERIPH_BASE		(0x40020000UL)
#define		GPIOA_PERIPH			(AHB1_PERIPH_BASE)
#define		GPIOB_PERIPH			(AHB1_PERIPH_BASE + 0x0400UL)
#define		GPIOC_PERIPH			(AHB1_PERIPH_BASE + 0x0800UL)


//GPIO's register
typedef struct{
	uint32_t volatile MODER;
	uint32_t volatile OTYPER;
	uint32_t volatile OSPEEDER;
	uint32_t volatile PUPDR;
	uint32_t volatile IDR;
	uint32_t volatile ODR;
	uint32_t volatile BSRR;
	uint32_t volatile LCKR;
	uint32_t volatile AFRL;
	uint32_t volatile AFRH;

}GPIOx_typeDef;

//Pointers to GPIO's peripherals
#define		GPIOA				((GPIOx_typeDef*) GPIOA_PERIPH)
#define		GPIOB				((GPIOx_typeDef*) GPIOB_PERIPH)
#define		GPIOC				((GPIOx_typeDef*) GPIOC_PERIPH)

//Pin numbers
#define 	GPIO_PIN_1			1
#define 	GPIO_PIN_2			2
#define 	GPIO_PIN_3			3
#define 	GPIO_PIN_4			4
#define 	GPIO_PIN_5			5
#define 	GPIO_PIN_6			6
#define 	GPIO_PIN_7			7
#define 	GPIO_PIN_8			8
#define 	GPIO_PIN_9			9
#define 	GPIO_PIN_10			10
#define 	GPIO_PIN_11			11
#define 	GPIO_PIN_12			12
#define 	GPIO_PIN_13			13
#define 	GPIO_PIN_14			14
#define 	GPIO_PIN_15			15

//GPIO's states
#define 	HIGH				1
#define		LOW					0


//GPIO's direction mode
#define		INPUT_MODE			(0x0)
#define		GPOM_MODE			(0x1)
#define		AF_MODE				(0x2)
#define		ANALOG_MODE			(0x3)

//GPIO's output type
#define 	OTYPE_PP     		0x0  // Push-pull
#define 	OTYPE_OD     		0x1  // Open-drain

//GPIO's Pull-up, pull-down values
#define 	PUPD_NONE    		0x00
#define 	PUPD_PULLUP  		0x01
#define 	PUPD_PULLDOWN 		0x02

//Functions prototypes for GPIO's
void GPIO_init();


#endif /* F446RE_GPIO_H_ */
