#include "bsp_io.h"
#include "bsp_usart.h"
#include "bsp_relay.h"
#include "string.h"
#include "bsp_timer3.h"

uint8_t IO_Enable_Buffer[8]={0};
uint8_t IO_Input_Buffer[8]={0};

uint8_t IO_Temp[2]={0};

GPIO IO_Switch_GPIO[8]={{GPIOB, GPIO_Pin_9},
                        {GPIOC, GPIO_Pin_14},
                        {GPIOC, GPIO_Pin_15},
                        {GPIOA, GPIO_Pin_7},
                        {GPIOA, GPIO_Pin_6},
												{GPIOA, GPIO_Pin_5},
												{GPIOA, GPIO_Pin_4},
                        {GPIOA, GPIO_Pin_3}};

GPIO IO_Trigger_GPIO[8]={{GPIOA, GPIO_Pin_15},
                         {GPIOB, GPIO_Pin_3},
                         {GPIOB, GPIO_Pin_4},
                         {GPIOB, GPIO_Pin_5},
                         {GPIOB, GPIO_Pin_6},
												 {GPIOB, GPIO_Pin_7},
												 {GPIOB, GPIO_Pin_8},
                         {GPIOC, GPIO_Pin_13}};

/**********************************************************************************
  * @brief  对输入IO端口进行初始化
  * @param  None
  * @retval None
 *********************************************************************************/												 
void IO_Init(void)
{
  IO_Input_Init();
  IO_Enable_Init();
}

/**********************************************************************************
  * @brief  对输入IO端口进行初始化
  * @param  None
  * @retval None
 *********************************************************************************/	
void IO_Input_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);		
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);			
}

/**********************************************************************************
  * @brief  IO使能拨码开关初始化
  * @param  None
  * @retval None
 *********************************************************************************/	
void IO_Enable_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);		
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);		
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);	
}

/**********************************************************************************
  * @brief  在线情况下对输入IO的状态进行扫描
  * @param  None
  * @retval None
 *********************************************************************************/	
void IO_Online_Input_Scan(void)
{
  uint8_t Cnt;
	
	for(Cnt = 0;Cnt < 8;Cnt++)
	{
   IO_Input_Buffer[Cnt]=(GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);		
	}
}

/**********************************************************************************
  * @brief  离线情况下对输入IO的状态进行扫描
  * @param  None
  * @retval None
 *********************************************************************************/	
void IO_Offline_Input_Scan(void)
{
  uint8_t Cnt = 0,Temp1 = 0,Temp2 = 0;

  for(Cnt = 0;Cnt < 8;Cnt++)
	{		
//   IO_Input_Buffer[Cnt]=(GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);
		Temp1 = (GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);			
	  Timer3_Delay(10);
		Temp2 = (GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);
			
		
		if(Temp1 == Temp2)
		{
		  if(IO_Input_Buffer[Cnt] != Temp2)
			{
		    IO_Control_Relay(Cnt);					
			  Timer3_Delay(200);
        IO_Input_Buffer[Cnt]=(GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);				
			}
		}
		
//		if(Temp1 != IO_Input_Buffer[Cnt])
//		{
////			Temp = Temp2;
//			Timer3_Delay(100);
//			Temp3 = (GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);
////			Timer3_Delay(10);
////			Temp4 = (GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);			
//     
//      if(Temp3 != Temp1)
//			{
//		    IO_Control_Relay(Cnt);				
//			}				
//		}
//		IO_Input_Buffer[Cnt] = Temp4;
	}
	
//	Timer3_Delay(50); 	
//	
//	for(Cnt = 0;Cnt < 8;Cnt++)
	
	
//	{
//   IO_Input_Buffer[Cnt]=(GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);		
//	}	

//	Timer3_Delay(50); 	
//	
//	for(Cnt = 0;Cnt < 8;Cnt++)
//	{	 
//		Temp = (GPIO_ReadInputDataBit(IO_Trigger_GPIO[Cnt].GPIO,IO_Trigger_GPIO[Cnt].GPIO_Pin)==Tirgger?0x01:0x00);
//		if(IO_Input_Buffer[Cnt] != Temp)
//		{
//		  IO_Input_Buffer[Cnt] = Temp;
//		  IO_Control_Relay(Cnt);
//		}
//	}
}

/**********************************************************************************
  * @brief  对IO使能拨码开关进行扫描
  * @param  None
  * @retval None
 *********************************************************************************/	
void IO_Enable_Scan(void)
{  
  uint8_t i=0;
  for(i=0;i<8;i++)
  {
    IO_Enable_Buffer[i]=(GPIO_ReadInputDataBit(IO_Switch_GPIO[i].GPIO,IO_Switch_GPIO[i].GPIO_Pin)==0?0x01:0x00);
  }
}

/**********************************************************************************
  * @brief  将存储IO输入的数据和IO使能拨码开关的数据转换成发送命令所需要的数据
  * @param  None
  * @retval None
 *********************************************************************************/	
void IO_State_Convert(void)
{
  IO_Temp[0] |=((IO_Enable_Buffer[0]==0x01?0x01:0x00)<<1
               |(IO_Enable_Buffer[1]==0x01?0x01:0x00)<<3
               |(IO_Enable_Buffer[2]==0x01?0x01:0x00)<<5
               |(IO_Enable_Buffer[3]==0x01?0x01:0x00)<<7);
  
  IO_Temp[1] |=((IO_Enable_Buffer[4]==0x01?0x01:0x00)<<1
               |(IO_Enable_Buffer[5]==0x01?0x01:0x00)<<3              
               |(IO_Enable_Buffer[6]==0x01?0x01:0x00)<<5
               |(IO_Enable_Buffer[7]==0x01?0x01:0x00)<<7);
	
  IO_Temp[0] |=((IO_Input_Buffer[0]==0x01?0x01:0x00)
               |(IO_Input_Buffer[1]==0x01?0x01:0x00)<<2
               |(IO_Input_Buffer[2]==0x01?0x01:0x00)<<4
               |(IO_Input_Buffer[3]==0x01?0x01:0x00)<<6);
  
  IO_Temp[1] |=((IO_Input_Buffer[4]==0x01?0x01:0x00)
               |(IO_Input_Buffer[5]==0x01?0x01:0x00)<<2
               |(IO_Input_Buffer[6]==0x01?0x01:0x00)<<4
               |(IO_Input_Buffer[7]==0x01?0x01:0x00)<<6);	
}
