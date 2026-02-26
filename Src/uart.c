
#include"uart_driver.h"
#include "rcc_driver.h"
#include "gpio_driver.h"





uint8_t UART_data_return(USARTx_typeDef* USARTx){

	return 0;
}

void UART_mode(USARTx_typeDef* USARTx, uint8_t TxRx){

	//Clear bits for Receiver enable
	USARTx->CR1 &= ~(TxRx << 2);

	//Set bits for Receiver enable
	USARTx->CR1 |= (TxRx << 2);

}

uint8_t UART_check_RXNE_flag(USARTx_typeDef* USARTx){

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


}

