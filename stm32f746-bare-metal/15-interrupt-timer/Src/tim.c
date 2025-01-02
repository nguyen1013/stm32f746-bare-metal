/*
 * tim.c
 *
 *  Created on: Jan 2, 2025
 *      Author: nguyen
 */
#include "tim.h"

void tim1_1hz_init(void)
{
	//Enable clk to APB2
	SET_BIT(RCC->APB2ENR, RCC_APB2LPENR_TIM1LPEN);

	//Set the prescaler
	TIM1->PSC = 1600 -1; // 16000000/1600 = 10000

	//Set auto-reload value
	TIM1->ARR = 10000 - 1; // 10000/10000 = 1hz

	//Enable timer
	TIM1->CR2 |= TIM_CR1_CEN;
}

void tim1_1hz_interrupt_init(void)
{
	//Enable clk to TIM1
	SET_BIT(RCC->APB2ENR, RCC_APB2LPENR_TIM1LPEN);

	//Set the prescaler
	TIM1->PSC = 1600 -1; // 16000000/1600 = 10000

	//Set auto-reload value
	TIM1->ARR = 10000 - 1; // 10000/10000 = 1hz

	//Enable TIM1 update interrupt
	SET_BIT(TIM1->DIER, TIM_DIER_UIE);

	//Enable TIM1 update interrupt in NVIC
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	//Enable timer
	TIM1->CR1 |= TIM_CR1_CEN;

	//Force update generation
	TIM1->EGR |= TIM_EGR_UG;

}
