#include "MDR32Fx.h"
#include "global_var_def.h"

void SSP2Config(void);
void SSP2_IRQHandler(void);

void SSP2Config(void)
{
MDR_RST_CLK_TypeDef* rst_clk = MDR_RST_CLK;	
MDR_SSP_TypeDef* ssp2 = MDR_SSP2;

	rst_clk->PER_CLOCK |= (1<<20);								//Разрешение тактирования SPI2
	rst_clk->SSP_CLOCK = (1<<25)|(3<<8);   				//Разрешение тактовой частоты на SSP2 - 8МГц

	ssp2->CPSR = 2; 															//Коэффициент деления тактовой частоты F_SSPCLK(8/2)=4МГц
	ssp2->CR0 = (7<<0)|(3<<8)|(1<<6)|(0<<7);			//Скорость последовательного обмена F_SSPCLK / ( CPSDVR * (1 + SCR) ) = 1МГц,SPO=1
	ssp2->CR1 = 1<<1;															//Разрешение работы приемопередатчика
	
	ssp2->IMSC = 1<<2;	
	NVIC->IP[SSP2_IRQn] = (1<<5);									//приоритет ssp2 - 1
	NVIC->ISER[0] = 1<<SSP2_IRQn;
}

void SSP2_IRQHandler()
{
Global_Var* pgv = PGV;	
unsigned int i1,i2;
MDR_SSP_TypeDef* ssp2 = MDR_SSP2;
	
	i1 = ssp2->DR;
	i1 <<= 8;
	i2 = ssp2->DR;
	i1 = i2 + i1;
	i1 <<= 8;
	i2 = ssp2->DR;
	i1 = i2 + i1;
	i1 <<= 8;
	i2 = ssp2->DR;
	i1 = i2 + i1;
	i1 <<= 2;
	i1 >>= 8;
	pgv->angle = i1;

	if(pgv->f_stream)
	{
		i2 = pgv->head;
		*(unsigned int*)(ADR0+i2) = i1;
		i2+=4;	
		pgv->head=i2&NSIZE;
	}
	else
	{
	
	i2 = ADR0;
		*(unsigned int*)(ADR0+i2) = i1;
		i2+=4;	
		pgv->head=i2&NSIZE;
	pgv->tail= ADR0;
	}
}	
