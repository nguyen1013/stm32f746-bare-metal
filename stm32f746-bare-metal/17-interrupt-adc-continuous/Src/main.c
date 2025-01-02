#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"

static void adc_conversion_callback(void);

int sensor_value;

int main(){

	uart1_tx_init();
	pf10_adc3_interrupt_init();

	while(1)
	{

	}
}

static void adc_conversion_callback(void)
{
	sensor_value = ADC3->DR;
	printf("Sensor value is: %d\n\r", sensor_value);
}

void ADC_IRQHandler(void)
{
	//Check if end-of-conversion interrupt occur
	if (ADC3->SR & ADC_SR_EOC){
		//Clear EOC flag
		ADC3->SR &= ~ADC_SR_EOC;

		//Callback
		adc_conversion_callback();
	}
}
