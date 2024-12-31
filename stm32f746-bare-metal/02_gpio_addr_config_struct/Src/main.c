#include <stdint.h>

#define PERISH_BASE 			0x40000000UL
#define AHB1_OFFSET				0x00020000UL
#define AHB1_BASE				(PERISH_BASE + AHB1_OFFSET)

#define RCC_OFFSET				0x00003800UL
#define RCC_BASE				(AHB1_BASE + RCC_OFFSET)
#define GPIOI_CLK_EN			(1U<<8)

#define GPIOI_OFFSET			0x00002000UL
#define GPIOI_BASE				(AHB1_BASE + GPIOI_OFFSET)
#define USER_LED_MODER			(1U<<2) // PI1
#define USER_LED_ODR			(1U<<1) // PI1

typedef struct {
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
} RCC_Typedef;

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
} GPIO_Typedef;

#define	RCC						((RCC_Typedef *)(RCC_BASE))
#define GPIOI					((GPIO_Typedef *) (GPIOI_BASE))

int main(){

	RCC->AHB1ENR |= (1U<<8);
	GPIOI->MODER |= USER_LED_MODER;

	while(1) {

		GPIOI->ODR |= USER_LED_ODR;
	}

}
