
#include"uart_driver.h"
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "arm_nvic.h"
#include "arm_nvic_driver.h"
#include "door_context.h"




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

void UART_recieve_handler(DoorContext_t* door){

		uint8_t ch = UART_data_return(door->uart);

		if(ch == '\r' || ch == '\n'){
			door->rx_buffer[door->rx_index] = '\0';  // Add null terminator
			door->string_ready = 1;                 // Set flag
            door->rx_index = 0;
		}
		else{
			door->rx_buffer[door->rx_index] = ch;
			door->rx_index++;
		}

}

uint8_t UART_check_RXNE_flag(USARTx_typeDef* USARTx){
	return USARTx->SR & (USART_SR_RXNE);
}


uint8_t UART_data_return(USARTx_typeDef* USARTx){

	return USARTx->DR;

}

uint8_t Is_Digit(uint8_t c){
    return (c >= '0' && c <= '9');
}

uint8_t QR_data_parse(const uint8_t* buffer, QR_data_t* qr_data){
	//Checking the length of the string from start to "TU_STOL"
	//20:02:2026:13:02:TU_STOL (example)
	uint8_t len = 0;
	while (buffer[len] != '\0') len++;
	if (len < 17) {
		return 0;
	}

	//Check for ':' symbol to be on the expected positions
	if(buffer[2] != ':' || buffer[5] != ':' || buffer[10] != ':' ||
	       buffer[13] != ':' || buffer[16] != ':') return 0;

	//Checking if the collected characters are really numbers from 0 to 9.
	uint8_t digit_positions[] = {0,1,3,4,6,7,8,9,11,12,14,15};
	for(uint8_t i = 0; i < 12; i++){
		if(!Is_Digit(buffer[digit_positions[i]])){
			return 0;
		}
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
	qr_data->minute = ((buffer[14] - '0') * 10) + (buffer[15] - '0');

	return 1;

}

void UART4_init(void){

		//Enabling clock for peripheral C
		RCC_GPIOC_clock_enable();

		//UART2 clock enable
		RCC_UART4_clock_enable();

		//Set PA2 as AF mode
		GPIO_pin_mode(GPIOC, GPIO_PIN_10, AF_MODE);
			//Set PA3 as AF mode
		GPIO_pin_mode(GPIOC, GPIO_PIN_11, AF_MODE);

		//AF selection for PA2
		GPIO_AF_selection_low(GPIOC, GPIO_PIN_10, AF8);

		//AF selection for PA3
		GPIO_AF_selection_low(GPIOC, GPIO_PIN_11, AF8);
		//Pull up on RX to prevent floating pin. UART RX idle is HIGH
		//GPIO_pull_up(GPIOA, GPIO_PIN_3);

		//Enable Receive interrupt
		UART_RXIE_enable(UART4);

		//Set UART to Receive mode only
		UART_mode(UART4, USART_MODE_RX);

		UART_set_baud_rate(UART4, BAUDE_RATE_115200, PERIPH_CLOCK_TEST);

		UART_enable(UART4);

		NVIC_EnableIRQ(IRQ_UART4);
		NVIC_SetPriority(IRQ_UART4, 0);
}

void UART5_init(void){

		//Enabling clock for peripheral D
		RCC_GPIOD_clock_enable();
		//UART2 clock enable
		RCC_UART5_clock_enable();

		//Set PA2 as AF mode
		GPIO_pin_mode(GPIOD, GPIO_PIN_2, AF_MODE);
			//Set PA3 as AF mode
		GPIO_pin_mode(GPIOC, GPIO_PIN_12, AF_MODE);

		//AF selection for PA2
		GPIO_AF_selection_low(GPIOD, GPIO_PIN_2, AF8);

		//AF selection for PA3
		GPIO_AF_selection_low(GPIOC, GPIO_PIN_12, AF8);
		//Pull up on RX to prevent floating pin. UART RX idle is HIGH
		//GPIO_pull_up(GPIOA, GPIO_PIN_3);

		//Enable Receive interrupt
		UART_RXIE_enable(UART5);

		//Set UART to Receive mode only
		UART_mode(UART5, USART_MODE_RX);

		UART_set_baud_rate(UART5, BAUDE_RATE_115200, PERIPH_CLOCK_TEST);

		UART_enable(UART5);

		NVIC_EnableIRQ(IRQ_UART5);
		NVIC_SetPriority(IRQ_UART5, 0);
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

void UART5_IRQHandler(){
	if(UART_check_RXNE_flag(UART5)){
		UART_recieve_handler(&doorB);
	}
}
void UART4_IRQHandler(){
	if(UART_check_RXNE_flag(UART4)){
		UART_recieve_handler(&doorA);
	}
}
/*
void USART2_IRQHandler(void){
	if(UART_check_RXNE_flag(USART2)){
		UART_recieve_handler(USART2);
	}

}
*/
