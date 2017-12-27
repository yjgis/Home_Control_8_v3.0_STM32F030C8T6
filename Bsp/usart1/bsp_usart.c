#include "bsp_usart.h"
#include "bsp_crc8.h"
#include "bsp_io.h"
#include "bsp_relay.h"
#include <string.h>
#include "bsp_timer3.h"

uint8_t RS485_Addr=0;
uint8_t Device_State=Online;


GPIO RS485_Addr_GPIO[6] ={{GPIOB, GPIO_Pin_12},
                          {GPIOB, GPIO_Pin_13},
                          {GPIOB, GPIO_Pin_14},
                          {GPIOB, GPIO_Pin_15},
                          {GPIOA, GPIO_Pin_8},
                          {GPIOA, GPIO_Pin_11}};




void USART1_Init(void)
{	
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);   
 	
	//USART1_TX -> PA9 , USART1_RX -> PA10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;                 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);   

//  //RS485_DIR ->PF4	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
//  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	
  USART_InitStructure.USART_BaudRate = Baud_Rate;//设置串口波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置停止位
  USART_InitStructure.USART_Parity = USART_Parity_No;//设置效验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置流控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//设置工作模式
  USART_Init(USART1, &USART_InitStructure); //配置入结构体	
	
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);			
  USART_Cmd(USART1, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Addr_Switch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);		
}


void Addr_Switch_Scan(void)
{
	uint8_t i=0;
  for(i=0;i<6;i++)
  {
    if((GPIO_ReadInputDataBit(RS485_Addr_GPIO[i].GPIO,RS485_Addr_GPIO[i].GPIO_Pin)==0?0x01:0x00)) 
    {
      RS485_Addr |=(0x01<<i);        
    }
    else
    {
      RS485_Addr &=~(0x01<<i);
    }
  }
}





void Analyse_Received_Buffer(uint8_t *Buffer,uint8_t Cnt)
{
	if(Buffer[3]==RS485_Addr)
  {							
    switch(Buffer[4])
    { 	
    case 0x20:
      Device_State = Online;
      Device_Online_Count = 6000;//6s
      IO_State_Convert();
      Relay_State_Convert();
      Response_IO_Relay_State(Buffer[4]);
      memset(IO_Temp,0,2);	
      break;
      
    case 0x60: 
      UART_Cmd_Control_Relay(Buffer);						
      break;
    }
  }
  else if(Buffer[3] == 0xff && Buffer[4] == 0xf0)
  {
    Response_RS485_Adrress(Buffer[3],Buffer[4]); 
  } 		

}

void Response_IO_Relay_State(uint8_t cmd)
{
  uint8_t Send_Temp[15]={0};
  uint8_t CRC_Temp[10]={0};
  Send_Temp[0]=0xad;
  CRC_Temp[0]=Send_Temp[0];
  
  Send_Temp[1]=0xda;
  CRC_Temp[1]=Send_Temp[1];
  
  Send_Temp[2]=0x03;
  CRC_Temp[2]=Send_Temp[2];
  
  Send_Temp[3]=RS485_Addr;
  CRC_Temp[3]=Send_Temp[3];
  
  Send_Temp[4]=cmd;
  CRC_Temp[4]=Send_Temp[4];
  
  Send_Temp[5]=Device_Mode;
  CRC_Temp[5]=Send_Temp[5];
  
  Send_Temp[6]=IO_Temp[1];
  CRC_Temp[6]=Send_Temp[6];
  
  Send_Temp[7]=IO_Temp[0];
  CRC_Temp[7]=Send_Temp[7];
  
  Send_Temp[8]=Relay_State;
  CRC_Temp[8]=Send_Temp[8];
  
  Send_Temp[2]=6;
  
  Send_Temp[9]=CRC8_Check(9,CRC_Temp);

  USART1_Send_Data(Send_Temp,10);
}

void UART_Cmd_Control_Relay(uint8_t *Cmd_Temp)
{
  Cmd_Control_Relay(Cmd_Temp); 
  Response_Cmd_Control_Msg(Cmd_Temp[4]);
}

void Response_Cmd_Control_Msg(uint8_t cmd)
{
  uint8_t Send_Temp[15]={0};
  uint8_t CRC_Temp[10]={0};
  Send_Temp[0]=0xad;
  CRC_Temp[0]=Send_Temp[0];
  
  Send_Temp[1]=0xda;
  CRC_Temp[1]=Send_Temp[1];
  
  Send_Temp[2]=0x03;
  CRC_Temp[2]=Send_Temp[2];  
  
  Send_Temp[3]=RS485_Addr;
  CRC_Temp[3]=Send_Temp[3];
  
  Send_Temp[4]=cmd;
  CRC_Temp[4]=Send_Temp[4];
  
  Send_Temp[5]=Device_Mode;
  CRC_Temp[5]=Send_Temp[5];
  
  Send_Temp[2]=3;
  
  Send_Temp[6]=CRC8_Check(6,CRC_Temp);
   
  USART1_Send_Data(Send_Temp,7);
}

void Response_RS485_Adrress(uint8_t addr,uint8_t cmd)
{
  uint8_t Send_Temp[15]={0};
  uint8_t CRC_Temp[10]={0};
  Send_Temp[0]=0xad;
  CRC_Temp[0]=Send_Temp[0];
  
  Send_Temp[1]=0xda;
  CRC_Temp[1]=Send_Temp[1];
  
  Send_Temp[2]=0x03;
  CRC_Temp[2]=Send_Temp[2];  
  
  Send_Temp[3]=addr;
  CRC_Temp[3]=Send_Temp[3];
  
  Send_Temp[4]=cmd;
  CRC_Temp[4]=Send_Temp[4];
  
  Send_Temp[5]=Device_Mode;
  CRC_Temp[5]=Send_Temp[5];
  
  Send_Temp[6]=RS485_Addr;
  CRC_Temp[6]=Send_Temp[6];
  
  Send_Temp[2]=4;
  
  Send_Temp[7]=CRC8_Check(7,CRC_Temp);
  
  USART1_Send_Data(Send_Temp,8);
}





void USART1_Send_Data(volatile uint8_t *buf,uint8_t len)
{
  uint8_t i=0;

//  GPIO_SetBits(GPIOA,GPIO_Pin_6); //进入发送模式	
	
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	for(i=0;i<len;i++)
	{
   USART_SendData(USART1,buf[i]);
		
	 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	
  }
	
//  GPIO_ResetBits(GPIOA,GPIO_Pin_6);	//进入接收模式		
}

void uart_puts(char *s)
{
	while (*s)
	uart_putc(*s++);
}
void uart_putc(unsigned char c)
{
	while(!((USART1->ISR)&(1<<7)));
	USART1->TDR=c;	
}

