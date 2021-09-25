#include "stm32f10x.h"
#include "core_cm3.h"
#include "global_var_def.h"

void delay(int a);
void PORT_INIT(void);
extern void UART_INIT(void);

void SysInit(void);

extern void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint16_t Size, uint16_t Conf);//Load DMAx to send 1 puc 
extern void DMA_Enable(DMA_Channel_TypeDef* Channel);// start DMA 
extern void DMA_Disable(DMA_Channel_TypeDef* Channel);// turn off DMA


Pucket pucket;

int main(void)
{
	Pucket* puc;

	__disable_irq();
			Flag_Reg = 0;
			puc = &pucket;
			PUC = puc;
		
		for(int i1 = 0; i1<sizeof(Pucket); i1+=4)		//0s in global struct
					*((unsigned int*)((int)puc+i1)) = 0;
  puc->Adr0 = (uint8_t*) ADR0;
	for (int i = 0;i<255;i++)
	*(uint8_t *)(ADR0+i) = 'A';

	PORT_INIT();
	UART_INIT();
	DMA_Disable(DMA1_Channel4);
	DMA_Disable(DMA1_Channel5);

	
 NVIC_EnableIRQ(DMA1_Channel4_IRQn);	// interrupt  for TX on
 NVIC_EnableIRQ(DMA1_Channel5_IRQn);// interrupt  for RX on
	
	
	__enable_irq();// interrupts on
	



  while (1)//just blinking
 {


	GPIOA->BSRR = 1;
	delay(500000);
GPIOA->BRR = 1;
delay(500000);
 }
}
 void PORT_INIT(void)
 {

	RCC->APB2ENR |= 1<<4; 							// PortC EN
	GPIOC->CRL =	(3<<4)|(1<<0);				//led C0
 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;  // enable clock for Alternate Function
// AFIO->MAPR   &= ~(1 << 2);         // clear USART1 remap
 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // enable clock for GPIOA	
 GPIOA->CRL =	(3<<4)|(1<<0);					//led A0
 GPIOA->CRH   &= ~(0xFFUL<<4);     //Clear PA9, PA10

 GPIOA->CRH   |=  (0x0B<<4);  		//USART1 Tx (PA9)  alternate output push-pull
 GPIOA->CRH   |=  (0x04<<8);     	//USART1 Rx (PA10) input floating
 } 
 

 
void SysInit(void)
{
	unsigned int StartUpCounter = 0, HSEStatus = 0;
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */

  RCC->CFGR &= (uint32_t)0xF8FF0000;

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;
	
  /* Disable all interrupts and clear pending bits  */
	 RCC->CIR = 0x009F0000;
		
	/* Enable HSE */  
	 RCC->CR |= 0x10000;

	{
		
		/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
		/* Enable HSE */    
		RCC->CR |=  ((uint32_t)0x00010000);
	 
		/* Wait till HSE is ready and if Time out is reached exit */
		do
		{
			HSEStatus = RCC->CR &  ((uint32_t)0x00020000);
			StartUpCounter++;  
		} while((HSEStatus == 0) && (StartUpCounter != ((uint16_t)0x0500)));

		if ((RCC->CR & RCC_CR_HSERDY) != RESET)
		{
			HSEStatus = (uint32_t)0x01;
		}
		else
		{
			HSEStatus = (uint32_t)0x00;
		}  

		if (HSEStatus == (uint32_t)0x01)
		{
			/* Enable Prefetch Buffer */
			FLASH->ACR |= FLASH_ACR_PRFTBE;

			/* Flash 2 wait state */
			FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
			FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

	 
			/* HCLK = SYSCLK */
			RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
				
			/* PCLK2 = HCLK */
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
			
			/* PCLK1 = HCLK */
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;


			
			/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
			RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
																					RCC_CFGR_PLLMULL));
			RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);


			/* Enable PLL */
			RCC->CR |= RCC_CR_PLLON;

			/* Wait till PLL is ready */
			while((RCC->CR & RCC_CR_PLLRDY) == 0)
			{
			}
			
			/* Select PLL as system clock source */
			RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
			RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

			/* Wait till PLL is used as system clock source */
			while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
			{
			}
		}
		
	}
}



void delay (int a)
{
 volatile int i,j;
 for (i=0 ; i < a ; i++)
 {
  j++;
 }
 return;
}

