#ifndef __BSP_IO_H
#define __BSP_IO_H

#include "stm32f0xx.h"

typedef struct IO
{
  GPIO_TypeDef* GPIO;
  uint16_t GPIO_Pin;
}GPIO;


#define Tirgger        0

extern uint8_t IO_Enable_Buffer[8];
extern uint8_t IO_Temp[2];
extern uint8_t IO_Input_Lock[8];


void IO_Init(void);
void IO_Input_Init(void);
void IO_Enable_Init(void);
void IO_Enable_Scan(void);
void IO_Input_Scan(void);
void IO_Online_Input_Scan(void);
void IO_Offline_Input_Scan(void);		
void IO_State_Convert(void);

#endif

