
#include"uart_driver.h"
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "arm_nvic.h"
#include "arm_nvic_driver.h"

				uint8_t		uart_rx_buffer[32];
volatile		uint8_t		uart_index = 0;
volatile		uint8_t		uart_string_ready = 0;


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

void UART_recieve_handler(USARTx_typeDef* USARTx){
	//Check for the flag

		uint8_t ch = UART_data_return(USARTx);

		if(ch == '\r' || ch == '\n'){
			uart_rx_buffer[uart_index] = '\0';  // Add null terminator
			uart_string_ready = 1;                 // Set flag
            uart_index = 0;
		}
		else{
			 uart_rx_buffer[uart_index] = ch;
			 uart_index++;
		}

}

uint8_t UART_string_ready(){
	return uart_string_ready;
}

void UART_string_ready_clear(){
	uart_string_ready = 0;
}

uint8_t UART_check_RXNE_flag(USARTx_typeDef* USARTx){
	return USARTx->SR & (USART_SR_RXNE);
}


uint8_t UART_data_return(USARTx_typeDef* USARTx){

	return USARTx->DR;

}

uint8_t QR_data_parse(const uint8_t* buffer, QR_data_t* qr_data){
	//Checking the length of the string from start to "TU_STOL"
	//20:02:2026:13:02:TU_STOL (example)
	uint8_t len = 0;
	while (buffer[len] != '\0') len++;
	if (len < 17) {
		return 0;
	}

	//Parsing the days
	qr_data->day = ((buffer[0] - '0') * 10) + (buffer[1] - '0');
	/*
	 * -----EXPLAINING PARSING CALCULATION-------
	 * Decimal representation of the character '0' is 48
	 * Every next character after '0' is +1 for example:
	 * Decimal representation of '1' is 49, '2' is 50 and so on
	 * So to convert the character into number i use this calculation
	 * I will use the (example):
	 * '20' -> '2' and '0'
	 * ('2'(50) - '0'(48)) * 10 => 20
	 * ('0'(48) - '0'(48)) 		=> 	0
	 * Thats how parsing is done
	 */
	//Parsing the month
	qr_data->month = ((buffer[3] - '0') * 10) + (buffer[4] - '0');
	//Parsing the year
	qr_data->year = ((buffer[6] - '0') * 1000) 	+
					((buffer[7] - '0') * 100 )	+
					((buffer[8] - '0') * 10  )	+
					((buffer[9] - '0')   	 );
	//Parsing hours
	qr_data->hour = ((buffer[11] - '0') * 10) + (buffer[12] - '0');

	//Parsing minutes
	qr_data->hour = ((buffer[14] - '0') * 10) + (buffer[15] - '0');

	return 1;

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
		//GPIO_pull_up(GPIOA, GPIO_PIN_3);

		//Enable Receive interrupt
		UART_RXIE_enable(USART2);

		//Set UART to Receive mode only
		UART_mode(USART2, USART_MODE_RX);

		UART_set_baud_rate(USART2, BAUDE_RATE_115200, PERIPH_CLOCK_TEST);

		UART_enable(USART2);

		NVIC_EnableIRQ(IRQ_USART2);
		NVIC_SetPriority(IRQ_USART2, 0);

}

void USART2_IRQHandler(void){
	if(UART_check_RXNE_flag(USART2)){
		UART_recieve_handler(USART2);
	}

}
