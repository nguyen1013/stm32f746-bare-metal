/*
 * adc.h
 *
 *  Created on: Jan 1, 2025
 *      Author: nguyen
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f7xx.h"

void pf10_adc3_init(void);
void start_conversion(void);
uint32_t adc_get_data(void);

#endif /* ADC_H_ */
