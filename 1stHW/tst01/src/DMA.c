#include "stm32f10x.h"
#include "core_cm3.h"
#include "global_var_def.h"
#define DMA1_Channel4_IT_Mask    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA1_Channel5_IT_Mask    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))
#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
                                   ((PERIPH) == DMA1_Channel2) || \
                                   ((PERIPH) == DMA1_Channel3) || \
                                   ((PERIPH) == DMA1_Channel4) || \
                                   ((PERIPH) == DMA1_Channel5) || \
                                   ((PERIPH) == DMA1_Channel6) || \
                                   ((PERIPH) == DMA1_Channel7) || \
                                   ((PERIPH) == DMA2_Channel1) || \
                                   ((PERIPH) == DMA2_Channel2) || \
                                   ((PERIPH) == DMA2_Channel3) || \
                                   ((PERIPH) == DMA2_Channel4) || \
                                   ((PERIPH) == DMA2_Channel5))

#define DMA_BUFFER_SIZE 256
void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint16_t Size, uint16_t Conf);
void DMA_Enable(DMA_Channel_TypeDef* Channel);
void DMA_Disable(DMA_Channel_TypeDef* Channel);
void DMA_DeInitRX(void);
void DMA_DeInitTX(void);
extern unsigned char Crc8(unsigned char *pcBlock, unsigned char len);

void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint16_t Size, uint16_t Conf)
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
		DMA1->IFCR = DMA_IFCR_CTCIF4;		// Drop the flask of the empty register. Do not send a zero byte
}
void DMA_Enable(DMA_Channel_TypeDef* Channel)
{
    Channel->CCR |= DMA_CCR1_EN;
		
}
 
void DMA_Disable(DMA_Channel_TypeDef* Channel)
{
    Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
	if (Channel == DMA1_Channel4)	DMA_DeInitTX();
	else{
	NVIC_EnableIRQ(USART1_IRQn);
	DMA_DeInitRX();
	}
}

void DMA_DeInitTX(void)
{  
  /* Disable the selected DMAy Channelx */
  DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
  
  /* Reset DMAy Channelx control register */
  DMA1_Channel4->CCR  = 0;
  
  /* Reset DMAy Channelx remaining bytes register */
  DMA1_Channel4->CNDTR = 0;
  
  /* Reset DMAy Channelx peripheral address register */
  DMA1_Channel4->CPAR  = 0;
  
  /* Reset DMAy Channelx memory address register */
  DMA1_Channel4->CMAR = 0;
	
	DMA1->IFCR |= DMA1_Channel4_IT_Mask;

}
void DMA_DeInitRX(void)
{  
  /* Disable the selected DMAy Channelx */
  DMA1_Channel5->CCR &= (uint16_t)(~DMA_CCR1_EN);
  
  /* Reset DMAy Channelx control register */
  DMA1_Channel5->CCR  = 0;
  
  /* Reset DMAy Channelx remaining bytes register */
  DMA1_Channel5->CNDTR = 0;
  
  /* Reset DMAy Channelx peripheral address register */
  DMA1_Channel5->CPAR  = 0;
  
  /* Reset DMAy Channelx memory address register */
  DMA1_Channel5->CMAR = 0;
	
	DMA1->IFCR |= DMA1_Channel5_IT_Mask;

}
void DMA1_Channel4_IRQHandler(void)
{
DMA_Disable(DMA1_Channel4);

}
void DMA1_Channel5_IRQHandler(void)
{
	 Pucket* puc =PUC;
	if(DMA1->ISR&(1<<17))//source: Channel 5 transfer complete flag 
	{
	uint8_t l_len = puc->length;
  uint8_t l_crc8 = *(uint8_t*) (ADR0+l_len-1);//read crc
	DMA_Disable(DMA1_Channel5);
  uint8_t l_crc82 = Crc8((uint8_t*) ADR0, l_len-1) ;//calc crc
	if (l_crc8!=l_crc82)//is crc are not equal 
		{
		for (int i = 0;i<255;i++)	*(uint8_t *)(ADR0+i) = 0xff;//init memory with ones, it means error 
		}

	DMA_Init( DMA1_Channel4,(uint32_t)&(USART1->DR), (uint32_t)(ADR0), l_len ,MEMTOUART);	//load DMA for TX 
		puc->type =0;
	DMA_Enable(DMA1_Channel4);
	USART1->CR1  |= USART_CR1_RXNEIE;//enasble UART RX interrupts
	}
	else //source: Channel 5 transfer complete with error
	{
	for (int i = 0;i<255;i++)	*(uint8_t *)(ADR0+i) = 0xff;
	DMA_Disable(DMA1_Channel5);
	}
	
}
