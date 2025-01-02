/*
 * exti.c
 *
 *  Created on: Jan 2, 2025
 *      Author: nguyen
 */
#include "exti.h"

void pi11_exti_init(void) //User button connect to PI11
{
	//Enable clk port I
	SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);

	//Set PI11 to input
	MODIFY_REG(GPIOI->MODER, GPIO_MODER_MODER11_0 | GPIO_MODER_MODER11_1, ~(GPIO_MODER_MODER11_0 | GPIO_MODER_MODER11_1));

	//Enable clk to SYSCFG
	SET_BIT(RCC->APB2ENR, RCC_APB2RSTR_SYSCFGRST);

	//Clear port selection for EXTI11
	CLEAR_BIT(SYSCFG->EXTICR[2], SYSCFG_EXTICR3_EXTI11);

	//Select port I for EXTI11
	SET_BIT(SYSCFG->EXTICR[2], SYSCFG_EXTICR3_EXTI11_PI);

	//Unmask EXTI11
	SET_BIT(EXTI->IMR, EXTI_IMR_MR11);

	//Select falling edge trigger
	SET_BIT(EXTI->FTSR, EXTI_FTSR_TR11);

	//Enable EXTI11 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

