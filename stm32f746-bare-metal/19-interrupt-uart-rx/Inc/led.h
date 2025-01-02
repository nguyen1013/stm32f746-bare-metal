#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include "stm32f7xx.h"

#define USER_LED 		(1U<<1) // Led connected to PI1
#define GPIOI_CLK_EN	(1U<<8) // Led connected to PI1

typedef uint32_t ledType;

void user_led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif /* LED_H_ */
