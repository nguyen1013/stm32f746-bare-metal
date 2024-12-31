#define PERISH_BASE 			0x40000000UL
#define AHB1_OFFSET				0x00020000UL
#define AHB1_BASE				(PERISH_BASE + AHB1_OFFSET)

#define RCC_OFFSET				0x00003800UL
#define RCC_BASE				(AHB1_BASE + RCC_OFFSET)
#define RCC_AHB1ENR_OFFSET		0x30UL
#define RCC_AHB1ENR 			(*(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))
#define GPIOI_CLK_EN			(1U<<8)

#define GPIOI_OFFSET			0x00002000UL
#define GPIOI_BASE				(AHB1_BASE + GPIOI_OFFSET)

#define MODER_OFFSET			0x0UL
#define GPIOI_MODER				(*(volatile unsigned int *) (GPIOI_BASE + MODER_OFFSET))
#define USER_LED_MODER			(1U<<2) // PI1

#define GPIOI_ODR_OFFSET		0x14UL
#define	GPIOI_ODR				(*(volatile unsigned int *) (GPIOI_BASE + GPIOI_ODR_OFFSET))
#define USER_LED_ODR			(1U<<1) // PI1


int main(){

	RCC_AHB1ENR |= GPIOI_CLK_EN;

	GPIOI_MODER |= USER_LED_MODER;

	while(1) {

		GPIOI_ODR |= USER_LED_ODR;
	}

}
