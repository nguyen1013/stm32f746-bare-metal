#include "uart.h"
#include "rcc.h"
#include "gpio.h"

#define UART1_TX				(1U<<9) // UART1 tx connected to PA9
#define UART1_RX				(1U<<7) // UART1 rx connected to PB7
//#define UART1EN					(1U<<4) // UART1 connected APB2
#define UART_DATAWIDTH_8B		(0x00000000U) // Start bit, 8 data bits, n stop bits
#define UART_PARITY_NONE        (0x00000000U) // Parity control disabled
#define UART_STOPBITS_1			(0x00000000U) // 1 stop bit

static void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits);
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t Baudrate);
static void uart_set_baudrate(USART_TypeDef * USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static void uart_write(USART_TypeDef * USARTx, uint8_t value);
static void set_uart_transfer_direction(USART_TypeDef * USARTx, uint32_t TransferDirection);
static void uart_enable(USART_TypeDef * USARTx);

int __io_putchar(int ch)
{
	uart_write(USART1,ch);

	return ch;
}

void uart1_tx_init(void)
{
	// 1. Enable clk access GPIOA
	set_ahb1_periph_clock(RCC_AHB1ENR_GPIOAEN);

	// 2. Set PA9 to alternation mode
	set_pin_mode(GPIOA, UART1_TX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function to USART
	GPIOA->AFR[1] |= (1U<<4);
	GPIOA->AFR[1] |= (1U<<5);
	GPIOA->AFR[1] |= (1U<<6);
	GPIOA->AFR[1] &= ~(1U<<7);

	// Enable clk to the USART1 module
	set_apb2_periph_clock(RCC_APB2ENR_USART1EN);

	// Configure USART parameters
	config_uart_parameters(USART1, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBITS_1);
	set_uart_transfer_direction(USART1, USART_CR1_TE);

	// Set Baudrate
	uart_set_baudrate(USART1, 16000000, 115200);

	// Enable USART
	uart_enable(USART1);
}

void uart1_rx_interrupt_init(void)
{
	// PA9 = tx
	// PB7 = rx

	/**********Configure tx pin********************/
	// 1. Enable clk access GPIOA
	set_ahb1_periph_clock(RCC_AHB1ENR_GPIOAEN);

	// 2. Set PA9 to alternation mode
	set_pin_mode(GPIOA, UART1_TX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function to USART
	GPIOA->AFR[1] |= (1U<<4);
	GPIOA->AFR[1] |= (1U<<5);
	GPIOA->AFR[1] |= (1U<<6);
	GPIOA->AFR[1] &= ~(1U<<7);

	/**********Configure rx pin********************/
	// 1. Enable clk access GPIOB
	set_ahb1_periph_clock(RCC_AHB1ENR_GPIOBEN);

	// 2. Set PB7 to alternation mode
	set_pin_mode(GPIOB, UART1_RX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function to USART
	GPIOB->AFR[0] |= (1U<<28);
	GPIOB->AFR[0] |= (1U<<29);
	GPIOB->AFR[0] |= (1U<<30);
	GPIOB->AFR[0] &= ~(1U<<31);


	/************General configuration***************/
	// Enable clk to the USART1 module
	set_apb2_periph_clock(RCC_APB2ENR_USART1EN);

	// Configure USART parameters
	config_uart_parameters(USART1, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBITS_1);
	set_uart_transfer_direction(USART1, USART_CR1_TE | USART_CR1_RE);

	// Set Baudrate
	uart_set_baudrate(USART1, 16000000, 115200);

	// Enable USART
	uart_enable(USART1);

	//Enable USART rxne interrupt
	USART1->CR1 |= USART_CR1_RXNEIE;

	//Enable USART interrupt in NVIC
	NVIC_EnableIRQ(USART1_IRQn);
}

void uart1_rxtx_init(void)
{
	// PA9 = tx
	// PB7 = rx

	/**********Configure tx pin********************/
	// 1. Enable clk access GPIOA
	set_ahb1_periph_clock(RCC_AHB1ENR_GPIOAEN);

	// 2. Set PA9 to alternation mode
	set_pin_mode(GPIOA, UART1_TX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function to USART
	GPIOA->AFR[1] |= (1U<<4);
	GPIOA->AFR[1] |= (1U<<5);
	GPIOA->AFR[1] |= (1U<<6);
	GPIOA->AFR[1] &= ~(1U<<7);

	/**********Configure rx pin********************/
	// 1. Enable clk access GPIOB
	set_ahb1_periph_clock(RCC_AHB1ENR_GPIOBEN);

	// 2. Set PB7 to alternation mode
	set_pin_mode(GPIOB, UART1_RX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function to USART
	GPIOB->AFR[0] |= (1U<<28);
	GPIOB->AFR[0] |= (1U<<29);
	GPIOB->AFR[0] |= (1U<<30);
	GPIOB->AFR[0] &= ~(1U<<31);


	/************General configuration***************/
	// Enable clk to the USART1 module
	set_apb2_periph_clock(RCC_APB2ENR_USART1EN);

	// Configure USART parameters
	config_uart_parameters(USART1, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBITS_1);
	set_uart_transfer_direction(USART1, USART_CR1_TE | USART_CR1_RE);

	// Set Baudrate
	uart_set_baudrate(USART1, 16000000, 115200);

	// Enable USART
	uart_enable(USART1);
}

static void uart_write(USART_TypeDef * USARTx, uint8_t value)
{
	// Make sure TDR is empty
	while (!((USARTx->ISR & USART_ISR_TXE))) {}
	// Write value into TDR
	USARTx->TDR = value;
}

uint8_t uart_read(USART_TypeDef *USARTx)
{
	// Make sure RDR is empty
	//while (!((USARTx->ISR & USART_ISR_RXNE))) {}
	while(!(USARTx->ISR & USART_ISR_RXNE)){}

	// Return value from RDR
	return (READ_BIT(USARTx->RDR, USART_RDR_RDR)& 0xFFU);
}

static void uart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CR1,USART_CR1_UE);
}


static void set_uart_transfer_direction(USART_TypeDef *USARTx,uint32_t TransferDirection)
{
	  MODIFY_REG(USARTx->CR1, USART_CR1_RE | USART_CR1_TE, TransferDirection);

}
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div( PeriphClk,  BaudRate);
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

static void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE | USART_CR1_M, Parity | DataWidth);

  MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}
