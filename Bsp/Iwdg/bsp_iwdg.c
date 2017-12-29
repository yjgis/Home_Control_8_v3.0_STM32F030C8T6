#include "bsp_iwdg.h"


/**********************************************************************************
  * @brief  ��ʼ���������Ź�
  * @param  prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)����Ƶ����=4*2^prer.�����ֵֻ����256!
	          rlr:��װ�ؼĴ���ֵ:��11λ��Ч��ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).
  * @retval ��
 *********************************************************************************/
void IWDG_Init(uint8_t prer,uint16_t rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	
	IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	
	IWDG_SetReload(rlr);  //����IWDG��װ��ֵ
	
	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	
	IWDG_Enable();  //ʹ��IWDG
}


/**********************************************************************************
  * @brief  ι�������Ź�
  * @param  ��
  * @retval ��
 *********************************************************************************/
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();//reload										   
}
