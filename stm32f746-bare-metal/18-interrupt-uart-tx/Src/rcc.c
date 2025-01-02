#include "rcc.h"

void set_ahb1_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->AHB1ENR,perihs);
}


void set_ahb2_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->AHB2ENR,perihs);
}

void set_apb1_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->APB1ENR,perihs);
}

void set_apb2_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->APB2ENR,perihs);
}
