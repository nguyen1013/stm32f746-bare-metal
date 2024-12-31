#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"

int main(){

	int x;
	uart1_tx_init();

	while(1)
	{
		printf("Hello from STM32F746\n\r");
		for(int i=0;i<9000;i++)
		{
			x++;
		}
	}
}