#include "stm32f7xx.h"

#define GPIOI_CLK_EN			(1U<<8)
#define USER_LED1_MODER			(1U<<2)
#define USER_LED1 				(1U<<1)
#define PIN_11					(1U<<11)
#define BTN_PIN					PIN_11

int main(void)
{
	RCC->AHB1ENR |= GPIOI_CLK_EN;
	GPIOI->MODER |= USER_LED1_MODER;

	GPIOI->MODER &= ~(1U<<22);
	GPIOI->MODER &= ~(1U<<23);

	while(1){
		if (GPIOI->IDR & BTN_PIN ) {
			GPIOI->BSRR = 1U<<1;
		} else {
			GPIOI->BSRR = 1U<<17;
		}
	}
}
