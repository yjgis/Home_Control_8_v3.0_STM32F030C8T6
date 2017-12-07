#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f0xx.h"

void SysTick_Init(void);
void Delay_us(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
#define Delay_ms(x) Delay_us(100*x)	 //��λms

#endif /* __SYSTICK_H */
