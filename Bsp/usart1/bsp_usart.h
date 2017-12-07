#ifndef  __BSP_USART_H
#define  __BSP_USART_H

#include "stm32f0xx.h"

typedef struct data
{
  uint8_t Rx_Flag;
	uint8_t Rx_Buffer[100];
	uint8_t Rx_Cont;
}Data;


#define  Baud_Rate  9600


void USART1_Init(void);

void uart_puts(char *s );
void uart_putc(unsigned char c);
void USART1_Send_Data(volatile uint8_t *buf,uint8_t len);





#endif
