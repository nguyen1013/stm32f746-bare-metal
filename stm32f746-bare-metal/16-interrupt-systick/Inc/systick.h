/*
 * systick.h
 *
 *  Created on: Jan 1, 2025
 *      Author: nguyen
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include "stm32f7xx.h"

void systickDelayMs(int delay);
void systick_1hz_interrupt(void);

#endif /* SYSTICK_H_ */
