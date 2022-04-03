 #include "stm32f10x.h"
#include "global_var_def.h"
void ADC_Init(void);


void ADC_scun_DMA(void);
extern void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint32_t Size, uint16_t Conf);
extern void DMA_Enable(DMA_Channel_TypeDef* Channel);


void ADC_scun_DMA(void)
{
	
	      ADC1->CR2 |= ADC_CR2_CONT;
        ADC1->CR2 |= ADC_CR2_DMA 
        | ADC_CR2_EXTTRIG 
        | ADC_CR2_EXTSEL 
        | ADC_CR2_JEXTSEL; 
        ADC1->CR1 |= ADC_CR1_SCAN; 
				ADC1->CR2 |= ADC_CR2_SWSTART; 
	
				DMA_Init(DMA1_Channel1, (uint32_t)&(ADC1->DR), (uint32_t) ADRTX, 10, ADCTOMEM );
				DMA_Enable(DMA1_Channel1);
}




void ADC_Init(void)
{
	//Clock =72Mhz
	
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ; // 
GPIOA->CRL &= ~ (GPIO_CRL_MODE0 | GPIO_CRL_CNF0); // PA0 
GPIOA->CRL &= ~ (GPIO_CRL_MODE1 | GPIO_CRL_CNF1); // PA1 
GPIOA->CRL &= ~ (GPIO_CRL_MODE2 | GPIO_CRL_CNF2); // PA2 
GPIOA->CRL &= ~ (GPIO_CRL_MODE3 | GPIO_CRL_CNF3); // PA3 
	
RCC->AHBENR|= 1; //DMA1 enable	
RCC->CFGR &=~(3<<14); //
RCC->CFGR |= 2<<14;// 72/6 = 12
ADC1->CR1 = 0;      // 
ADC1->CR2 = 0;
	

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // (1<<9) 
	ADC1->CR2 |= ADC_CR2_ADON; // 

ADC1->SMPR2 |= ADC_SMPR2_SMP0_0 | ADC_SMPR2_SMP0_1 ; // время выборки 28,5 циклов канала 0
ADC1->SMPR2 &= ~ADC_SMPR2_SMP0_2 ;
ADC1->SMPR2 |= ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1 ; // время выборки 28,5 циклов канала 1
ADC1->SMPR2 &= ~ADC_SMPR2_SMP1_2 ;
ADC1->SMPR2 |= ADC_SMPR2_SMP2_0 | ADC_SMPR2_SMP2_1 ; // время выборки 28,5 циклов канала 2
ADC1->SMPR2 &= ~ADC_SMPR2_SMP2_2 ;
ADC1->SMPR2 |= ADC_SMPR2_SMP3_0 | ADC_SMPR2_SMP3_1 ; // время выборки 28,5 циклов канала 3
ADC1->SMPR2 &= ~ADC_SMPR2_SMP3_2 ;
	
	

ADC1->SQR1 =0; 
ADC1->SQR3 =0; 

ADC1->JSQR =0; 
ADC1->JSQR |= ADC_JSQR_JSQ4_0; 


for(int i = 0;i<=10000;i++);
ADC1->CR2 |= ADC_CR2_CAL; 
while ((ADC1->CR2 & ADC_CR2_CAL) != 0) ; 
ADC1->CR2 |= ADC_CR2_EXTSEL; 
ADC1->CR2 |= ADC_CR2_EXTTRIG; 
       
       
}

