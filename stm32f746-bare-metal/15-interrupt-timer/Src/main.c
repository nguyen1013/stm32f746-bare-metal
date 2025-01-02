#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

static void tim1_update_callback(void);

int main(){

	uart1_tx_init();
	user_led_init();
	tim1_1hz_interrupt_init();

	while(1)
	{

	}

}

static void tim1_update_callback(void)
{
	led_toggle();
	printf("A second is just passed...\n\r");
}

void TIM1_UP_TIM10_IRQHandler(void) //defined in the startup file startup_stm32f746nghx
{
	//Check whether update interrupt is pending
	if (TIM1->SR & TIM_SR_UIF)
	{
		//Clear the update interrupt flag
		TIM1->SR &= ~TIM_SR_UIF;

		//Call back
		tim1_update_callback();
	}
}
