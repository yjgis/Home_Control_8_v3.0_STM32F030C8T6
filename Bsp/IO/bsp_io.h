#ifndef __BSP_IO_H
#define __BSP_IO_H

#include "stm32f0xx.h"

typedef struct IO
{
  GPIO_TypeDef* GPIO;
  uint16_t GPIO_Pin;
}GPIO;


#define Tirgger        0

extern uint8_t IO_Switch_Temp[8];
extern uint8_t IO_Temp[2];

void IO_Init(void);
void IO_Switch(void);
void Addr_Switch_Scan(void);
void IO_Trigger_Scan(void);
void IO_Switch_Scan(void);
void IO_State_Convert(void);
uint8_t IO_Offline_Trigger(uint8_t *Trigger_Temp1,uint8_t *Trigger_Temp2);

#endif

