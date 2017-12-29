#ifndef  __BSP_USART_H
#define  __BSP_USART_H

#include "stm32f0xx.h"

#define Mode4

#ifdef Mode4
 #define Device_Mode 0x04
#else
 #define Device_Mode 0x02
#endif



#define  Baud_Rate  9600
#define  Offline     0
#define  Online      1

extern uint8_t Device_State;
extern uint16_t Device_Online_Count;

void USART1_Init(void);
void RS485_Addr_Init(void);
void RS485_Addr_Scan(void);
void uart_puts(char *s );
void uart_putc(unsigned char c);
void USART1_Send_Data(volatile uint8_t *buf,uint8_t len);
void Analyse_Received_Buffer(uint8_t *Buffer,uint8_t Cnt);
void Response_IO_Relay_State(uint8_t cmd);
void UART_Cmd_Control_Relay(uint8_t *Cmd_Temp);
void Response_RS485_Adrress(uint8_t addr,uint8_t cmd);
void Response_Cmd_Control_Msg(uint8_t cmd);



#endif
