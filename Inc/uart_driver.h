
#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "f446re_uart.h"

void UART_mode(USARTx_typeDef* USARTx, uint8_t TxRx);
void UART_enable(USARTx_typeDef* USARTx);
void UART_RXIE_enable(USARTx_typeDef* USARTx);
void UART2_init(void);
void UART_set_baud_rate(USARTx_typeDef* USARTx, uint32_t baudRate, uint32_t periphClock);
void UART_recieve_handler(USARTx_typeDef* USARTx);
uint8_t UART_check_RXNE_flag(USARTx_typeDef* USARTx);
uint8_t UART_data_return(USARTx_typeDef* USARTx);

#endif /* UART_DRIVER_H_ */
