/******************** (C) COPYRIGHT 2012 ������ ********************
 * �ļ���  ��main
 * ����    ��         
 * ʵ��ƽ̨�����stm32f030������
 * ����    ��LED��˸
 * ����    �����
 * ����    ��qfv5.taobao.com
 
     485-Addr               USART              RELAY
B12 B13 B14 B15 A8 A11     A9 A10          B0 B1 B10 11

       IO                          IO_SWITCH
A15 B3 B4 B5 B6 B7 B8 C13    B9 C14 C15 A7 A6 A5 A4 A3
 
**********************************************************************/

#include "stm32f0xx.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include <string.h>
#include "bsp_relay.h"
#include "bsp_io.h"
#include "bsp_timer3.h"




Receive Rx={0};
uint8_t Buffer[5]={0x01,0x02,0x03,0x04,0x05};
/**********************************************/
/* �������ܣ�������                           */
/* ��ڲ�������                               */
/**********************************************/
int main(void)
{	
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
	}
}
