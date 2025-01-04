/*
 * spi.c
 *
 *  Created on: Jan 4, 2025
 *      Author: nguyen
 */
#include "spi.h"

void spi1_config(void)
{
	//Enable clk GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Set AF mode to MODER pin PA5
	GPIOA->MODER &= ~GPIO_MODER_MODER5_0;
	GPIOA->MODER |= GPIO_MODER_MODER5_1;

	//Set alternate function AF5 to PA5
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL5_0;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL5_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL5_2;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL5_3;

	//Set pin speed to very high
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR5_0 | GPIO_OSPEEDR_OSPEEDR5_1;

	//Enable internal pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR5_1;

	//Configure SPI MOSI Pin PA7
	GPIOA->MODER &= ~GPIO_MODER_MODER7_0;
	GPIOA->MODER |= GPIO_MODER_MODER7_1;

	//Set alternate function AF5 to PA7
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL7_0;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL7_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL7_2;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL7_3;

	//Set pin speed to very high
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7_0 | GPIO_OSPEEDR_OSPEEDR7_1;

	//Enable internal pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR7_1;

	//SPI interrupt in the NVIC
	NVIC_EnableIRQ(SPI1_IRQn);

	/*******************************/
	//Config SPI1 communication
	//Enable clock access to SPI1
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	//Set clk to fPCLK/256
	SPI1->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;

	//Select TX only
	SPI1->CR1 |= SPI_CR1_BIDIOE;

	//Select 1-line bidirectional data mode selected
	SPI1->CR1 |= SPI_CR1_BIDIMODE;

	//Set CPOL to 1 and CPHA to 1
	SPI1->CR1 |= SPI_CR1_CPOL;
	SPI1->CR1 |= SPI_CR1_CPHA;

	//Set data width to 8 bit
	SPI1->CR2 |= SPI_CR2_DS_0;
	SPI1->CR2 |= SPI_CR2_DS_1;
	SPI1->CR2 |= SPI_CR2_DS_2;
	SPI1->CR2 &= ~SPI_CR2_DS_3;

	//Enable software slave management
	SPI1->CR1 |= SPI_CR1_SSM;

	//Enable Slave Select Output
	SPI1->CR2 |= SPI_CR2_SSOE;

	//Set fifo reception threshold
	SPI1->CR2 |= SPI_CR2_FRXTH;

	//Enable TXE Interrupt
	SPI1->CR2 |= SPI_CR2_TXEIE;

	//Set mode to MASTER
	SPI1->CR1 |= SPI_CR1_MSTR;
}


void spi3_config(void)
{
	//Enable the peripheral clock of GPIOB
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	//Configure SPI3 SCK Pin PB3
	GPIOB->MODER &= ~GPIO_MODER_MODER3_0;
	GPIOB->MODER |= GPIO_MODER_MODER3_1;

	//Select alternate type AF6
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL3_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL3_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL3_2;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL3_3;

	//Set pin speed to Very High
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR3_0 | GPIO_OSPEEDR_OSPEEDR3_1;

	//Enable internal pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR3_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR3_1;

	//Configure SPI3 MISO Pin PB4
	GPIOB->MODER &= ~GPIO_MODER_MODER4_0;
	GPIOB->MODER |= GPIO_MODER_MODER4_1;

	//Select alternate type AF6
	GPIOB->AFR[0] &= GPIO_AFRL_AFRL4_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL4_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL4_2;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL4_3;

	//Set pin speed to Very High
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR4_0 | GPIO_OSPEEDR_OSPEEDR4_1;

	//Enable internal pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR4_1;

	//Enable SPI3 interrupt in NVIC
	NVIC_EnableIRQ(SPI3_IRQn);

	/*******************************/
	//Configure SPI3 communication
	//Enable clock access to SPI3
	RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

	//Set clock to fPCLK/256
	SPI3->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;

	//Set CPOL to 1 and CPHA to 1
	SPI3->CR1 |= SPI_CR1_CPOL;
	SPI3->CR1 |= SPI_CR1_CPHA;

	//Set data width to 8 bit
	SPI3->CR2 |= SPI_CR2_DS_0;
	SPI3->CR2 |= SPI_CR2_DS_1;
	SPI3->CR2 |= SPI_CR2_DS_2;
	SPI3->CR2 &= ~SPI_CR2_DS_3;

	//Enable software slave management
	SPI3->CR1 |= SPI_CR1_SSM;

	//Enable Slave Select Output
	SPI3->CR2 |= SPI_CR2_SSOE;

	//Select 1-line bidirectional data mode selected
	SPI3->CR1 |= SPI_CR1_BIDIMODE;

	//Select RX only
	SPI3->CR1 &=  ~SPI_CR1_BIDIOE;

	//Set fifo reception threshold
	SPI3->CR2 |= SPI_CR2_FRXTH;

	//Enable RXNE  Interrupt
	SPI3->CR2 |= SPI_CR2_RXNEIE;
}

void spi5_config(void) //PF7 SPI5_SCK - PF9 SPI5_MOSI
{
	//Enable clk GPIOF
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

	//Set AF mode to MODER pin PF7
	GPIOF->MODER &= ~GPIO_MODER_MODER7_0;
	GPIOF->MODER |= GPIO_MODER_MODER7_1;

	//Set alternate function AF5 to PF7
	GPIOF->AFR[0] |= GPIO_AFRL_AFRL7_0;
	GPIOF->AFR[0] &= ~GPIO_AFRL_AFRL7_1;
	GPIOF->AFR[0] |= GPIO_AFRL_AFRL7_2;
	GPIOF->AFR[0] &= ~GPIO_AFRL_AFRL7_3;

	//Set pin speed to very high
	GPIOF->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7_0 | GPIO_OSPEEDR_OSPEEDR7_1;

	//Enable internal pull-down
	GPIOF->PUPDR &= ~GPIO_PUPDR_PUPDR7_0;
	GPIOF->PUPDR |= GPIO_PUPDR_PUPDR7_1;

	//Configure SPI MOSI Pin PF9
	GPIOF->MODER &= ~GPIO_MODER_MODER9_0;
	GPIOF->MODER |= GPIO_MODER_MODER9_1;

	//Set alternate function AF5 to PF9
	GPIOF->AFR[1] |= GPIO_AFRH_AFRH1_0;
	GPIOF->AFR[1] &= ~GPIO_AFRH_AFRH1_1;
	GPIOF->AFR[1] |= GPIO_AFRH_AFRH1_2;
	GPIOF->AFR[1] &= ~GPIO_AFRH_AFRH1_3;

	//Set pin speed to very high
	GPIOF->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9_0 | GPIO_OSPEEDR_OSPEEDR9_1;

	//Enable internal pull-down
	GPIOF->PUPDR &= ~GPIO_PUPDR_PUPDR9_0;
	GPIOF->PUPDR |= GPIO_PUPDR_PUPDR9_1;

	//SPI5 interrupt in the NVIC
	NVIC_EnableIRQ(SPI5_IRQn);

	/*******************************/
	//Config SPI5 communication
	//Enable clock access to SPI5
	RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;

	//Set clk to fPCLK/256
	SPI5->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;

	//Select TX only
	SPI5->CR1 |= SPI_CR1_BIDIOE;

	//Select 1-line bidirectional data mode selected
	SPI5->CR1 |= SPI_CR1_BIDIMODE;

	//Set CPOL to 1 and CPHA to 1
	SPI5->CR1 |= SPI_CR1_CPOL;
	SPI5->CR1 |= SPI_CR1_CPHA;

	//Set data width to 8 bit
	SPI5->CR2 |= SPI_CR2_DS_0;
	SPI5->CR2 |= SPI_CR2_DS_1;
	SPI5->CR2 |= SPI_CR2_DS_2;
	SPI5->CR2 &= ~SPI_CR2_DS_3;

	//Enable software slave management
	SPI5->CR1 |= SPI_CR1_SSM;

	//Enable Slave Select Output
	SPI5->CR2 |= SPI_CR2_SSOE;

	//Set fifo reception threshold
	SPI5->CR2 |= SPI_CR2_FRXTH;

	//Enable TXE Interrupt
	SPI5->CR2 |= SPI_CR2_TXEIE;

	//Set mode to MASTER
	SPI5->CR1 |= SPI_CR1_MSTR;
}

void spi2_config(void) //PI1 SPI2_SCK - PB14 SPI2_MISO
{
	//Enable the peripheral clock of GPIOI
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;

	//Configure SPI2 SCK Pin PI1
	GPIOI->MODER &= ~GPIO_MODER_MODER1_0;
	GPIOI->MODER |= GPIO_MODER_MODER1_1;

	//Select alternate type AF5
	GPIOI->AFR[0] |= GPIO_AFRL_AFRL1_0;
	GPIOI->AFR[0] &= ~GPIO_AFRL_AFRL1_1;
	GPIOI->AFR[0] |= GPIO_AFRL_AFRL1_2;
	GPIOI->AFR[0] &= ~GPIO_AFRL_AFRL1_3;

	//Set pin speed to Very High
	GPIOI->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR1_0 | GPIO_OSPEEDR_OSPEEDR1_1;

	//Enable internal pull-down
	GPIOI->PUPDR &= ~GPIO_PUPDR_PUPDR1_0;
	GPIOI->PUPDR |= GPIO_PUPDR_PUPDR1_1;

	//Configure SPI2 MISO Pin PB14
	//Enable the peripheral clock of GPIOB
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER &= ~GPIO_MODER_MODER14_0;
	GPIOB->MODER |= GPIO_MODER_MODER14_1;

	//Select alternate type AF5
	GPIOB->AFR[1] |= GPIO_AFRL_AFRL6_0;
	GPIOB->AFR[1] &= ~GPIO_AFRL_AFRL6_1;
	GPIOB->AFR[1] |= GPIO_AFRL_AFRL6_2;
	GPIOB->AFR[1] &= ~GPIO_AFRL_AFRL6_3;

	//Set pin speed to Very High
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR14_0 | GPIO_OSPEEDR_OSPEEDR14_1;

	//Enable internal pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR14_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR14_1;

	//Enable SPI2 interrupt in NVIC
	NVIC_EnableIRQ(SPI2_IRQn);

	/*******************************/
	//Configure SPI2 communication
	//Enable clock access to SPI2
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

	//Set clock to fPCLK/256
	SPI2->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;

	//Set CPOL to 1 and CPHA to 1
	SPI2->CR1 |= SPI_CR1_CPOL;
	SPI2->CR1 |= SPI_CR1_CPHA;

	//Set data width to 8 bit
	SPI2->CR2 |= SPI_CR2_DS_0;
	SPI2->CR2 |= SPI_CR2_DS_1;
	SPI2->CR2 |= SPI_CR2_DS_2;
	SPI2->CR2 &= ~SPI_CR2_DS_3;

	//Enable software slave management
	SPI2->CR1 |= SPI_CR1_SSM;

	//Enable Slave Select Output
	SPI2->CR2 |= SPI_CR2_SSOE;

	//Select 1-line bidirectional data mode selected
	SPI2->CR1 |= SPI_CR1_BIDIMODE;

	//Select RX only
	SPI2->CR1 &=  ~SPI_CR1_BIDIOE;

	//Set fifo reception threshold
	SPI2->CR2 |= SPI_CR2_FRXTH;

	//Enable RXNE  Interrupt
	SPI2->CR2 |= SPI_CR2_RXNEIE;
}

void spi2_activate(void)
{
	//Enable SPI2
	SPI2->CR1 |= SPI_CR1_SPE;
}

void spi5_activate(void)
{
	//Enable SPI5
	SPI5->CR1 |= SPI_CR1_SPE;
}

void spi1_activate(void)
{
	//Enable SPI1
	SPI1->CR1 |= SPI_CR1_SPE;
}

void spi3_activate(void)
{
	//Enable SPI3
	SPI3->CR1 |= SPI_CR1_SPE;
}





















