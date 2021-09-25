 #include "stm32f10x.h"
#include "global_var_def.h"
 void UART_INIT(void);
 extern void delay(int a);
 extern void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint16_t Size, uint16_t Conf);
 extern void DMA_Enable(DMA_Channel_TypeDef* Channel);
 extern void DMA_Disable(DMA_Channel_TypeDef* Channel);
 extern void DMA_DeInitRX(void);
 extern void DMA_DeInitTX(void);
 void WorkTX(int h, int t);
void UART_INIT(void)
{

 RCC->APB2ENR |= RCC_APB2ENR_USART1EN;// enable clock for USART1
 USART1->BRR  =  0x9c; 							// set baudrate //0x270-115200 0x9c - 460800															
 USART1->CR1  = (1<<13)|(1<<2)|(1<<3);// en, rx, tx, 1stopbit, 
 USART1->CR1  |= USART_CR1_RXNEIE;// 1<<5;
 USART1->CR3 |=USART_CR3_DMAT;		//  connect the DMA channel to the UART TX.
 USART1->CR3 |=USART_CR3_DMAR;   //  connect the DMA channel to the UART RX.
 NVIC_EnableIRQ(USART1_IRQn);

}


 void USART1_IRQHandler(void)
 {
	 Pucket* puc =PUC;

	
	 if (USART1->SR&(1<<5))// 
		 {
		int l_len;
		l_len = USART1->DR & 0xff;//read 1st byte(size)
		DMA_Init( DMA1_Channel5,(uint32_t)&(USART1->DR), (uint32_t)((ADR0)), l_len, UARTTOMEM  );//load to read 
		DMA_Enable(DMA1_Channel5);//start deading
		USART1->CR1  &= ~USART_CR1_RXNEIE;//disasble UART RX interrupts
		puc->cnt += 1;
		puc->length = l_len;
		puc->type =1;
			
	 }
		 
	
}

