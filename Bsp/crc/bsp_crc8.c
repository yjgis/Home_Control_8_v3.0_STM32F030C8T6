#include "bsp_crc8.h"



/**********************************************************************************
  * @brief  �����ݽ���CRCֵ����
  * @param  len--���ݳ��ȣ�
	          buf--��������
  * @retval CRCֵ
 *********************************************************************************/
uint8_t CRC8_Check(uint8_t len,const uint8_t *buf)
{
    uint8_t num_i = 0,num_j = 0,crc = 0,middle_byte = 0;
    for(num_i = 0 ; num_i < len-3; num_i++)
    {
        middle_byte = buf[num_i+3]; 
        for( num_j = 0 ; num_j < 8; num_j++)
			  {
            if(((crc^middle_byte)&0x01) == 0 )
						{
                crc >>=1;
            }
            else
						{
                crc^= 0x18;
                crc >>=1;
                crc |=0x80;
            }
            middle_byte >>=1;
        }
    }
    return crc ;
}



/*******************************END*********************************/
