/**
  ******************************************************************************
  * @file    stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include <string.h>
#include "bsp_timer3.h"


extern Receive Rx;
extern uint8_t ttt[6];

//uint8_t Buffer[5]={0x01,0x02,0x03,0x04,0x05};
/** @addtogroup STM32F0-Discovery_Demo
  * @{
  */

/** @addtogroup STM32F0XX_IT
  * @brief Interrupts driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}
/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */

uint8_t rx_temp[20]={0};
uint8_t rx_cnt=0;
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {		
		rx_temp[rx_cnt++]=USART_ReceiveData(USART1);
		
		 if(rx_temp[0]== 0xad)
     {
        if(rx_cnt == (rx_temp[2]+4))
        {			
					memcpy(Rx.Buffer,rx_temp,rx_cnt);
					Rx.Cont=rx_cnt;
					Rx.Flag=1;
					 Analyse_Received_Buffer(rx_temp,rx_cnt);	
					 rx_cnt=0;        
           memset(rx_temp,0,20);
      
         }
         else if(rx_cnt > (rx_temp[2]+4))
         {
           rx_cnt=0;
           memset(rx_temp,0,20);
         }
      }        
      else
      {
         memset(rx_temp,0,20);
         rx_cnt=0;  
      }
		
		 LED1_Toggle();
// USART1_Send_Data(ttt,6);
  }
}

uint8_t *Timer3_Cnt = 0;
void TIM3_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{ 
	  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		
    Timer3_Count_Decrement();
//		USART1_Send_Data(Buffer,5);

//		Timer3_Events();
		
		
	}
//	
//	LED1_Toggle();
}



/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
