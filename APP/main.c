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
#include <string.h>
#include "bsp_relay.h"
#include "bsp_io.h"
#include "bsp_timer3.h"




Receive Rx={0};

uint8_t ttt[6]={0x01,0x02,0x03,0x04,0x05};

/**********************************************/
/* 函数功能；主函数                           */
/* 入口参数：无                               */
/**********************************************/
int main(void)
{	
	SysTick_Init();
	Timer_Init();
	LED_Init();
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
