
#include"uart_driver.h"
#include "rcc_driver.h"
#include "gpio_driver.h"

void UART_enable(USARTx_typeDef* USARTx){
	//UART enable bit clear
	USARTx->CR1 &= ~(USART_EN);

	//UART enable bit set
	USARTx->CR1 |= (USART_EN);
}

void UART_RXIE_enable(USARTx_typeDef* USARTx){
	//Clear RXIE bits
	USARTx->CR1 &= ~(UART_CR1_RXNEIE);

	//Set RXIE bits
	USARTx->CR1 |= (UART_CR1_RXNEIE);
}


void UART_mode(USARTx_typeDef* USARTx, uint8_t TxRx){

	//Clear bits for Receiver enable
	USARTx->CR1 &= ~(TxRx << 2);

	//Set bits for Receiver enable
	USARTx->CR1 |= (TxRx << 2);

}

void UART_set_baud_rate(USARTx_typeDef* USARTx, uint32_t baudRate, uint32_t periphClock){
	USARTx->BRR = (uint16_t)( (periphClock + (baudRate/2)) / baudRate);
}

uint8_t UART_check_RXNE_flag(USARTx_typeDef* USARTx){

	return 0;
}


uint8_t UART_data_return(USARTx_typeDef* USARTx){

	return 0;
}

void UART2_init(void){
		//UART2 clock enable
		RCC_UART2_clock_enable();

		//Set PA2 as AF mode
		GPIO_pin_mode(GPIOA, GPIO_PIN_2, AF_MODE);
		//Set PA3 as AF mode
		GPIO_pin_mode(GPIOA, GPIO_PIN_3, AF_MODE);

		//AF selection for PA2
		GPIO_AF_selection_low(GPIOA, GPIO_PIN_2, AF7);

		//AF selection for PA3
		GPIO_AF_selection_low(GPIOA, GPIO_PIN_3, AF7);
		//Pull up on RX to prevent floating pin. UART RX idle is HIGH
		GPIO_pull_up(GPIOA, GPIO_PIN_3);

		//Enable UART2
		UART_enable(USART2);

		//Enable Receive interrupt
		UART_RXIE_enable(USART2);

		//Set UART to Receive mode only
		UART_mode(USART2, USART_MODE_RX);

		UART_set_baud_rate(USART2, BAUDE_RATE_115200, PERIPH_CLOCK_TEST);

}

