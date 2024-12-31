#include "stm32f7xx.h"

#define GPIOI_CLK_EN			(1U<<8)
#define USER_LED_MODER			(1U<<2) // PI1
//#define USER_LED_ODR			(1U<<1) // PI1



int main(){

	RCC->AHB1ENR |= (1U<<8);
	GPIOI->MODER |= USER_LED_MODER;

	while (1) {
		GPIOI->BSRR |= (1U<<1);
		for (int i=0; i<1000000; i++){}
		GPIOI->BSRR |= (1U<<17);
		for (int i=0; i<1000000; i++){}
	}

}
