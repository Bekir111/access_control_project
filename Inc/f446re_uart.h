
#ifndef F446RE_UART_H_
#define F446RE_UART_H_

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

//Macros for receiving, transmitting or both
#define			USART_MODE_RX			1
#define			USART_MODE_TX			2
#define			USART_MODE_TX_RX		3

#endif /* F446RE_UART_H_ */
