#ifndef __BSP_LED_H
#define	__BSP_LED_H

#include "stm32f0xx.h"
#define LED1_PIN      GPIO_Pin_2
#define LED2_PIN       GPIO_Pin_3
#define LED1_PORT       GPIOA	
#define LED2_PORT       GPIOA
void LED_Init(void);
void LED_Open(void);
void LED_Close(void);
void LED1_Toggle(void);
#endif /* __LED_H */

