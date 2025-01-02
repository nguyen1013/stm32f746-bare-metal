#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"

int main(){

	user_led_init();
	uart1_tx_interrupt_init();

	while(1)
	{

	}
}

static void uart_tx_callback(void)
{
	// Write value into TDR
	USART1->TDR = 'A';
}

void USART1_IRQHandler(void)
{
	//Check if TXE interrupt occur
	if (USART1->ISR & USART_ISR_TXE)
	{
		//Callback
		uart_tx_callback();
	}
}
