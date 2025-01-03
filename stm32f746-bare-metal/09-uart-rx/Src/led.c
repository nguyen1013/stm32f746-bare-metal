#include "led.h"

void user_led_init(void)
{
	// Enable clk for GPIOI
	RCC->AHB1ENR |= GPIOI_CLK_EN;

	// Configure GPIOI as output
	GPIOI->MODER |= 1U<<2;
	GPIOI->MODER &= ~(1U<<3);
}

void led_on(void)
{
	GPIOI->ODR |= USER_LED;
}

void led_off(void)
{
	GPIOI->ODR &= ~(USER_LED);
}

void led_toggle(void)
{
	GPIOI->ODR ^= USER_LED;
}

