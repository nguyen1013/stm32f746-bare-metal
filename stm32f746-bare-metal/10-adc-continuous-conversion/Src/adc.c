/*
 * adc.c
 *
 *  Created on: Jan 1, 2025
 *      Author: nguyen
 */
#include "adc.h"

void pf10_adc3_init(void)
{
	/*********Configure ADC GPIO pin**********/
	//Enable clk GPIOF
	SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);

	//Set PF10 to analog mode
	SET_BIT(GPIOF->MODER, GPIO_MODER_MODER10_0 | GPIO_MODER_MODER10_1);

	/*********Configure ADC module**********/
	//Enable clk ADC module
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN);

	//Set conversion to continous
	SET_BIT(ADC3->CR2, ADC_CR2_CONT);

	//Set sequence length
	MODIFY_REG(ADC3->SQR1, ADC_SQR1_L_0 | ADC_SQR1_L_1 | ADC_SQR1_L_2 | ADC_SQR1_L_3, ADC_SQR1_L_0);

	//Set adc channel
	MODIFY_REG(ADC3->SQR3, ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_4, ADC_SQR3_SQ1_3);

	//Enable adc module
	SET_BIT(ADC3->CR2, ADC_CR2_ADON);

	//Start conversion
	SET_BIT(ADC3->CR2, ADC_CR2_SWSTART);
}

uint32_t adc_get_data(void)
{
	//Waiting for EOC (end of conversion flag)
	while(!(ADC3->SR & ADC_SR_EOC)){}

	//Read value
	return (ADC3->DR);
}

