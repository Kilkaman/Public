#include "MDR1986VE8T.h"
#include "global_var_def.h" 

#define CHARGE_ADC 2                
#define PAUSE_ADC  1               



//void ADC_Handler(void);


void ADCInit(void);

void ADCInit(void)
{
	CLK_CNTR->ADC0_CLK = (13u<<28)|(1<<16)|5;	// ADCCLK0 = MAX_CLK/6 = 10,66M
	ADC0->KEY = _KEY_;
	ADC0->CONFIG0 = (1<<10)|(1<<6)|(0<<1)|1;     // 
	ADC0->CONFIG1 = (CHARGE_ADC<<3)|(PAUSE_ADC<<12);    
	ADC0->CONTROL = (1<<8);			            // (ADC0 CH1)
	ADC0->FIFOEN0 = (1<<1);                 //FIFO 
	ADC0->CONFIG2 = (1<<1);								//прерывание при FIFO OverFlow
  NVIC_EnableIRQ(ADC0_IRQn);
}
	
void INT_ADC0_Handler()
{
	//Результаты преобразования АЦП сохраняются в выходном FIFO размером 16 записей, 
	// соответственно нам нужно считать массив 2 раза, 1е 16 записей запускаются прыванием по таймеру, 
	//2е прерыванием по заполнению по заполнению буфера 
	
	Global_Var* pgv = PGV;
	if(pgv->ADCN == 0)
	{		
		pgv->ADC_sum_val = 0;//если это 1е 16 записей, очищаем накопитель 
		pgv->ADCN = 1;
	}else{
		pgv->ADCN = 0;
	}
	
	int l_val = pgv->ADC_mean_val;
	for(int i = 0;i<16; i++ )
	{
		l_val += ADC0->RESULT&0xffff;

	}
	pgv->ADC_sum_val = l_val;
	if(pgv->ADCN==1)ADC0->CONTROL = 1; //если 16записей есть запускаем запись
	else		
	{
	pgv->ADC_mean_val=l_val>>5; // берем среднее по 32значениям 
	ADC0->CONTROL = 0;		//останавливаем запись
	}

}

