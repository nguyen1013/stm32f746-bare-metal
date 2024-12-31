#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"

int main(){

	char ch;
	user_led_init();
	uart1_rxtx_init();

	while(1)
	{
		ch = uart_read(USART1);
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
				break;
			default:
				break;
		}

	}
}
