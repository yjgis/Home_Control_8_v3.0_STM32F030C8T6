/******************** (C) COPYRIGHT 2012 ������ ********************
 * �ļ���  ��main
 * ����    ��         
 * ʵ��ƽ̨�����stm32f030������
 * ����    ��LED��˸
 * ����    �����
 * ����    ��qfv5.taobao.com
**********************************************************************/

#include "stm32f0xx.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"

Data Rx;

uint8_t ttt[6]={0x01,0x02,0x03,0x04,0x05};
/**********************************************/
/* �������ܣ��򵥵��ӳٺ���                   */
/* ��ڲ�������                               */
/**********************************************/
void delay()
{
	int i,j;
  for(i=0;i<1000;i++)
	  {
			for(j=0;j<1000;j++);
		}
}
/**********************************************/
/* �������ܣ�������                           */
/* ��ڲ�������                               */
/**********************************************/
int main(void)
{
	delay();
	
	SysTick_Init();
	LED_Init();
	USART1_Init();
	
	GPIO_SetBits(GPIOF,GPIO_Pin_4);
	uart_puts("Fresh Persimmon all right reserved!");
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);
	
	while(1)
	{
Delay_ms(500);		
		LED1_Toggle();
	}
}
