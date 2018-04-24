#include "bsp_relay.h"
#include "bsp_io.h"
#include "string.h"
#include "bsp_usart.h"

/**********************************************************
												 RELAY
								    	B0 B1 B10 11
**********************************************************/
uint8_t Relay_Temp[4]={0};
uint8_t Relay_State=0;



GPIO Relay_GPIO[3] ={{GPIOA, GPIO_Pin_2},
                     {GPIOA, GPIO_Pin_1},
                     {GPIOA, GPIO_Pin_0}};

/**********************************************************************************
  * @brief  �򿪼̵���
  * @param  GPIO------�̵����������ŵĶ˿ں�
						GPIO_Pin--�̵����������ŵ����ź�
						Num-------��Ҫ�򿪵ļ̵����ı��				 
  * @retval None
 *********************************************************************************/	
void Turn_ON_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num)
{
	GPIO_SetBits(GPIO,GPIO_Pin);
  Relay_Temp[Num]=0x01;
}

/**********************************************************************************
  * @brief  �رռ̵���
  * @param  GPIO------�̵����������ŵĶ˿ں�
						GPIO_Pin--�̵����������ŵ����ź�
						Num-------��Ҫ�رյļ̵����ı��				 
  * @retval None
 *********************************************************************************/	
void Turn_OFF_Relay(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,uint8_t Num)
{
	GPIO_ResetBits(GPIO,GPIO_Pin);
  Relay_Temp[Num]=0x00;
}

/**********************************************************************************
  * @brief  ��ת�̵���
  * @param  GPIO------�̵����������ŵĶ˿ں�
						GPIO_Pin--�̵����������ŵ����ź�
						Num-------��Ҫ��ת�ļ̵����ı��				 
  * @retval None
 *********************************************************************************/	
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

/**********************************************************************************
  * @brief  �̵������ŵĳ�ʼ��(��)
  * @param  None		 
  * @retval None
 *********************************************************************************/	
void Relay_Init(void)
{
	uint8_t i=0;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_Level_3;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  for(i=0;i<4;i++)
  {
    Turn_OFF_Relay(Relay_GPIO[i].GPIO,Relay_GPIO[i].GPIO_Pin,i);   
  }
}

/**********************************************************************************
  * @brief  ͨ��RS485�������ݶԼ̵������п���
  * @param  Cmd_Temp--ͨ��RS485�������Ŀ�������		 
  * @retval None
 *********************************************************************************/	
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
  default:
    break;
  }
}

/**********************************************************************************
  * @brief  ���������ͨ��IO���ŶԼ̵������п���
  * @param  Num--��Ҫ���Ƶļ̵����ı��		 
  * @retval None
 *********************************************************************************/	
void IO_Control_Relay(uint8_t Num)
{
  if(Num < Device_Mode)
	{		
		switch(Num)
		{
			case 0x00:
				if(IO_Enable_Buffer[0] == 0x01)
				{
					Turn_Toggle_Relay(Relay_GPIO[0].GPIO,Relay_GPIO[0].GPIO_Pin,0);
				}			
			  break;
			case 0x01:
				if(IO_Enable_Buffer[1] == 0x01)
				{
					Turn_Toggle_Relay(Relay_GPIO[0].GPIO,Relay_GPIO[0].GPIO_Pin,1);
				}				
		  	break;		
			case 0x02:
				if(IO_Enable_Buffer[2] == 0x01)
				{
					Turn_Toggle_Relay(Relay_GPIO[0].GPIO,Relay_GPIO[0].GPIO_Pin,2);
				}				
			  break;		
			default:
				break;
		}
	}
}

/**********************************************************************************
  * @brief  ���洢�������еļ̵���״̬ת�������ݷ���ʱ����Ҫ������
  * @param  None	 
  * @retval None
 *********************************************************************************/	
void Relay_State_Convert(void)
{
  Relay_State=(Relay_Temp[0] == 0x01?0x02:0x01)
             |(Relay_Temp[1] == 0x01?0x02:0x01)<<2
             |(Relay_Temp[2] == 0x01?0x02:0x01)<<4
             |(Relay_Temp[3] == 0x01?0x02:0x01)<<6;  
}
