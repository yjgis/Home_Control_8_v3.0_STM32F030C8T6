#include "bsp_timer3.h"
#include "bsp_usart.h"


uint16_t Timing_Count = 0;
uint16_t Device_Online_Count = 0;

/**********************************************************************************
  * @brief  ��ʱ����ʼ��,����ʱ��3�ж�,1ms��ʱ
  * @param  None 
  * @retval None
 *********************************************************************************/	
void Timer_Init(void)  //1ms
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
	
  /* Time ��ʱ���������� */
  TIM_TimeBaseStructure.TIM_Period = 480;
  TIM_TimeBaseStructure.TIM_Prescaler = 100;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
	
  /*  TIM3 �ж�Ƕ�����*/
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
	
  /* TIM �ж�ʹ�� */
  TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);

  /* TIM3 ʹ�� */
  TIM_Cmd(TIM3, ENABLE);
}

/**********************************************************************************
  * @brief  ��ʱ��3�����жϺ�����д���ĺ���
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
  * @brief  ����Timer3��1ms��ʱ
  * @param  Delay_ms--��ʱ��ʱ�� 
  * @retval None
 *********************************************************************************/	
void Timer3_Delay(uint16_t Delay_ms)  //1ms
{
  Timing_Count = Delay_ms;              
	while(Timing_Count);
}	

/**********************************************************************************
  * @brief  ��ǰ��ģ�����߻�������״̬�����жϴ���
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



