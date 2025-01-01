#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "systick.h"

int main(){

	int x = 0;
	uart1_tx_init();


	while(1)
	{
		systickDelayMs(1000);
		x++;
		printf("A second passed and current second is: %d \n\r", x);
	}
}
