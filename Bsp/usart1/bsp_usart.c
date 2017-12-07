#include "bsp_usart.h"




void USART1_Init(void)
{	
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);	
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

  //RS485_DIR ->PF4	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOF,GPIO_Pin_4);
	
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


void USART1_Send_Data(volatile uint8_t *buf,uint8_t len)
{
  uint8_t i=0;

  GPIO_SetBits(GPIOF,GPIO_Pin_4); //进入发送模式	
	
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	for(i=0;i<len;i++)
	{
   USART_SendData(USART1,buf[i]);
		
	 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	
  }
  GPIO_ResetBits(GPIOF,GPIO_Pin_4);	//进入接收模式		
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

