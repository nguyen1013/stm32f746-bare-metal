#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "spi.h"

uint8_t tx_buff[] = "AAAAA";
uint8_t tx_size = sizeof(tx_buff);
volatile uint8_t idx = 0;

uint8_t rx_buff[sizeof(tx_buff)];
uint8_t rx_size = sizeof(tx_buff);
volatile uint8_t rx_idx = 0;

int main(){

	uart1_tx_init();
	spi5_config(); //Configure master device
	spi2_config(); //Configure master device
	spi2_activate(); //Enable slave(RX) device
	spi5_activate(); //Enable master(TX) device

	while(1)
	{
	}
}

static void spi5_callback(void)
{
	volatile uint8_t *spidr = ((volatile uint8_t *)&SPI5->DR);
	*spidr = tx_buff[idx];
	idx++;
	if (idx >= tx_size) idx=0;
}

void SPI5_IRQHandler(void)
{
	//Check TXE flag value in SR register
	if (SPI5->SR & SPI_SR_TXE)
	{
		//callback
		spi5_callback();
	}
}

static void spi2_callback(void)
{
	rx_buff[rx_idx] =  SPI2->DR;
	rx_idx++;
	if (rx_idx >= rx_size) rx_idx=0;
}

void SPI2_IRQHandler(void)
{
	//Check RXNE flag value in SR register
	if ((SPI2->SR & SPI_SR_RXNE))
	{
		//callback
		spi2_callback();
	}

}















