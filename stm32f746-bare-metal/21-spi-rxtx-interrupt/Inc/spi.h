/*
 * spi.h
 *
 *  Created on: Jan 4, 2025
 *      Author: nguyen
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include "stm32f7xx.h"



void spi1_config(void);
void spi2_config(void);
void spi3_config(void);
void spi5_config(void);
void spi1_activate(void);
void spi2_activate(void);
void spi3_activate(void);
void spi5_activate(void);

#endif /* SPI_H_ */
