#include "bsp_relay.h"
#include "bsp_io.h"
#include "string.h"
#include "bsp_usart.h"

uint8_t Relay_Temp[4]={0};
uint8_t Relay_State=0;




GPIO Relay_GPIO[4] ={{GPIOD, GPIO_Pin_7},
                     {GPIOD, GPIO_Pin_4},
                     {GPIOD, GPIO_Pin_3},
                     {GPIOD, GPIO_Pin_2}};





void Turn_ON_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num)
{
	GPIO_SetBits(GPIO,GPIO_Pin);
  Relay_Temp[Num]=0x01;
}

void Turn_OFF_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num)
{
	GPIO_ResetBits(GPIO,GPIO_Pin);
  Relay_Temp[Num]=0x00;
}

void Turn_Toggle_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num)
{
  if(Relay_Temp[Num]==0x01)
  {
    Turn_OFF_Relay(Relay_GPIO[Num].GPIO,Relay_GPIO[Num].GPIO_Pin,Num);
  }
  else if(Relay_Temp[Num]==0x00)
  {
    Turn_ON_Relay(Relay_GPIO[Num].GPIO,Relay_GPIO[Num].GPIO_Pin,Num);
  }
}


void Relay_Init(void)
{
	uint8_t i=0;
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2  ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_Level_3;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  for(i=0;i<4;i++)
  {
    Turn_OFF_Relay(Relay_GPIO[i].GPIO,Relay_GPIO[i].GPIO_Pin,i);   
  }
}




void Cmd_Control_Relay(uint8_t *Cmd_Temp)
{	
  switch(Cmd_Temp[5])
  {
  case 0x01:
    switch(Cmd_Temp[6])
    {
    case 0x00:
      break;
    case 0x01:
      Turn_OFF_Relay(Relay_GPIO[0].GPIO,Relay_GPIO[0].GPIO_Pin,0);
      break;
    case 0x02:
      Turn_ON_Relay(Relay_GPIO[0].GPIO,Relay_GPIO[0].GPIO_Pin,0);
      break;
    case 0x03:
      Turn_Toggle_Relay(Relay_GPIO[0].GPIO,Relay_GPIO[0].GPIO_Pin,0);     
      break;
      
    default:
      break;
    }
    break;
  case 0x02:
    switch(Cmd_Temp[6])
    {
    case 0x00:
      break;
    case 0x01:
      Turn_OFF_Relay(Relay_GPIO[1].GPIO,Relay_GPIO[1].GPIO_Pin,1);
      break;
    case 0x02:
      Turn_ON_Relay(Relay_GPIO[1].GPIO,Relay_GPIO[1].GPIO_Pin,1);      
      break;
    case 0x03:
      Turn_Toggle_Relay(Relay_GPIO[1].GPIO,Relay_GPIO[1].GPIO_Pin,1);   
      break;
      
    default:
      break;
    }
    break;
  case 0x03:
    switch(Cmd_Temp[6])
    {
    case 0x00:
      break;
    case 0x01:
      Turn_OFF_Relay(Relay_GPIO[2].GPIO,Relay_GPIO[2].GPIO_Pin,2);
      break;
    case 0x02:
      Turn_ON_Relay(Relay_GPIO[2].GPIO,Relay_GPIO[2].GPIO_Pin,2);
      break;
    case 0x03:
      Turn_Toggle_Relay(Relay_GPIO[2].GPIO,Relay_GPIO[2].GPIO_Pin,2);  
      break;
      
    default:
      break;
    }
    break;
  case 0x04:
    switch(Cmd_Temp[6])
    {
    case 0x00:
      break;
    case 0x01:
      Turn_OFF_Relay(Relay_GPIO[3].GPIO,Relay_GPIO[3].GPIO_Pin,3);
      break;
    case 0x02:
      Turn_ON_Relay(Relay_GPIO[3].GPIO,Relay_GPIO[3].GPIO_Pin,3);      
      break;
    case 0x03:
      Turn_Toggle_Relay(Relay_GPIO[3].GPIO,Relay_GPIO[3].GPIO_Pin,3);    
      break;
      
    default:
      break;
    }
    break;
    
  default:
    break;
  }
  
}

void IO_Control_Relay(uint8_t Num)
{
  if(IO_Switch_Temp[Num]==0x01)
  {
    Turn_Toggle_Relay(Relay_GPIO[Num].GPIO,Relay_GPIO[Num].GPIO_Pin,Num);
  }
}


void Relay_State_Convert(void)
{
  Relay_State=(Relay_Temp[0] == 0x01?0x02:0x01)
             |(Relay_Temp[1] == 0x01?0x02:0x01)<<2
             |(Relay_Temp[2] == 0x01?0x02:0x01)<<4
             |(Relay_Temp[3] == 0x01?0x02:0x01)<<6;  
}
