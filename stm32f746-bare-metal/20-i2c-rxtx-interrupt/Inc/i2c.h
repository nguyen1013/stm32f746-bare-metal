/*
 * i2c.h
 *
 *  Created on: Jan 3, 2025
 *      Author: nguyen
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "stm32f7xx.h"

#define SLAVE_OWN_ADDRESS					0x3A //Random value
#define I2C_DIRECTION_WRITE					0x00000000U

void i2c_slave_config(void);
uint32_t i2c2_get_address_matchcode(void);
void i2c_master_config(void);

#endif /* I2C_H_ */
