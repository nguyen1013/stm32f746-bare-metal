#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

int main(){

	int x = 0;

	uart1_tx_init();
	tim1_1hz_init();

	while(1)
	{
		// waiting for UIF
		while (!(TIM1->SR & TIM_SR_UIF)){}

		//Clear UIF
		TIM1->SR &= ~TIM_SR_UIF;

		x++;
		printf("A second passed and current second is: %d \n\r", x);
	}
}
