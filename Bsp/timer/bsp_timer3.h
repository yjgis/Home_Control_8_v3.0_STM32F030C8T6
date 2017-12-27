#ifndef __BSP_TIMER3_H
#define __BSP_TIMER3_H

#include "stm32f0xx.h"




extern uint16_t Device_Online_Count;


void Timer_Init(void);
void Timer3_Count_Decrement(void);
void Timer3_Delay_MS(uint16_t Delay_ms);  //1ms
void Timer3_Timing_Sec(uint8_t Timing_Sec); //1s
void Device_State_Judgment(void);







#endif
