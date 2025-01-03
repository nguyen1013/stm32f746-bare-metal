#include "stm32f7xx.h"

//#define GPIOAEN					(1U<<0) // UART1 connected to PA9
#define UART1_TX				(1U<<9) // UART1 connected to PA9
#define GPIO_ALTERNATE_MODE		(0x2) 	// 0b 10
//#define UART1EN					(1U<<4) // UART1 connected APB2
#define UART_DATAWIDTH_8B		(0x00000000U) // Start bit, 8 data bits, n stop bits
#define UART_PARITY_NONE        (0x00000000U) // Parity control disabled
#define UART_STOPBITS_1			(0x00000000U) // 1 stop bit

void set_ahb1_periph_clock(uint32_t periphs);
void set_ahb2_periph_clock(uint32_t periphs);
void set_apb1_periph_clock(uint32_t periphs);
void set_apb2_periph_clock(uint32_t periphs);
void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);
void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits);
uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t Baudrate);
void uart_set_baudrate(USART_TypeDef * USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart_write(USART_TypeDef * USARTx, uint8_t value);
void uart1_tx_init(void);
void set_uart_transfer_direction(USART_TypeDef * USARTx, uint32_t TransferDirection);
void uart_enable(USART_TypeDef * USARTx);

int main(){

	int x;
	uart1_tx_init();

	while(1)
	{
		 uart_write(USART1 , 'A');
		 for(int i=0;i<9000;i++)
		 {
			 x++;
		 }
	}
}

void uart_write(USART_TypeDef * USARTx, uint8_t value)
{
	// Make sure TDR is empty
	while (!((USARTx->ISR & USART_ISR_TXE))) {}
	// Write value into TDR
	USARTx->TDR = value;
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

void uart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CR1,USART_CR1_UE);
}


void set_uart_transfer_direction(USART_TypeDef *USARTx,uint32_t TransferDirection)
{
	  MODIFY_REG(USARTx->CR1, USART_CR1_RE | USART_CR1_TE, TransferDirection);

}
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div( PeriphClk,  BaudRate);
}

void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE | USART_CR1_M, Parity | DataWidth);

  MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}

void set_ahb1_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->AHB1ENR,perihs);
}


void set_ahb2_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->AHB2ENR,perihs);
}

void set_apb1_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->APB1ENR,perihs);
}

void set_apb2_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->APB2ENR,perihs);
}

void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
	// Clear the relevant bits in the mode register
	 //GPIOx->MODER &= ~(1U<<18);
	 //GPIOx->MODER &= ~(1U<<19);
	// Set the relevant bits in the mode register
	 //GPIOx->MODER |= 1U<<19;
	//MODIFY_REG(GPIOx->MODER, (0x3 << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
	MODIFY_REG(GPIOx->MODER, (0x3 << (POSITION_VAL(Pin) * 2U)), (Mode << ((POSITION_VAL(Pin) * 2U))));
}

uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
































