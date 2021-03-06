#ifndef __BSP_RELAY_H
#define __BSP_RELAY_H

#include "stm32f0xx.h"


extern uint8_t Relay_State;

void Relay_Init(void);

void Cmd_Control_Relay(uint8_t *Cmd_Temp);

void Relay_State_Convert(void);
void Turn_ON_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num);
void Turn_OFF_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num);
void Turn_Toggle_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num);
void IO_Control_Relay(uint8_t Num);




#endif

