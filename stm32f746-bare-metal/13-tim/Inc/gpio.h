#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "stm32f7xx.h"

//#define GPIOAEN					(1U<<0) // UART1 connected to PA9
#define GPIO_ALTERNATE_MODE		(0x2) 	// 0b 10

void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);

#endif /* GPIO_H_ */
