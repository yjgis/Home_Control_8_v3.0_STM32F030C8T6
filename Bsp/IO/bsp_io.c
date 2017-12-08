#include "bsp_io.h"
#include "bsp_usart.h"
#include "bsp_relay.h"
#include "bsp_SysTick.h"
#include "string.h"
//#include "bsp_timer.h"

uint8_t IO_Switch_Temp[6]={0};
uint8_t IO_Trigger_Temp[6]={0};
uint8_t IO_Temp[2]={0};


GPIO IO_Switch_GPIO[6]={{GPIOB, GPIO_Pin_7},
                        {GPIOB, GPIO_Pin_5},
                        {GPIOB, GPIO_Pin_3},
                        {GPIOB, GPIO_Pin_1},
                        {GPIOF, GPIO_Pin_7},
                        {GPIOF, GPIO_Pin_5}};

GPIO IO_Trigger_GPIO[6]={{GPIOB, GPIO_Pin_0},
                         {GPIOB, GPIO_Pin_2},
                         {GPIOB, GPIO_Pin_4},
                         {GPIOB, GPIO_Pin_6},
                         {GPIOA, GPIO_Pin_6},
                         {GPIOA, GPIO_Pin_5}};


void IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

void IO_Switch(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
		
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);	

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStruct);		
}

void IO_Trigger_Scan(void)
{ 
  uint8_t i=0;	
  static uint8_t Trigger_Temp[4]={0};
  
  for(i=0;i<6;i++)
  {
    IO_Trigger_Temp[i]=(GPIO_ReadInputDataBit(IO_Trigger_GPIO[i].GPIO,IO_Trigger_GPIO[i].GPIO_Pin)==Tirgger?0x01:0x00);
  }
  
  if(Device_State==Offline)
  {
    if(IO_Offline_Trigger(Trigger_Temp,IO_Trigger_Temp))
    {
      Delay_ms(3000);
      for(i=0;i<6;i++)
      {
        IO_Trigger_Temp[i]=(GPIO_ReadInputDataBit(IO_Trigger_GPIO[i].GPIO,IO_Trigger_GPIO[i].GPIO_Pin)==Tirgger?0x01:0x00);
      }
      memcpy(Trigger_Temp,IO_Trigger_Temp,4);
    }
  }
}


uint8_t IO_Offline_Trigger(uint8_t *Trigger_Temp1,uint8_t *Trigger_Temp2)
{ 
  uint8_t Trigger=0,i=0;
  for(i=0;i<4;i++)
  {
    if(Trigger_Temp1[i]!=Trigger_Temp2[i])
    {
      IO_Control_Relay(i);
      Trigger=1;
    }  
  }
  return Trigger;
}


void IO_Switch_Scan(void)
{  
  uint8_t i=0;
  for(i=0;i<6;i++)
  {
    IO_Switch_Temp[i]=(GPIO_ReadInputDataBit(IO_Switch_GPIO[i].GPIO,IO_Switch_GPIO[i].GPIO_Pin)==0?0x01:0x00);
  }
}


void IO_State_Convert(void)
{
  IO_Temp[0] |=((IO_Switch_Temp[0]==0x01?0x01:0x00)<<1
               |(IO_Switch_Temp[1]==0x01?0x01:0x00)<<3
               |(IO_Switch_Temp[2]==0x01?0x01:0x00)<<5
               |(IO_Switch_Temp[3]==0x01?0x01:0x00)<<7);
  
  IO_Temp[1] |=((IO_Switch_Temp[4]==0x01?0x01:0x00)<<1
               |(IO_Switch_Temp[5]==0x01?0x01:0x00)<<3);

  IO_Temp[0] |=((IO_Trigger_Temp[0]==0x01?0x01:0x00)
               |(IO_Trigger_Temp[1]==0x01?0x01:0x00)<<2
               |(IO_Trigger_Temp[2]==0x01?0x01:0x00)<<4
               |(IO_Trigger_Temp[3]==0x01?0x01:0x00)<<6);
  
  IO_Temp[1] |=((IO_Trigger_Temp[4]==0x01?0x01:0x00)
               |(IO_Trigger_Temp[5]==0x01?0x01:0x00)<<2);  
}
