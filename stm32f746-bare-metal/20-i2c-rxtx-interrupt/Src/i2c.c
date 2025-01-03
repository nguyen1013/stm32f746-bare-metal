/*
 * i2c.c
 *
 *  Created on: Jan 3, 2025
 *      Author: nguyen
 */
#include "i2c.h"

#define I2C_TIMING					0x00303D5B //Value from CubeMX software calculation

static void i2c2_setOwnAddress1(uint32_t OwnAddress1, uint32_t OwnAddrSize);

//I2C2- SDA on PB9, SCL on PB10
void i2c_slave_config(void)
{
	//Enable clk GPIOB
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	/***********Configure SCL line*************/
	//Configure alternate fuction mode on PB10
	GPIOB->MODER &= ~GPIO_MODER_MODER10_0;
	GPIOB->MODER |= GPIO_MODER_MODER10_1;

	//Select AF4 (I2C2_SCL)
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH2_0;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH2_1;
	GPIOB->AFR[1] |= GPIO_AFRH_AFRH2_2;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH2_3;

	//Set output pin type to open-drain
	GPIOB->OTYPER |= GPIO_OTYPER_OT10;

	//Enable internal pull-up resistor
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR10_0;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR10_1;

	/**********Configure SDA line*************/
	//Configure alternate fuction mode on PB9
	GPIOB->MODER &= ~GPIO_MODER_MODER9_0;
	GPIOB->MODER |= GPIO_MODER_MODER9_1;

	//Select AF4 (I2C2_SCL)
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH1_0;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH1_1;
	GPIOB->AFR[1] |= GPIO_AFRH_AFRH1_2;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH1_3;

	//Set output pin type to open-drain
	GPIOB->OTYPER |= GPIO_OTYPER_OT9;

	//Enable internal pull-up resistor
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR9_0;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR9_1;

	/**********Configure I2C parameters*************/
	//Enable clk I2C
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

	//Enable I2C interrupt in NVIC
	NVIC_EnableIRQ(I2C2_EV_IRQn);

	//Disable I2C module
	I2C2->CR1 &= ~I2C_CR1_PE;

	//Set device address
	i2c2_setOwnAddress1(SLAVE_OWN_ADDRESS, 0);

	//Enable I2C module
	I2C2->CR1 |= I2C_CR1_PE;

	//Enable ADDR interrupt
	I2C2->CR1 |= I2C_CR1_ADDRIE;

	//Enable NACK interrupt
	I2C2->CR1 |= I2C_CR1_NACKIE;

	//Enable STOP interrupt
	I2C2->CR1 |= I2C_CR1_STOPIE;

}

//I2C3- SDA on PH8, SCL on PH7
void i2c_master_config(void)
{
	//Enable clk GPIOH
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;

	//Configure SCL pin: alternate function, open-dreain, pull-up
	GPIOH->MODER &= ~GPIO_MODER_MODER7_0;
	GPIOH->MODER |= GPIO_MODER_MODER7_1;

	GPIOH->AFR[0] &= ~GPIO_AFRL_AFRL7_0;
	GPIOH->AFR[0] &= ~GPIO_AFRL_AFRL7_1;
	GPIOH->AFR[0] |= GPIO_AFRL_AFRL7_2;
	GPIOH->AFR[0] &= ~GPIO_AFRL_AFRL7_3;

	GPIOH->OTYPER |= GPIO_OTYPER_OT7;

	GPIOH->PUPDR |= GPIO_PUPDR_PUPDR7_0;
	GPIOH->PUPDR &= ~GPIO_PUPDR_PUPDR7_1;

	//Configure SDA pin: alternate function, open-dreain, pull-up
	GPIOH->MODER &= ~GPIO_MODER_MODER8_0;
	GPIOH->MODER |= GPIO_MODER_MODER8_1;

	GPIOH->AFR[1] &= ~GPIO_AFRH_AFRH0_0;
	GPIOH->AFR[1] &= ~GPIO_AFRH_AFRH0_1;
	GPIOH->AFR[1] |= GPIO_AFRH_AFRH0_2;
	GPIOH->AFR[1] &= ~GPIO_AFRH_AFRH0_3;

	GPIOH->OTYPER |= GPIO_OTYPER_OT8;

	GPIOH->PUPDR |= GPIO_PUPDR_PUPDR8_0;
	GPIOH->PUPDR &= ~GPIO_PUPDR_PUPDR8_1;

	/**********Configure I2C parameters*************/
	RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;

	//Disable I2C module
	I2C3->CR1 &= ~I2C_CR1_PE;

	//Set timing
	I2C3->TIMINGR = I2C_TIMING;

	//Enable I2C module
	I2C3->CR1 |= I2C_CR1_PE;

}

static void i2c2_setOwnAddress1(uint32_t OwnAddress, uint32_t OwnAddrSize)
{
	MODIFY_REG(I2C2->OAR1, I2C_OAR1_OA1 | I2C_OAR1_OA1MODE, OwnAddress | OwnAddrSize);
}

uint32_t i2c2_get_address_matchcode(void)
{
	return (uint32_t)(READ_BIT(I2C2->ISR, I2C_ISR_ADDCODE) >> I2C_ISR_ADDCODE_Pos << 1);
}

























