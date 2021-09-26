#include "MDR1986VE8T.h"
#include "global_var_def.h" 
 void DMA_Init();
 
 void DMA_Init()
{   DMAControl* DMA = MDR_DMA;                  
    DMA->CHMUX0=(10<<24)|(10<<16)|(8<<8)|(8<<0);// Настраиваем  8 реальный (TMR0_REQ) канал DMA на 0,1 виртуальный,
                                                // и 10 реальный (TMR2_REQ) канал на 2,3 виртуальные

    DMA->CTRL_BASE_PTR = 0x20000000;            // Задаем базовый адрес управляющих данных каналов
		DMA->CONFIG = 0x1;                          // разрешили работу контроллера DMA
    DMA->CHNL_PRI_ALT_SET = 0;
		DMA->CHNL_ENABLE_SET = (1<<3)|(1<<2)|(1<<1)|(1<<0);// разрешили работу 0,1,2,3 канала

}
