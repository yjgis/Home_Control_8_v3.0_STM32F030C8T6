/******************** (C) COPYRIGHT 2012 青风电子 ********************
 * 文件名  ：main
 * 描述    ：         
 * 实验平台：青风stm32f030开发板
 * 描述    ：LED闪烁
 * 作者    ：青风
 * 店铺    ：qfv5.taobao.com
**********************************************************************/

#include "stm32f0xx.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"

Data Rx;

uint8_t ttt[6]={0x01,0x02,0x03,0x04,0x05};
/**********************************************/
/* 函数功能；简单的延迟函数                   */
/* 入口参数：无                               */
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
/* 函数功能；主函数                           */
/* 入口参数：无                               */
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
