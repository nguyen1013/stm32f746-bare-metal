#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "i2c.h"

static void handle_i2c_master(void);

//Buffer used for transmission
const uint8_t msg[] = "HELLO";
uint8_t* p_tx_buff = (uint8_t*)msg;
uint8_t tx_size = sizeof(msg);
volatile uint8_t tx_idx = 0;

//Buffer used for reception
uint8_t rx_buff[sizeof(msg)];
uint8_t rx_size = sizeof(msg);
volatile uint8_t rx_idx = 0;

int main(){

	uart1_tx_init();
	user_led_init();
	i2c_slave_config();
	i2c_master_config();
	handle_i2c_master();

	while(1)
	{

	}
}

static void slave_reception_callback(void)
{
	//Read character in receive data register.
	//RXNE flag is cleared by reading data in RXDR register

	//Read first 8 bits
	rx_buff[rx_idx++] = (I2C2->RXDR & 0xFF);
}

static void slave_complete_callback(void)
{
	printf("Transmission complete...\n\r");
}

static void handle_i2c_master(void)
{
	//Set slave address
	I2C3->CR2 |= SLAVE_OWN_ADDRESS;

	//Set 7 bits
	I2C3->CR2 &= ~I2C_CR2_ADD10;

	//Set transfer size
	I2C3->CR2 |= tx_size << 16;

	//Set automatic end mode
	I2C3->CR2 |= I2C_CR2_AUTOEND;

	//Loop until STOP flag is raised
	while (!(I2C3->ISR & I2C_ISR_STOPF))
	{
		//Check TXIS flag value in ISR register
		if (I2C3->ISR & I2C_ISR_TXIS)
		{
			//Write data in tx register.
			//TXIS flag is cleared by writing data in TXDR register
			I2C3->TXDR = (*p_tx_buff++);
		}
	}

	//Clear stop flag
	I2C3->ICR |= I2C_ICR_STOPCF;
}

void I2C2_EV_IRQHandler(void)
{
	//Check ADDR flag in ICR register
	if (I2C2->ICR & I2C_ICR_ADDRCF)
	{
		//Verify the Address Match with the SLAVE_OWN_ADDRESS
		if (i2c2_get_address_matchcode() == SLAVE_OWN_ADDRESS )
		{
			//Clear ADDR flag value ISR register
			I2C2->ISR |= I2C_ICR_ADDRCF;

			//Enable receive interrupt
			I2C2->CR1 |= I2C_CR1_RXIE;
		}
	}
	else if (I2C2->ISR & I2C_ISR_RXNE) //Check RXNE flag value in ISR register
	{
		//Callback
		slave_reception_callback();
	}
	else if (I2C2->ISR & I2C_ISR_STOPF) // Check STOP detection flag in ISR
	{
		//Set STOP detection flag in ICR
		I2C2->ICR |= I2C_ICR_STOPCF;

		//Callback
		slave_complete_callback();
	}
	else
	{
		led_on();
	}
}































