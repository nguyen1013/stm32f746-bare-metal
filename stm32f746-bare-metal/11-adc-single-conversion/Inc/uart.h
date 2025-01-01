#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f7xx.h"

void uart1_tx_init(void);
void uart1_rxtx_init(void);
uint8_t uart_read(USART_TypeDef *USARTx);

#endif /* UART_H_ */
