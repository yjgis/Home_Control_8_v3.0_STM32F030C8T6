#include "bsp_timer3.h"
#include "bsp_usart.h"


uint16_t Timing_Count = 0;
uint16_t Device_Online_Count = 6000;

void Timer_Init(void)  //1ms
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
	
  /* Time 定时器基础设置 */
  TIM_TimeBaseStructure.TIM_Period = 480;
  TIM_TimeBaseStructure.TIM_Prescaler = 100;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
	
  /*  TIM3 中断嵌套设计*/
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
	
  /* TIM 中断使能 */
  TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);

  /* TIM3 使能 */
  TIM_Cmd(TIM3, ENABLE);
}

void Timer3_Count_Decrement(void)
{
	Device_State_Judgment();
	
  if(Timing_Count)
	{
	  Timing_Count--;	
	}
}

void Timer3_Timing_Sec(uint8_t Timing_Sec)
{
   Timing_Count =  Timing_Sec * 1000;

   while(Timing_Count);
}


void Timer3_Delay_MS(uint16_t Delay_ms)  //1ms
{
  Timing_Count = Delay_ms;
                
	while(Timing_Count);
}	

void Device_State_Judgment(void)
{
   if(Device_State == Online && Device_Online_Count)
	 {
		 Device_Online_Count--;
	 }
	 else
	 {
	  Device_State = Offline;	 
	 }
}



