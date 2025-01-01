/*
 * systick.c
 *
 *  Created on: Jan 1, 2025
 *      Author: nguyen
 */
#include "systick.h"

#define SYSTICK_LOAD_VALUE 			16000 // 1ms
#define CTRL_EN						(1U<<0)
#define COUNTFLAG						(1U<<16)

void systickDelayMs(int delay)
{
	//Reload the number of clocks per millisecond
	SysTick->LOAD = SYSTICK_LOAD_VALUE;

	//Clear SYST_CVR(current value register)
	SysTick->VAL = 0;

	//Enable and set clock source(Control and Status Register)
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

	for (int i = 0; i<delay; i++)
	{
		// Waiting until COUNTFLAG is set
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {}
	}

	//Clear SYST_CSR
	SysTick->CTRL = 0;
}

