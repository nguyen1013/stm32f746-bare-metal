#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"

int main(){

	int sensor_value;

	uart1_tx_init();
	pf10_adc3_init();

	while(1)
	{
		start_conversion();
		sensor_value = adc_get_data();
		printf("Sensor value is: %d\n\r", sensor_value);
	}
}
