#include "MDR32Fx.h"
#include "global_var_def.h"

void TimerConfig(void);
void Timer1_IRQHandler(void);

void TimerConfig(void)
{
MDR_RST_CLK_TypeDef* rst_clk = MDR_RST_CLK;
MDR_TIMER_TypeDef* timer;
  
	rst_clk->PER_CLOCK |= (1<<14);	//TIMER 1
	rst_clk->TIM_CLOCK = (1<<24)|(6<<0); 	//TIMER1 (HCLK/64)
// таймер 1 ---> 1 МГц
	timer = MDR_TIMER1;
	timer->PSG = 0;
	timer->ARR = 165; 									// значение основания счета для основного счетчика	   65535
	timer->CNTRL = 0x1;									// timer1 0n
	timer->STATUS = 0;
	timer->IE = (1<<0);									//CNT = 0 
	NVIC->ISER[0] = (1<<Timer1_IRQn);
}
	
void Timer1_IRQHandler()
{
Global_Var* pgv = PGV;		
unsigned int i1;
	i1 = 0;
	MDR_TIMER1->STATUS = i1;
	MDR_SSP2->DR = i1;
	MDR_SSP2->DR = i1;
	MDR_SSP2->DR = i1;
	MDR_SSP2->DR = i1;
	i1 = pgv->it;
	i1++;
	if(i1 == 2500)
	{
		i1 = MDR_PORTB->RXTX;
		i1 &= (1<<1);
		i1 ^= (1<<1);
		MDR_PORTB->RXTX = i1;
		
//		i1 = pgv->ibuf_rxlir;
//		i1++;
//		if (i1 == (sizeof(pgv->buf_angle)>>2)) i1 = 0;
//		pgv->ibuf_rxlir = i1;		
//		i1 = 0;
	}
	pgv->it = i1;
}

