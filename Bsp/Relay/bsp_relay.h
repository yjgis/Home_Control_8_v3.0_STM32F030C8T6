#ifndef __BSP_RELAY_H
#define __BSP_RELAY_H

#include "stm32f0xx.h"


#ifdef Mode4
 #define Relay_Num   4
#else
 #define Relay_Num   2
#endif



extern uint8_t Relay_State;

void Relay_Init(void);

void Cmd_Control_Relay(uint8_t *Cmd_Temp);

void Relay_State_Convert(void);
//void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
void Turn_ON_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num);
void Turn_OFF_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num);
void Turn_Toggle_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num);
void IO_Control_Relay(uint8_t Num);




#endif

