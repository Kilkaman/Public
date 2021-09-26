#include "MDR1986VE8T.h"
#include "global_var_def.h" 

void TIMER1_Handler(void);
void Timer1Config(void);
void ADC_Handler(void);
void work_64ms(void);
void PortConf(void);


void TimerConfig(void)
{
	CLK_CNTR->TIM0_CLK = (1<<16)|(63);           	//  тактирование таймеров CLK=1Mhz
	CLK_CNTR->TIM1_CLK = (1<<16)|(63);           	// тактирование таймеров CLK=1Mhz
	CLK_CNTR->TIM2_CLK = (1<<16)|(63);           	// тактирование таймеров CLK=1Mhz
	CLK_CNTR->TIM3_CLK = (1<<16)|(63);           	// 
	
	TIMER0->CNT  = 0;                       // 
	TIMER0->PSG  = 0;                         // 
	TIMER0->ARR  = 9999;   //100hz   
	TIMER0->IE = (1<<1);    //прерывание при CNT = ARR
  NVIC_EnableIRQ(TMR0_IRQn);
	TIMER0->CNTRL =1;
	
	
	TIMER1->CNT  = 0;                       // 
	TIMER1->PSG  = 0;                         // 
	TIMER1->ARR  = 999;   //1 000hz   
	TIMER1->IE = (1<<1);//прерывание при CNT = ARR
  NVIC_EnableIRQ(TMR1_IRQn);
	TIMER1->CNTRL =1;
	
	TIMER2->CNT  = 0;                       // 
	TIMER2->PSG  = 0;                         // 
	TIMER2->ARR  = 29999;   //300hz
	TIMER2->IE = (1<<1);//прерывание при CNT = ARR
  NVIC_EnableIRQ(TMR2_IRQn);
	TIMER2->CNTRL =1;
	
	TIMER3->CNT  = 0;                       // 
	TIMER3->PSG  = 0;                         // 
	TIMER3->ARR  = 99;   //10 000hz
	TIMER3->IE = (1<<1);     //прерывание при CNT = ARR
  NVIC_EnableIRQ(TMR3_IRQn);
	TIMER3->CNTRL =1;
	
}

void INT_TMR0_Handler()
{
	
ADC0->CONTROL = 1;
 TIMER0->STATUS = 0;
}
void INT_TMR1_Handler()
{
	
 PortConf();
 TIMER1->STATUS = 0;
}

void INT_TMR2_Handler()
{
	
PortConf();
 TIMER2->STATUS = 0;
}

void INT_TMR3_Handler()
{
	
PortConf();
 TIMER3->STATUS = 0;
}
