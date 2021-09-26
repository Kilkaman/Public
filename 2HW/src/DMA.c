#include "MDR1986VE8T.h"
#include "global_var_def.h" 
 void DMA_Init();
 
 void DMA_Init()
{   DMAControl* DMA = MDR_DMA;                  
    DMA->CHMUX0=(10<<24)|(10<<16)|(8<<8)|(8<<0);// �����������  8 �������� (TMR0_REQ) ����� DMA �� 0,1 �����������,
                                                // � 10 �������� (TMR2_REQ) ����� �� 2,3 �����������

    DMA->CTRL_BASE_PTR = 0x20000000;            // ������ ������� ����� ����������� ������ �������
		DMA->CONFIG = 0x1;                          // ��������� ������ ����������� DMA
    DMA->CHNL_PRI_ALT_SET = 0;
		DMA->CHNL_ENABLE_SET = (1<<3)|(1<<2)|(1<<1)|(1<<0);// ��������� ������ 0,1,2,3 ������

}
