/******************** (C) COPYRIGHT 2011 青风电子 ********************
 * 文件名  ：led.c
 * 描述    ：         
 * 实验平台：青风stm32f051开发板
 * 描述    ：led驱动函数
 * 作者    ：青风
 * 店铺    ：qfv5.taobao.com
**********************************************************************************/

#include "bsp_led.h"
/**********************************************/
/* 函数功能； led灯 初始化                     */
/* 入口参数：无                               */
/**********************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_InitStruct.GPIO_Pin = LED1_PIN |LED2_PIN  ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_Level_3;
  GPIO_Init(LED1_PORT, &GPIO_InitStruct);
	
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
//	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
////  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP ;
//  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_Level_3;
//  GPIO_Init(GPIOF, &GPIO_InitStruct);
//		GPIO_SetBits(GPIOF,GPIO_Pin_4);
	
	GPIO_SetBits(LED1_PORT, LED1_PIN  | LED2_PIN );
}

/**********************************************/
/* 函数功能；打开led灯                        */
/* 入口参数：无                               */
/**********************************************/
void LED_Open(void)
{
	GPIO_ResetBits(LED1_PORT, LED1_PIN );
}
/**********************************************/
/* 函数功能； 关掉led灯                        */
/* 入口参数：无                               */
/**********************************************/
void LED_Close(void)
{
		GPIO_SetBits(LED1_PORT, LED1_PIN );
}
/**********************************************/
/* 函数功能；led翻转                          */
/* 入口参数：无                               */
/**********************************************/
void LED1_Toggle(void)
{
//	toggle(GPIOA,GPIO_Pin_2|GPIO_Pin_3);
GPIO_WriteBit(GPIOA,GPIO_Pin_2|GPIO_Pin_3, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2|GPIO_Pin_3))));
}
