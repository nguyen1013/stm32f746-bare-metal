#include "stm32f7xx.h"

#define GPIOI_CLK_EN			(1U<<8)
#define USER_LED_MODER			(1U<<2) // PI1
#define USER_LED_ODR			(1U<<1) // PI1



int main(){

	RCC->AHB1ENR |= (1U<<8);
	GPIOI->MODER |= USER_LED_MODER;

	while(1) {

		GPIOI->ODR |= USER_LED_ODR;
	}

}
