#include "bsp_timer3.h"
#include "bsp_usart.h"


uint16_t Timing_Count = 0;
uint16_t Device_Online_Count = 0;

/**********************************************************************************
  * @brief  定时器初始化,开定时器3中断,1ms定时
  * @param  None 
  * @retval None
 *********************************************************************************/	
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

/**********************************************************************************
  * @brief  定时器3进入中断后需进行处理的函数
  * @param  None 
  * @retval None
 *********************************************************************************/	
void Timer3_Count_Decrement(void)
{
	Device_State_Judgment();
	
  if(Timing_Count)
	{
	  Timing_Count--;	
	}
}

/**********************************************************************************
  * @brief  基于Timer3的1ms延时
  * @param  Delay_ms--延时的时间 
  * @retval None
 *********************************************************************************/	
void Timer3_Delay(uint16_t Delay_ms)  //1ms
{
  Timing_Count = Delay_ms;              
	while(Timing_Count);
}	

/**********************************************************************************
  * @brief  对前置模块离线或者在线状态进行判断处理
  * @param  None
  * @retval None
 *********************************************************************************/	
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



