/******************** (C) COPYRIGHT 2011 ������ ********************
 * �ļ���  ��led.c
 * ����    ��         
 * ʵ��ƽ̨�����stm32f051������
 * ����    ��led��������
 * ����    �����
 * ����    ��qfv5.taobao.com
**********************************************************************************/

#include "bsp_led.h"
/**********************************************/
/* �������ܣ� led�� ��ʼ��                     */
/* ��ڲ�������                               */
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
	GPIO_SetBits(LED1_PORT, LED1_PIN  | LED2_PIN );
}

/**********************************************/
/* �������ܣ���led��                        */
/* ��ڲ�������                               */
/**********************************************/
void LED_Open(void)
{
	 GPIO_ResetBits(LED1_PORT, LED1_PIN );
	}
/**********************************************/
/* �������ܣ� �ص�led��                        */
/* ��ڲ�������                               */
/**********************************************/
void LED_Close(void)
{
		GPIO_SetBits(LED1_PORT, LED1_PIN );
}

/**********************************************/
/* �������ܣ�led��ת                          */
/* ��ڲ�������                               */
/**********************************************/
void LED1_Toggle(void)
{
GPIO_WriteBit(GPIOA, GPIO_Pin_6, 
		               (BitAction)((1-GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_6))));
}
