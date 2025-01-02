#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"

static void uart_rx_callback(void);

char ch;

int main(){


	user_led_init();
	uart1_rx_interrupt_init();

	while(1)
	{
		switch(ch)
		{
			case 'o':
				led_off();
				break;
			case 'i':
				led_on();
				break;
			case 't':
				led_toggle();
				ch = 0; //Reset ch to prevent led continously toggled due to ch = 't'
				break;
			default:
				break;
		}
	}
}

static void uart_rx_callback(void)
{
	ch = (READ_BIT(USART1->RDR, USART_RDR_RDR)& 0xFFU);;
}

void USART1_IRQHandler(void)
{
	//Check if rxne interrupt occur
	if (USART1->ISR & USART_ISR_RXNE)
	{
		//callback
		uart_rx_callback();
	}
}
