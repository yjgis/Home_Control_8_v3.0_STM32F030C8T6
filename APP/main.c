/******************** (C) COPYRIGHT 2012 ������ ********************
 * �ļ���  ��main
 * ����    ��         
 * ʵ��ƽ̨�����stm32f030������
 * ����    ��LED��˸
 * ����    �����
 * ����    ��qfv5.taobao.com
 
        ADDR          485              USART              RELAY
A0 A1 A2 A3 A4 A5      A6     A7       A9 A10          A8 A11 A12 A15

       IO                          IO_SWITCH
B0 B1 B2 B3 B4 B5 B6 B7    B8 B9 B10 B11 B12 B13 B14 B15

C13 C14 C15
 
**********************************************************************/

#include "stm32f0xx.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include <string.h>
#include "bsp_relay.h"
#include "bsp_io.h"
#include "bsp_timer3.h"




Receive Rx={0};

uint8_t ttt[6]={0x01,0x02,0x03,0x04,0x05};

/**********************************************/
/* �������ܣ�������                           */
/* ��ڲ�������                               */
/**********************************************/
int main(void)
{	
	SysTick_Init();
	Timer_Init();
	LED_Init();
	
  Relay_Init();
	USART1_Init();
	IO_Init();
	IO_Switch();
	Addr_Switch_Init();
	while(1)
	{
		Addr_Switch_Scan();
    IO_Switch_Scan();
    IO_Trigger_Scan(); 	
		if(Rx.Flag)
		{
		  Rx.Flag=0;
			Analyse_Received_Buffer(Rx.Buffer,Rx.Cont);
		  memset(Rx.Buffer,0,20);
		}
		
		
		
//Delay_ms(500);		
//		LED1_Toggle();
	}
}
