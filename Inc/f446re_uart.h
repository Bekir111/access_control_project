
#ifndef F446RE_UART_H_
#define F446RE_UART_H_

#include <stdint.h>

#define 		APB1_BASE_ADDR			0x40000000UL
#define 		USART2_ADDR				(APB1_BASE_ADDR + 0x4400UL)
#define 		USART3_ADDR				(APB1_BASE_ADDR + 0x4800UL)

typedef struct{
	uint32_t volatile SR;
	uint32_t volatile DR;
	uint32_t volatile BRR;
	uint32_t volatile CR1;
	uint32_t volatile CR2;
	uint32_t volatile CR3;
	uint32_t volatile GTPR;
}USARTx_typeDef;


//Pointers to USART peripherals
#define			USART2					((USARTx_typeDef*)USART2_ADDR)
#define			USART3					((USARTx_typeDef*)USART3_ADDR)


//UART Enable macro
#define			USART_EN				(1U<<13)
//Macros for receiving, transmitting or both
#define			USART_MODE_RX			1
#define			USART_MODE_TX			2
#define			USART_MODE_TX_RX		3

//Macros for interrupts
#define 		UART_CR1_RXNEIE			(1U<<5)
#define 		UART_CR1_IDLEIE			(1U<<4)
#define 		UART_CR1_TCIE			(1U<<6)
#define 		UART_CR1_TXEIE			(1U<<7)
#define 		UART_CR1_PEIE			(1U<<8)


//Status register macros
#define			USART_SR_RXNE			(1U<<5)
//Baud rate macros
#define			BAUDE_RATE_115200		115200

//Peripheral clock used in prototyping
#define			PERIPH_CLOCK_TEST		16000000


extern 			uint8_t					uart_rx_buffer[32];

typedef struct{
	uint8_t 	day;
	uint8_t 	month;
	uint16_t 	year;
	uint8_t		hour;
	uint8_t		minute;
	uint8_t		reader_validate[12];

}QR_data_t;


#endif /* F446RE_UART_H_ */
