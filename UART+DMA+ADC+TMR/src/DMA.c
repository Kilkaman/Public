#include "stm32f10x.h"
#include "core_cm3.h"
#include "global_var_def.h"
#define DMA1_Channel4_IT_Mask    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA1_Channel5_IT_Mask    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))
#define DMA1_Channel1_IT_Mask    ((uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1))


#define DMA_BUFFER_SIZE 256
void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint32_t Size, uint16_t Conf);
void DMA_Enable(DMA_Channel_TypeDef* Channel);
void DMA_Disable(DMA_Channel_TypeDef* Channel);
 void DMA_DeInitRX(void);
 void DMA_DeInitTX(void);
 void DMA_DeInitADC(void);

void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint32_t Size, uint16_t Conf)
{
	
uint32_t tmp = 0;
 	RCC->AHBENR |= 1; 
    tmp = Channel->CCR;		
    tmp &= CCR_CLEAR_Mask;	
    tmp |= Conf;			
 
    Channel->CNDTR = Size;	//
    Channel->CPAR = Perif;	// 
    Channel->CMAR = Mem;		//
    Channel->CCR = tmp;		//
		//DMA1->IFCR = DMA_IFCR_CTCIF4;		// Drop the flask of the empty register. Do not send a zero byte
}
void DMA_DeInitADC(void)
{
	//ADC_OFF
 DMA1->IFCR |= DMA1_Channel1_IT_Mask;
}

 void DMA_Enable(DMA_Channel_TypeDef* Channel)
{
    Channel->CCR |= DMA_CCR1_EN;
		
}
 
void DMA_Disable(DMA_Channel_TypeDef* Channel)
{
	 /* Disable the selected DMAy Channelx */
	Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
  /* Reset DMAy Channelx control register */
  Channel->CCR  = 0;
  
  /* Reset DMAy Channelx remaining bytes register */
 Channel->CNDTR = 0;
  
  /* Reset DMAy Channelx peripheral address register */
  Channel->CPAR  = 0;
  
  /* Reset DMAy Channelx memory address register */
  Channel->CMAR = 0;
	
	switch((int)Channel)
	{
		case (int)DMA1_Channel4:
		DMA_DeInitTX();
		break;
		
		case (int)DMA1_Channel5:
	  NVIC_EnableIRQ(USART1_IRQn);
		DMA_DeInitRX();
		break;	
		
		case (int)DMA1_Channel1:
		
		DMA_DeInitADC();
		break;	
	}
	
}

 void DMA_DeInitTX(void)
{  
	DMA1->IFCR |= DMA1_Channel4_IT_Mask;
}
 void DMA_DeInitRX(void)
{  
	DMA1->IFCR |= DMA1_Channel5_IT_Mask;
}
void DMA1_Channel4_IRQHandler(void)
{
	Pucket* puc =PUC;	
	int l_rb = puc->rb;
	if (!l_rb)DMA_Disable(DMA1_Channel4);
	else{
	DMA_Disable(DMA1_Channel4);
	DMA_Init( DMA1_Channel4,(uint32_t)&(USART1->DR), (uint32_t)(ADRTX), l_rb ,MEMTOUART);	//load DMA for TX 
  DMA_Enable(DMA1_Channel4);
	puc->rb = 0;
	}
}

//void DMA1_Channel1_IRQHandler(void)
//{
////	DMA_Disable(DMA1_Channel1);
////	DMA_Init(DMA1_Channel1, (uint32_t)&(ADC1->DR), (uint32_t) ADRTX, 10, ADCTOMEM );
////	DMA_Enable(DMA1_Channel1);
//	Pucket* puc =PUC;
////	 int l_head = puc->head;
////	 	//*(uint16_t*)(ADRTX+l_head) = ADC1->DR;
////		l_head= (l_head+200)&SIZE;
////				DMA_Init(DMA1_Channel1, (uint32_t)&(ADC1->DR), (uint32_t) ADRTX, 10, ADCTOMEM );
////				DMA_Enable(DMA1_Channel1);
//	 DMA1->IFCR |= DMA1_Channel1_IT_Mask;
//}

