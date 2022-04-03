 #include "stm32f10x.h"
#include "global_var_def.h"
 void UART_INIT(void);

 extern void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint32_t Size, uint16_t Conf);
 extern void DMA_Enable(DMA_Channel_TypeDef* Channel);
 extern void DMA_Disable(DMA_Channel_TypeDef* Channel);
 extern void DMA_DeInitRX(void);
 extern void DMA_DeInitTX(void);
 extern unsigned char Crc8(unsigned char *pcBlock, unsigned char len);

 
 
 
 
 
void UART_INIT(void)
{

 RCC->APB2ENR |= RCC_APB2ENR_USART1EN;// enable clock for USART1
 USART1->BRR  =  0x9c; 							// set baudrate //72mHz => 0x270-115200 0x9c - 460800															
 USART1->CR1  = (1<<13)|(1<<2)|(1<<3);// en, rx, tx, 1stopbit, 
 USART1->CR1  |= USART_CR1_RXNEIE;// 1<<5;
 USART1->CR3 |=USART_CR3_DMAT;		//  connect the DMA channel to the UART TX.
 USART1->CR3 |=USART_CR3_DMAR;   //  connect the DMA channel to the UART RX.
 NVIC_EnableIRQ(USART1_IRQn);
//Pr_Tmr(0xFFFFFFFFu);
}


 void USART1_IRQHandler(void)
 {
	 Pucket* puc =PUC;

	 
	 if (USART1->SR&(1<<5))// по приему
		 {
	

	
		
		DMA_Init( DMA1_Channel5,(uint32_t)&(USART1->DR), (uint32_t)((ADRRX)), 9, UARTTOMEM  );//load to read 
		TIM3->CNT = 0;
		DMA_Enable(DMA1_Channel5);//start reading
		USART1->CR1  &= ~USART_CR1_RXNEIE;//disasble UART RX interrupts
		puc->rx = 1;
		
	
				
			 
	 }
		

}
void DMA1_Channel5_IRQHandler(void)
{ 
	
	
	Pucket* puc =PUC;	
	int l_len;// = puc->length;
	int l_head = puc->head;
	int l_tail = puc->tail;
	puc->tail= l_head;	
//	
//	 l_head = 0x400;
//	 l_tail = 0;
	if(DMA1->ISR&(1<<17))//source: Channel 15 transfer complete flag 
	{
		puc->rx = 0;
		DMA_Disable(DMA1_Channel5);

		l_len = l_head - l_tail;//
	if (l_len>=0)
	{
		
		puc->rb = 0;//
		//puc->type = 0;
	}
	else{//
	l_len = (SIZE+1)-l_tail; //
	puc->rb = l_head; //
	}
	
  uint8_t l_crc8 = *(uint8_t*) (ADRRX 	+9-1);//read crc


  uint8_t l_crc82 = Crc8((uint8_t*) ADRRX 	, 9-1) ;//calc crc
	if (l_crc8!=l_crc82)//is crc are not equal 
		{
		for (int i = 0;i<255;i++)	*(uint8_t *)(ADRRX 	+i) = 0xff;//init memory with ones, it means error 
		}

//	DMA_Init( DMA1_Channel4,(uint32_t)&(USART1->DR), (uint32_t)(ADRTX+l_tail), l_len ,MEMTOUART);	//load DMA for TX 
		DMA_Init( DMA1_Channel4,(uint32_t)&(USART1->DR), (uint32_t)(ADRTX), 10 ,MEMTOUART);	//load DMA for TX 
	DMA_Enable(DMA1_Channel4);
	
	USART1->CR1  |= USART_CR1_RXNEIE;//enasble UART RX interrupts
	}
	else //source: Channel 5 transfer complete with error
	{
	for (int i = 2;i<255;i++)	*(uint8_t *)(ADRTX ) = 0xff;
	DMA_Disable(DMA1_Channel5);
	}
	
}
