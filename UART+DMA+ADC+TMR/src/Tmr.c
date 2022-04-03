 #include "stm32f10x.h"
#include "global_var_def.h"

void Timer_conf(void);
extern void DMA_Disable(DMA_Channel_TypeDef* Channel);
extern void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint16_t Size, uint16_t Conf);
extern void DMA_Enable(DMA_Channel_TypeDef* Channel);
void Timer_conf(void)
{

	RCC->APB1ENR|=(1<<1);
	TIM3->SMCR&=~(7);
	TIM3->CR1 = 1;
	TIM3->PSC = 0x719; 
	TIM3->ARR  =100; 
	
	TIM3->DIER|= 1;
	
	NVIC_EnableIRQ(TIM3_IRQn);
}



void TIM3_IRQHandler(void)
{
	Pucket* puc =PUC;
	DMA_Channel_TypeDef *DMARX = DMA1_Channel5;
	static uint8_t l_rx;
	if(l_rx&puc->rx)									 // if waiting is too long
	{
		DMA_Disable(DMARX);							 //
		USART1->CR1  |= USART_CR1_RXNEIE;//enasble UART RX interrupts
		puc->rx = 0;
	}		
		
	l_rx = puc->rx;
	
//	*(unsigned int*)(ADRRX+0x50)= l_rx;
	TIM3->SR&=~1;
}


