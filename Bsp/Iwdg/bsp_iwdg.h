#ifndef __BSP_IWDG_H
#define __BSP_IWDG_H

#include "stm32f0xx.h"



void IWDG_Init(uint8_t prer,uint16_t rlr);
void IWDG_Feed(void);



















#endif


