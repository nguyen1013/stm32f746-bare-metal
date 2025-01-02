#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "systick.h"

int main(){

	uart1_tx_init();
	systick_1hz_interrupt();

	while(1)
	{

	}
}

static void systick_callback(void)
{
	printf("A second is passed...\n\r");
}

void SysTick_Handler(void)
{
	//Call back
	systick_callback();
}
