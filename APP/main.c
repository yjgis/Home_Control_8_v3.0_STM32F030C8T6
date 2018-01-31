/***********************************************************************
 * 文件名  ：main
 * 描述    ：         
 
     485-Addr               USART              RELAY
B12 B13 B14 B15 A8 A11     A9 A10          B0 B1 B10 11

       IO                          IO_SWITCH
A15 B3 B4 B5 B6 B7 B8 C13    B9 C14 C15 A7 A6 A5 A4 A3 
**********************************************************************/

#include "stm32f0xx.h"
#include "bsp_usart.h"
#include "bsp_relay.h"
#include "bsp_io.h"
#include "bsp_timer3.h"
#include "bsp_iwdg.h"
#include <string.h>


/**********************************************/
/* 函数功能；主函数                           */
/* 入口参数：无                               */
/**********************************************/
int main(void)
{	
	IO_Init();
  Relay_Init();
	USART1_Init();
	Timer_Init();
	RS485_Addr_Init();
	IWDG_Init(4,2500);//4s
	while(1)
	{
		RS485_Addr_Scan();   		
    IO_Enable_Scan();		
		if(Device_State == Online)
		{
		 IO_Online_Input_Scan();
		}
		else
		{
		 IO_Offline_Input_Scan();		
		}
		IWDG_Feed();
	}
}
