#ifndef __BSP_TIMER3_H
#define __BSP_TIMER3_H

#include "stm32f0xx.h"



void Timer_Init(void);
void Timer3_Count_Decrement(void);
void Timer3_Delay(uint16_t Delay_ms);  //1ms
void Device_State_Judgment(void);







#endif
