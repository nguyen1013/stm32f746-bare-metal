#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

static void user_btn_callback(void);

int main(){

	uart1_tx_init();
	user_led_init();

	pi11_exti_init();

	while(1){}

}

static void user_btn_callback(void)
{
	led_toggle();
	printf("User button is pressed...\n\r");
}

void EXTI15_10_IRQHandler(void) //defined in the startup file startup_stm32f746nghx
{
	if (EXTI->PR & EXTI_PR_PR11)
	{
		//Clear PR flag
		SET_BIT(EXTI->PR, EXTI_PR_PR11);

		//Call back
		user_btn_callback();
	}
}
